#include "httpclient.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonParseError>
#include <QJsonObject>
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonValue>
HttpClient::HttpClient(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    //manager具有异步API，当http请求完成后，会通过finished信号进行通知
//    connect(manager,&QNetworkAccessManager::finished,this,&MyClass::replyFinished);
}

void HttpClient::update()
{
    //发送异步get请求
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("http://101.42.35.137:8080/getList")));
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply ::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    const QByteArray reply_data=reply->readAll();
   //解析json
   QJsonParseError json_error;
   QJsonDocument document=QJsonDocument::fromJson(reply_data, &json_error);
   if(json_error.error==QJsonParseError::NoError){
       if(document.isObject()){
           const QJsonObject obj=document.object();
           qDebug()<<obj;
       }
       else if(document.isArray()){
           QJsonArray array = document.array();
           QVariantList list;
           for(int i = 0;i < array.size();++i){
               StudentData data;
               data.setFire(array.at(i)["fire"].toVariant());
               data.setName(array.at(i)["name"].toVariant());
               data.setTelephone(array.at(i)["telephone"].toVariant());
               list.append(QVariant::fromValue(data));
           }
           //model->studentList = list;
       }
   }else{
       qDebug()<<"json error:"<<json_error.errorString();
   }
}
