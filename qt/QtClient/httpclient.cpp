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
    model->clear();
    //发送异步get请求
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("https://liudi0303.cloud/getList")));
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply ::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    const QByteArray reply_data=reply->readAll();
    qDebug() << reply_data;
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
           for(int i = 0;i < array.size();++i){
               StudentData data;
               data.setFire(array.at(i)["fire"].toVariant());
               data.setName(array.at(i)["name"].toVariant());
               data.setTelephone(array.at(i)["phone"].toVariant());
               model->studentList.append(data);
               model->insert(i);
           }
       }
   }else{
       qDebug()<<"json error:"<<json_error.errorString();
   }
   qDebug() << "update";
}

void HttpClient::clear()
{
//    for(int i = 0;i < model->studentList.size();++i){
//        model->beginMoveRows(QModelIndex(),model->studentList[i],model->studentList[i]);
//    }

//    model->beginMoveRows(QModelIndex())
//    model->beginRemoveRows(QModelIndex(),index,index);
//    m_items.removeAt(index);
//    model->endRemoveRows();
//    qDebug() << "clear";
}

void HttpClient::test()
{
    //发送异步post请求
    QJsonDocument doc;
    QJsonObject jsonData;
//    jsonData.insert("access_token", "68_Ln7YZVpDz0ptjoba_Wr8QEjpUSn5u4BbIOxpVGmeP_6PT7GV60lukA3Hg8k5aOP0CGDNpzqpvKl-I02Az8pGDDATmDNI18Q6hNFZppR58KjMdT3UtNJ9p0PPD8gBZVaACARPL");     // 设置email字段
    jsonData.insert("code", "dccc968e106bf3b14cbaaba49a323f407c834dad28dbeb2543dfcacf55deb6e4");    // 设置内容字段
    doc.setObject(jsonData);
    QNetworkReply *reply = manager->post(QNetworkRequest(QUrl("https://api.weixin.qq.com/wxa/business/getuserphonenumber?access_token=68_swqkdMPCZ70eLGKvN_4Wa7xCI4kMFbnzuic2bxthDKK0PmmJnChJUFSxwa3-Mrlas6v5fFDfh3AMCejaCSW1A8KUWL7AejSeBiS3iZxtD8ZZM9cm6BvUK09b0DgKOUeABABFL")),doc.toJson());
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply ::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    const QByteArray reply_data=reply->readAll();
    qDebug() << reply_data;
   //解析json
//   QJsonParseError json_error;
//   QJsonDocument document=QJsonDocument::fromJson(reply_data, &json_error);
//   if(json_error.error==QJsonParseError::NoError){
//       if(document.isObject()){
//           const QJsonObject obj=document.object();
//           qDebug()<<obj;
//       }
//       else if(document.isArray()){
//           QJsonArray array = document.array();
//           for(int i = 0;i < array.size();++i){
//               StudentData data;
//               data.setFire(array.at(i)["fire"].toVariant());
//               data.setName(array.at(i)["name"].toVariant());
//               data.setTelephone(array.at(i)["phone"].toVariant());
//               model->studentList.append(data);
//           }
//       }
//   }else{
//       qDebug()<<"json error:"<<json_error.errorString();
//   }

    qDebug() << "update";
}

void HttpClient::getPhones()
{
    //发送异步get请求
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("https://liudi0303.cloud/phones")));
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply ::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    const QByteArray reply_data=reply->readAll();
    qDebug() << reply_data;
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
           for(int i = 0;i < array.size();++i){
               StudentData data;
               data.setTelephone(array.at(i)["phone"].toVariant());
               model->studentList.append(data);
           }
       }
   }else{
       qDebug()<<"json error:"<<json_error.errorString();
   }

   qDebug() << "update";
}

void HttpClient::remove(int index)
{
    //发送异步get请求
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("https://liudi0303.cloud/removeStudent?phone="+model->studentList[index].telephone().toString())));
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply ::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    const QByteArray reply_data=reply->readAll();
    qDebug() << reply_data;
   //解析json
   QJsonParseError json_error;
   QJsonDocument document=QJsonDocument::fromJson(reply_data, &json_error);
   if(json_error.error==QJsonParseError::NoError){
       if(document.isObject()){
           const QJsonObject obj=document.object();
           if(obj.value("protocol41") == true)
            model->remove(index);
       }
   }else{
       qDebug()<<"json error:"<<json_error.errorString();
   }
}

void HttpClient::update(int index,QString fire)
{
    //发送异步get请求
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("https://liudi0303.cloud/updateStudent?phone="+model->studentList[index].telephone().toString() + "&fire=" + fire)));
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply ::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    const QByteArray reply_data=reply->readAll();
    qDebug() << reply_data;
   //解析json
   QJsonParseError json_error;
   QJsonDocument document=QJsonDocument::fromJson(reply_data, &json_error);
   if(json_error.error==QJsonParseError::NoError){
       if(document.isObject()){
           if(document.isObject()){
               const QJsonObject obj=document.object();
               if(obj.value("protocol41") == true){
                   model->update(index,fire);
                   update();
               }
           }
       }
   }else{
       qDebug()<<"json error:"<<json_error.errorString();
   }


}

void HttpClient::newData(QString name, QString phone, QString fire)
{
    //发送异步get请求
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("https://liudi0303.cloud/newStudent?name="+name+"&fire="+fire+"&phone="+phone)));
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply ::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    const QByteArray reply_data=reply->readAll();
    qDebug() << reply_data;
   //解析json
   QJsonParseError json_error;
   QJsonDocument document=QJsonDocument::fromJson(reply_data, &json_error);
   if(json_error.error==QJsonParseError::NoError){
       if(document.isObject()){
           if(document.isObject()){
               const QJsonObject obj=document.object();
               if(obj.value("protocol41") == true)
               {
//                   StudentData data;
//                   data.setFire(fire);
//                   data.setTelephone(phone);
//                   data.setName(name);
//                   model->studentList.append(data);
                   update();
               }
           }
       }
   }else{
       qDebug()<<"json error:"<<json_error.errorString();
   }
}
