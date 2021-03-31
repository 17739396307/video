#include "mainwindow.h"

#include <QApplication>
#include <QWebEngineSettings>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("QtExamples");
       QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
       QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);


       app.setWindowIcon(QIcon(QStringLiteral(":AppLogoColor.png")));

       QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    MainWindow w;
    w.setWindowTitle("video");
    w.setWindowIcon(QIcon(":/image/icon.ico"));
    w.setSearch(argc, argv);
    w.show();
    return app.exec();
}

