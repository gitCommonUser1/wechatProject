#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QDebug>
#include <QVariant>
#include <QAbstractTableModel>
#include "studentdata.h"

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableModel(QObject *parent = nullptr){}
    enum ItemRoles{
            TypeName = Qt::UserRole + 1,
            TypeTelephone,
            TypeFire
        };

    int rowCount(const QModelIndex & = QModelIndex()) const override
     {
         return studentList.count();
     }

     int columnCount(const QModelIndex & = QModelIndex()) const override
     {
         return 4;
     }

     QVariant data(const QModelIndex &index, int role) const override
     {
        if (index.row() < 0 || index.row() >= studentList.count())
            return QVariant();
        StudentData item = studentList[index.row()];
        if (role == TypeName)
            return item.name();
        else if (role == TypeTelephone)
            return item.telephone();
        else if(role == TypeFire)
            return item.fire();
        return QVariant();
     }

     QHash<int, QByteArray> roleNames() const override
     {
         QHash<int, QByteArray> roles;
         roles[TypeName] = "name";
         roles[TypeTelephone] = "telephone";
         roles[TypeFire] = "fire";
         return roles;
     }

signals:

public slots:

public:
     QList<StudentData>studentList;
};

#endif // TABLEMODEL_H
