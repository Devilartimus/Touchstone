#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "./src/DataModel.h"
#include <QQmlEngine>
#include "./src/PlotItem.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<PlotItem>("CustomComponents", 1, 0, "PlotItem");

    DataModel model;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dataModel", &model);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
