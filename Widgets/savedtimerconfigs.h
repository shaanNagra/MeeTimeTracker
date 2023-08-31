#ifndef SAVEDTIMERCONFIGS_H
#define SAVEDTIMERCONFIGS_H

#include <QWidget>
#include <QList>
#include "../customstructs.h"
#include "../databasemanager.h"

namespace Ui {
class SavedTimerConfigs;
}

class SavedTimerConfigs : public QWidget
{
    Q_OBJECT

public:
    explicit SavedTimerConfigs(DatabaseManager &db_man, QWidget *parent = nullptr);
    ~SavedTimerConfigs();

private:
    Ui::SavedTimerConfigs *ui;

    DatabaseManager &db_man;
    QList<ProjectStruct> projectList;

};

#endif // SAVEDTIMERCONFIGS_H
