
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Scene.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/solar_2/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    // 设置上下文环境
    solar::Scene scene; // 要给scene类设置Q_OBJECT
    engine.rootContext()->setContextProperty("topoControl",
                                             scene.topo_tree_control.get());    //这里传入的应该是普通指针
    engine.rootContext()->setContextProperty("paraControl",
                                             scene.para_tree_control.get());


    engine.load(url);

    return app.exec();
}
