#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include "httpclient.h"
#include "tablemodel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    HttpClient* client = new HttpClient();
    TableModel *model = new TableModel();
    client->setModel(model);
    client->update();
    engine.rootContext()->setContextProperty("client", client);
    engine.rootContext()->setContextProperty("tableModel", model);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

<<<<<<< HEAD

    QNetworkAccessManager *manager = new QNetworkAccessManager(&app);
    //manager具有异步API，当http请求完成后，会通过finished信号进行通知
//    connect(manager,&QNetworkAccessManager::finished,&app,&MyClass::replyFinished);
    //发送异步get请求
    QNetworkRequest request;
    request.setUrl(QUrl("https://liudi0303.cloud/getList"));
    request.setRawHeader("Content-Type","application/json");
    QNetworkReply *reply = manager->get(request);
    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply ::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    //处理reply信息
    auto replyData = reply->readAll();
    qDebug() << replyData;
//    QJsonParseError json_error;
//    QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData, &json_error));
//    if(json_error.error != QJsonParseError::NoError)
//    {
//        return -1;
//    }
//    QJsonObject rootObj = jsonDoc.object();
//    QString codeStr = rootObj.value("phone").toString();
//    qDebug() << codeStr;



=======
>>>>>>> 7bc85bfffd38e34d3b90d820517d7228a9874319
    return app.exec();
}
