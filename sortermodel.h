#ifndef SORTERMODEL_H
#define SORTERMODEL_H

#include <QAbstractListModel>
#include <QFile>
#include <QDir>

#include "qqmlhelpers.h"

class SorterModel : public QAbstractListModel
{
    Q_OBJECT
    QML_WRITABLE_PROPERTY(QString, notificationMessage)

public:
    enum SorterRoles {
      FileName = Qt::UserRole,
    };
    SorterModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

public slots:
    void refreshModel(QString folderPath = "");
    void moveItems(int sourceIndex, int destinationIndex);
    void saveChanges();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QStringList m_fileList;
    QString m_currentFolderPath;
    void initModel();
    bool safeRename(const QString &oldName, QString &newName, int loopCount = 0);
};

#endif // SORTERMODEL_H
