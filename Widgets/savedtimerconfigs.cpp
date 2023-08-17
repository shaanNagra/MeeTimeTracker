#include "savedtimerconfigs.h"
#include "ui_savedtimerconfigs.h"

SavedTimerConfigs::SavedTimerConfigs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SavedTimerConfigs)
{
    ui->setupUi(this);
}

SavedTimerConfigs::~SavedTimerConfigs()
{
    delete ui;
}
