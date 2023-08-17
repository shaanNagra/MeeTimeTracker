#include "databasemanager.h"
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlError>
#include <QFile>
//#include "customstructs.cpp"

DatabaseManager::DatabaseManager(QString db_path, QString db_name,
    QString db_conn_name){

    this->db_name = db_name;
    this->db_path = db_path;
    this->db_conn_name = db_conn_name;
}


bool DatabaseManager::InitDatabase(){

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", db_conn_name);

    db.setDatabaseName(db_path+"/"+db_name);
    bool ok = db.open();
    if(!ok){
        qDebug() << ok << db_conn_name;
        qDebug() << "failed to open database";
        return false;
    }else if(0 == db.tables(QSql::Tables).length()){
        qDebug() << "new database created: creating tables";
        DatabaseManager::CreateDatabaseStructre(db);
    }
    return true;
}

QList<projectStruct> DatabaseManager::GetAllProject(){

    QList<projectStruct> projectList;
    auto db = QSqlDatabase::database(db_conn_name);
    QSqlQuery query(db);
    query.prepare("SELECT `project_id`, `name`, `color` FROM `Project`");
    if(query.exec()){
        while(query.next()){
            projectStruct new_project;
            new_project.db_id = query.value(0).toInt();
            new_project.name = query.value(1).toString();
            new_project.color = query.value(2).toInt();
            new_project.subprojects = QSet<QString>();
            projectList.append(new_project);
        }
    }else{
        return projectList;
    }
    query.prepare(
        "SELECT `name` FROM `Subproject` WHERE `project_id` = :project_id"
    );
    for(int i=0; i<projectList.count(); i++){
        query.bindValue(":project_id",projectList[i].db_id);
        if(query.exec()){
            while(query.next()){
                projectList[i].subprojects.insert(query.value(0).toString());
            }
        }

    }

    return projectList;

}

bool DatabaseManager::AddProject(const QString &name, const int &color){
    auto db = QSqlDatabase::database(db_conn_name);

    if(db.transaction()){
        QSqlQuery query(db);

        query.prepare(
            "INSERT INTO 'Project'('project_id','name','color')"
            "VALUES (NULL, :name, :color)"
        );
        query.bindValue(":name", name);
        query.bindValue(":color", color);
        if(!query.exec()){
            qDebug() << "AddProject error: " << query.lastError();
            db.rollback();
            return false;
        }

        auto ppk = query.lastInsertId().toInt();
        query.prepare(
            "INSERT INTO 'Subproject'"
            "('subproject_id', 'project_id', 'is_default', 'name') "
            "VALUES (NULL, :project_id, :is_default, :name)"
        );
        query.bindValue(":project_id", ppk);
        query.bindValue(":is_default", 1);
        query.bindValue(":name", "UnSLpp");
        if(!query.exec()){
            db.rollback();
            return false;
        }
        if(!db.commit()){
            qDebug() << "Failed to commit, Rollback";
            db.rollback();

        }else{
            qDebug() << "Transaction complete, added new project";
            return true;

        }
    }else{
        qDebug() << "Failed to initilise transaction";
    }
    return false;
}

bool DatabaseManager::AddSubproject(const QString &name,
    const QString &project_name){
    return AddSubproject(name, project_name, false);
}

bool DatabaseManager::AddSubproject(const QString &name,
    const QString &project_name, const bool &is_default){

    int is_de = 0;
    if(is_default) is_de = 1;

    auto db = QSqlDatabase::database(db_conn_name);
    if(db.transaction()){
        QSqlQuery query(db);

        query.prepare(
        "INSERT INTO Subproject(subproject_id,is_default,name,project_id) "
        "VALUES(NULL, :is_default, :name, "
            "(SELECT project_id FROM Project "
            "WHERE name = :project_name LIMIT 1)"
        ")"
        );
        query.bindValue(":name",name);
        query.bindValue(":is_default",is_de);
        query.bindValue(":project_name", project_name);
        if(!query.exec()){
            db.rollback();
            return false;
        }

        if(!db.commit()){
            qDebug() << "Failed to commit";
            db.rollback();
        }else{
            qDebug() << "Transaction complete: added new subproject";
            return true;
        }
    }else{
        qDebug() << "TS";
    }
    return false;
}

