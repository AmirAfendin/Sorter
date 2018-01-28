#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QDebug>

#include "sortermodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    SorterModel sorterModel;

    QQuickStyle::setStyle("Fusion");

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("sorterModel", &sorterModel);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
