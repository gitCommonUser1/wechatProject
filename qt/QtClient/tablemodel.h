#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QDebug>
#include <QVariant>
#include <QAbstractItemModel>
#include "studentdata.h"

class TableModel : public QAbstractListModel
{
    Q_OBJECT
public:
    TableModel(){}
    enum ItemRoles{
            TypeName = Qt::UserRole + 1,
            TypeTelephone,
            TypeFire
        };

    int rowCount(const QModelIndex & = QModelIndex()) const override
     {
         return studentList.count();
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

     void remove(int index){
         beginRemoveRows(QModelIndex(),index,index);
         studentList.removeAt(index);
         endRemoveRows();
     }

     void update(int index,QString fire){
         studentList[index].setFire(fire);
         dataChanged(this->index(index),this->index(index));
     }

     void clear(){
         if(studentList.size() == 0)
             return ;
         for(int i = studentList.size() - 1;i >= 0; --i){
             beginRemoveRows(QModelIndex(),i,i);
             studentList.removeAt(i);
             endRemoveRows();
         }
     }
     void insert(int index){
         beginInsertRows(QModelIndex(),index,index);
         endInsertRows();
     }

signals:

public slots:

public:
     QList<StudentData>studentList;
};

#endif // TABLEMODEL_H
