#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>
#include "customstructs.h"
#include <QList>

class DatabaseManager
{
public:
    DatabaseManager(QString db_path, QString db_name, QString db_conn_name);

    bool InitDatabase();

    bool AddProject(const QString &name, const int &color);
    bool UpdateProject();
    bool DeleteProject();
    bool ProjectExists();
    QList<projectStruct> GetAllProject();

    bool AddSubproject(const QString &name, const QString &project_name);
    bool UpdateSubproject();
    bool DeleteSubproject();
    bool SubprojectExists();

    bool AddSavedTimer();
    bool UpdateSavedTimer();
    bool DeleteSavedTimer();
    bool SavedTimerExists();
    bool GetSavedTimers();

private:

    QString db_name;
    QString db_path;
    QString db_conn_name;
    bool CreateDatabaseStructre(const QSqlDatabase &db);
    bool CreateDefaultData(const QSqlDatabase &db);
    bool AddSubproject(const QString &name,
        const QString &project_name, const bool &is_default);
};

#endif // DATABASEMANAGER_H
