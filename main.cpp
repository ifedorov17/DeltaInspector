#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;



//    QObject * root = customApp.initializeQML()->rootObjects()[0];

//    QObject::connect(root, SIGNAL(qmlSignal(QString)),
//                         &customApp, SLOT(onTagGot(QString)));

//    QQmlApplicationEngine* Application::initializeQML()
//    {
//        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

//        return &engine;
//    }

    w.show();
    return a.exec();
}
