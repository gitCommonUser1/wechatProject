#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonParseError>
#include <QJsonObject>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    QNetworkAccessManager *manager = new QNetworkAccessManager(&app);
    //manager具有异步API，当http请求完成后，会通过finished信号进行通知
//    connect(manager,&QNetworkAccessManager::finished,&app,&MyClass::replyFinished);
    //发送异步get请求
    QNetworkRequest request;
    request.setUrl(QUrl("http://101.42.35.137:8080/getList"));
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



    return app.exec();
}
