#include "mainwindow.h"
#include "mttdatabaseinf.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
//#include <QtSql/QSqlDatabase>
#include <QtDebug>
#include <QStandardPaths>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationDomain("MeeTimerTrackerTestOrg");
    app.setApplicationName("MeeTimerTracker");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "MeeTimeTracker_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (path.isEmpty()) qFatal("Cannot determine settings storage location");
    QDir d{path};
    if (d.mkpath(d.absolutePath())) {
        qDebug() << "settings in" << QDir::currentPath();
        QFile f{"settings.txt"};
        if (f.open(QIODevice::WriteOnly | QIODevice::Truncate))
            f.write("Hello, World");
    }
    MTTDatabaseInf *db = new MTTDatabaseInf();
    db->InitDatabase(path,"testDB", "testDB");
    qDebug() << "database init ran once";
    //db->InitDatabase(path);
    MainWindow w;
    w.show();
    return app.exec();
}
