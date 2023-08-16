#include "./mttdatabaseinf.h"
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QFile>

MTTDatabaseInf::MTTDatabaseInf()
{
    db_name = "testDB";
    db_hostname = "testHost";
}

bool MTTDatabaseInf::InitDatabase(const QString &db_nam){

    QSqlDatabase db = QSqlDatabase::database("testConnection");
    if(!db.isValid()){
        qDebug() << "BADDDDno existing db need to initilisation";
        db = QSqlDatabase::addDatabase("QSQLITE", "testConnection");
        db.setDatabaseName("testDB");
        qDebug() << db.isValid();
        qDebug() << db.connectionNames();
        if(!db.open()){

        }
        QSqlQuery query(db);
        query.prepare("CREATE TABLE testTeam");
        if(query.exec()){
            qDebug() << "created test table";
        }
        db.close();
    } else {
        qDebug() << "db exists no need for initilisation";
    }
    return true;
}

bool MTTDatabaseInf::InitDatabase(const QString &db_path,
    const QString &db_name, const QString conn_name){

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", conn_name);

    db.setDatabaseName(db_path+"/"+db_name);
    if(!db.open()){
        qDebug() << "failed to open database";
        return false;
    }

    if(0 == db.tables(QSql::Tables).length()){
        qDebug() << "new database created: creating tables";
        MTTDatabaseInf::CreateDatabaseStructre(db);
    }

    return true;
}

bool MTTDatabaseInf::CreateDatabaseStructre(const QSqlDatabase &db){
    if(!db.isOpen()){
        qDebug() << "database not open to create tables";
        return false;
    }
    QSqlQuery query;
    /* Timer Configuration Table*/
    query.exec("CREATE TABLE TimerConfig ("
        "timer_config_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "time_type TEXT NOT NULL,"
        "time TEXT );"
    );
    /* Projects Category Table*/
    query.exec("CREATE TABLE Project ("
        "project_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT,"
        "color INTEGER );"
    );
    /* Subprojects Category Table*/
    query.exec("CREATE TABLE Subproject ("
        "subproject_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "project_id INTEGER,"
        "is_default NUMERIC DEFAULT (0),"
        "name TEXT,"
        "CONSTRAINT Subproject_FK FOREIGN KEY (project_id)"
            "REFERENCES Project(project_id)"
    ");");
    /**/
    query.exec("CREATE TABLE Tag ("
        "name TEXT,"
        "tag_id INTEGER PRIMARY KEY AUTOINCREMENT"
    ");");
    /**/
    query.exec("CREATE TABLE SavedTimer ("
        "name TEXT,"
        "saved_timer_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "description INTEGER,"
        "subproject_id INTEGER,"
        "timer_config_id INTEGER,"
        "CONSTRAINT SavedTimer_FK FOREIGN KEY (subproject_id)"
            "REFERENCES Subproject(subproject_id),"
        "CONSTRAINT SavedTimer_Timer_FK FOREIGN KEY (timer_config_id)"
            "REFERENCES TimerConfig(timer_config_id)"
    ");");
    /**/
    query.exec("CREATE TABLE LoggedTime ("
        "name TEXT,"
        "logged_time_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "description INTEGER,subproject_id INTEGER,"
        "time_type TEXT NOT NULL, "
        "CONSTRAINT LoggedTime_FK FOREIGN KEY (subproject_id) "
               "REFERENCES Subproject(subproject_id)"
    ");");
    /*Recorded Times*/
    query.exec("CREATE TABLE RecordedTime ("
        "recorded_time_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "logged_time_id INTEGER,"
        "start_time TEXT NOT NULL,"
        "end_time TEXT NOT NULL,"
        "CONSTRAINT RecordedTime_FK FOREIGN KEY (logged_time_id) "
               "REFERENCES LoggedTime(logged_time_id)"
    ");");
    /*Saved Timers and Tag Relationship Table*/
    query.exec("CREATE TABLE [SavedTimerTag] ("
        "[saved_timer_ID] INTEGER NOT NULL,"
        "[tag_id] INTEGER NOT NULL,"
        "CONSTRAINT [PK_saved_timer_tag] PRIMARY KEY"
            "([saved_timer_id], [tag_id]),"
        "FOREIGN KEY ([saved_timer_id])"
            "REFERENCES [SavedTimer] ([saved_timer_id])"
            "ON DELETE NO ACTION ON UPDATE NO ACTION,"
        "FOREIGN KEY ([tag_id]) "
            "REFERENCES [Tag] ([tag_id])"
            "ON DELETE NO ACTION ON UPDATE NO ACTION"
    ");");
    /*INDEX for Tags*/
    query.exec("CREATE UNIQUE INDEX [IPK_saved_timer_tag] ON [SavedTimerTag]("
        "[saved_timer_id], [tag_id]"
    ");");
    query.exec("CREATE INDEX [IFK_saved_timer_tag_tag] ON [SavedTimerTag] ("
        "[tag_id]"
    ");");

    qDebug() << db.tables();
    return true;
}
//    auto db = QSqlDatabase::addDatabase("QSQLITE");
//    QSqlDatabase db;
//    db = QSqlDatabase::database(db_name);
//    qDebug() << db.isValid();
//    db = QSqlDatabase::addDatabase("QSQLITE", db_name);
//    //db.setDatabaseName(db_name);

//    //db = QSqlDatabase::database(db_name);
//    qDebug() << db.connectionNames();
//    qDebug() << db.isValid();
//    bool opened = db.open();
//    if(!opened){
//        qDebug() << "failed to open";
//    }
//    qDebug() << "qdebug out check";

//    db.close();

//    QSqlDatabase dbs;
//    qDebug() << dbs.isValid();
//    dbs = QSqlDatabase::database(db_name);
//    qDebug() << dbs.isValid();
//    return opened;

