#ifndef SORTERMODEL_H
#define SORTERMODEL_H

#include <QAbstractListModel>
#include <QFile>
#include <QDir>

#include "sfile.h"

class SorterModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum SorterRoles {
      FileName = Qt::UserRole,
    };
    SorterModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

public slots:
    void refreshModel(QString folderPath);
    void moveItems(int sourceIndex, int destinationIndex);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<SFile> m_files;
    QString m_currentFolderPath;
    void initModel();
};

#endif // SORTERMODEL_H
