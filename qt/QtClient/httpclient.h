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
    void update();
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
