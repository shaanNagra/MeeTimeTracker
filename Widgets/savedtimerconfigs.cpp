#include "savedtimerconfigs.h"
#include "ui_savedtimerconfigs.h"
#include <QDebug>

SavedTimerConfigs::SavedTimerConfigs(DatabaseManager &db_man, QWidget *parent) :
    QWidget(parent),
    db_man(db_man),
    ui(new Ui::SavedTimerConfigs)
{
    ui->setupUi(this);

    auto pList = db_man.GetAllProject();
    for(int i=0; i<pList.count(); i++){
        qDebug() << pList[i].db_id;
        qDebug() << pList[i].name;
        qDebug() << pList[i].color;
        qDebug() << pList[i].subprojects;
    }
    QList<QString> temp_test_list = {"test1, test2, test3"};
    for (int i = 0; i < temp_test_list.size(); ++i){

    }


}

SavedTimerConfigs::~SavedTimerConfigs()
{
    delete ui;
}
