#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
#include "studentdata.h"
#include "tablemodel.h"

class QNetworkAccessManager;

class HttpClient : public QObject
{
    Q_OBJECT
public:
    explicit HttpClient(QObject *parent = nullptr);
    Q_INVOKABLE void update();
    Q_INVOKABLE void clear();
    Q_INVOKABLE void test();
    Q_INVOKABLE void getPhones();
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void update(int index,QString fire);
    Q_INVOKABLE void newData(QString name = "0",QString phone = "0",QString fire = "0");
    void setModel(TableModel *t_model){
        model = t_model;
    }
signals:

public slots:

private:
    QNetworkAccessManager *manager;
    TableModel *model;
};

#endif // HTTPCLIENT_H
