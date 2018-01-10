#include <QDebug>
#include <QStringRef>
#include "sortermodel.h"

SorterModel::SorterModel()
{
}

int SorterModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_files.count();
}

QVariant SorterModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if (row < 0 || row >= m_files.count())
        return QVariant();

    switch (role) {
    case FileName:
        return m_files.at(row).name;
    }

    return QVariant();
}

void SorterModel::refreshModel(QString folderPath)
{
    m_currentFolderPath = folderPath;

    beginResetModel();
    m_files.clear();

    folderPath.remove("file://");
    if (!folderPath.endsWith('/'))
        folderPath.append('/');
    qDebug() << folderPath;

    if (!folderPath.isEmpty()) {
        QRegExp regExp("[0-9][1-9]\."); // 01.fileName

        QStringList folderFiles = QDir(folderPath).entryList(QDir::Files);
        for (int row = 0; row < folderFiles.count(); ++row) {
            QString fileName = folderFiles.at(row);
            m_files << SFile(row, fileName);


//            QString numPart = file.mid(0, 3);
//            if (!numPart.contains(regExp)) {
//                QString oldName = folderPath + file;
//                folderFiles.replace(row, QString("99." + file));
//                QString newName = folderPath + "99." + file;
//                qDebug() << oldName << newName;
//                qDebug() << rename(oldName.toStdString().c_str(), newName.toStdString().c_str());
//            }
        }

    }

    endResetModel();
}

void SorterModel::moveItems(int sourceIndex, int destinationIndex)
{
    qDebug() << sourceIndex << destinationIndex;
//    QString oldName = m_files.at(sourceIndex);
//    QString newName = m_files.at(destinationIndex);

//    bool isOk = rename(oldName.toStdString().c_str(), newName.toStdString().c_str()) == 0;

    if (/*isOk*/ true) {
        beginResetModel();
        m_files.move(sourceIndex, destinationIndex);
        endResetModel();
    }
}

QHash<int, QByteArray> SorterModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FileName] = "fileName";
    return roles;
}
