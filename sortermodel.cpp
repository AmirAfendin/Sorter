#include <QDebug>
#include <QStringRef>
#include "sortermodel.h"

SorterModel::SorterModel()
{
    m_currentFolderPath = "";
}

int SorterModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_fileList.count();
}

QVariant SorterModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if (row < 0 || row >= m_fileList.count())
        return QVariant();

    switch (role) {
    case FileName:
        return m_fileList.at(row);
    }

    return QVariant();
}

void SorterModel::refreshModel(QString folderPath)
{
    if (!folderPath.isEmpty()) {
        folderPath.remove("file://");
        if (!folderPath.endsWith('/'))
            folderPath.append('/');
        m_currentFolderPath = folderPath;
    }

    beginResetModel();
    m_fileList.clear();

    m_fileList = QDir(m_currentFolderPath).entryList(QDir::Files);

    endResetModel();
}

void SorterModel::moveItems(int sourceIndex, int destinationIndex)
{
    qDebug() << sourceIndex << destinationIndex;

    beginResetModel();
    m_fileList.move(sourceIndex, destinationIndex);
    endResetModel();
}

void SorterModel::saveChanges()
{
    if (m_fileList.isEmpty())
        return;

    QDir::setCurrent(m_currentFolderPath);
    QRegExp regExp("\\b[0-9][0-9]\\."); //01.file
    QString oldName;
    QString editName;
    QString newName;
    QString errorString = tr("Ошибка в переименовке на позициях: \n");

    for (int i = 0; i < m_fileList.count(); ++i) {
        oldName = m_fileList.at(i);
        if (oldName.contains(regExp)) {
            editName = oldName;
            editName.remove(0, 2);
            newName = QString::number(i + 1).rightJustified(2, '0');
            newName += editName;
        } else {
            newName = QString::number(i + 1).rightJustified(2, '0') + '.';
            newName += oldName;
        }

        if (!safeRename(oldName, newName))
            errorString += QString::number(i + 1) + ", ";
    }

    if (errorString.contains(',')) { // ',' - means there is corrupted indexes listed
        errorString.chop(2); // removes last ", ";
        set_notificationMessage(errorString);
    }

    set_notificationMessage(tr("Сохранение прошло без ошибок!"));
    refreshModel();
}

QHash<int, QByteArray> SorterModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FileName] = "fileName";
    return roles;
}

bool SorterModel::safeRename(const QString &oldName, QString &newName, int loopCount)
{
    if (oldName == newName)
        return true;

    bool success = QFile::rename(oldName, newName);

    if (success) {
        return true;
    } else if (loopCount > 0) {
        return false;
    } else {
        int lastDotIndex = newName.lastIndexOf('.');
        newName.insert(lastDotIndex, '.'); //adds additional dot before file format
        safeRename(oldName, newName, 1);
    }

    return false;
}
