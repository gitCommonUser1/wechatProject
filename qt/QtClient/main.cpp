#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include "httpclient.h"
#include "tablemodel.h"
#include <QSslSocket>
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    qDebug()<<"QSslSocket="<<QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    HttpClient* client = new HttpClient();
//    TableModel *model = new TableModel();
    TableModel *model = new TableModel();
    client->setModel(model);
    client->update();
//    client->test();
//    client->getPhones();
    engine.rootContext()->setContextProperty("client", client);
    engine.rootContext()->setContextProperty("tableModel", model);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