bool DatabaseManager::CreateDefaultData(const QSqlDatabase &db){
    if(!db.isOpen()){
        qDebug() << "could not open database to add template data";
        return false;
    }
    QSqlQuery *query = new QSqlQuery(QSqlDatabase::database(db_conn_name));
    query->exec(
    );

    return false;
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


bool DatabaseManager::CreateDatabaseStructre(const QSqlDatabase &db){
    if(!db.isOpen()){
        qDebug() << "database not open to create tables";
        return false;
    }
    QSqlQuery *query = new QSqlQuery(db);
    /* Timer Configuration Table*/
    query->exec("CREATE TABLE TimerConfig ("
        "timer_config_id	INTEGER PRIMARY KEY AUTOINCREMENT,"
        "time_type 			TEXT ,"
        "time 				TEXT );"
    );
    /* Projects Category Table*/
    query->exec("CREATE TABLE Project ("
        "project_id 	INTEGER 	PRIMARY KEY AUTOINCREMENT,"
        "name 			TEXT 		NOT NULL UNIQUE,"
        "color 			INTEGER );"
    );
    /* Subprojects Category Table*/
    query->exec("CREATE TABLE Subproject ("
        "subproject_id 	INTEGER 	PRIMARY KEY AUTOINCREMENT,"
        "project_id 	INTEGER		NOT NULL,"
        "is_default 	NUMERIC 	DEFAULT (0),"
        "name 			TEXT,"
        "UNIQUE(name,project_id)"
        "CONSTRAINT Subproject_FK FOREIGN KEY (project_id)"
            "REFERENCES Project(project_id)"
    ");");
    /**/
    query->exec("CREATE TABLE Tag ("
        "name 		TEXT,"
        "tag_id 	INTEGER 	PRIMARY KEY AUTOINCREMENT"
    ");");
    /**/
    query->exec("CREATE TABLE SavedTimer ("
        "name 				TEXT,"
        "saved_timer_id 	INTEGER 	PRIMARY KEY AUTOINCREMENT,"
        "description 		INTEGER,"
        "subproject_id 		INTEGER,"
        "timer_config_id 	INTEGER,"
        "CONSTRAINT SavedTimer_FK FOREIGN KEY (subproject_id)"
            "REFERENCES Subproject(subproject_id),"
        "CONSTRAINT SavedTimer_Timer_FK FOREIGN KEY (timer_config_id)"
            "REFERENCES TimerConfig(timer_config_id)"
    ");");
    /**/
    query->exec("CREATE TABLE LoggedTime ("
        "name 				TEXT,"
        "logged_time_id 	INTEGER 	PRIMARY KEY AUTOINCREMENT,"
        "description 		INTEGER,"
        "subproject_id 		INTEGER,"
        "time_type 			TEXT 		NOT NULL, "
        "CONSTRAINT LoggedTime_FK FOREIGN KEY (subproject_id) "
               "REFERENCES Subproject(subproject_id)"
    ");");
    /*Recorded Times*/
    query->exec("CREATE TABLE RecordedTime ("
        "recorded_time_id 	INTEGER 	PRIMARY KEY AUTOINCREMENT,"
        "logged_time_id 	INTEGER,"
        "start_time 		TEXT 		NOT NULL,"
        "end_time 			TEXT 		NOT NULL,"
        "CONSTRAINT RecordedTime_FK FOREIGN KEY (logged_time_id) "
               "REFERENCES LoggedTime(logged_time_id)"
    ");");
    /*Saved Timers and Tag Relationship Table*/
    query->exec("CREATE TABLE [SavedTimerTag] ("
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
    query->exec("CREATE UNIQUE INDEX [IPK_saved_timer_tag] ON [SavedTimerTag]("
        "[saved_timer_id], [tag_id]"
    ");");
    query->exec("CREATE INDEX [IFK_saved_timer_tag_tag] ON [SavedTimerTag] ("
        "[tag_id]"
    ");");

    qDebug() << db.tables();
    return true;
}
