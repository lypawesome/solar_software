#include "Scene.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <iostream>
int main(int argc, char* argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    //std::vector<int> a;
    //std::cout << a[-1] << std::endl;
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/solar_1/Main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl)
        {
            if (!obj && url == objUrl)
            {
                QCoreApplication::exit(-1);
            }
        },
        Qt::QueuedConnection);

    // 设置上下文环境
    solar::Scene scene; // 要给scene类设置Q_OBJECT
    engine.rootContext()->setContextProperty("topoControl",
                                             scene.topoTreeViewController);
    // engine.rootContext()->setContextProperty("paraControl",QVariant::fromValue(scene.paraTreeViewController));
    engine.rootContext()->setContextProperty("sunParaControl",
                                             scene.paraTreeViewController[0]);

    qDebug() << scene.paraTreeViewController[0];
    engine.load(url);

    return QGuiApplication::exec();
}
