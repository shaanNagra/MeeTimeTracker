#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Widgets/countdowntimer.h"
#include "Widgets/savedtimerconfigs.h"


MainWindow::MainWindow(DatabaseManager &db_man, QWidget *parent) :
    QMainWindow(parent),
    db_man(db_man),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadWidgets();
}

CountdownTimer *cTimer;
SavedTimerConfigs *stcWidget;

void MainWindow::loadWidgets(){ 

    cTimer = new CountdownTimer();
    ui->ttt_wg_cont->layout()->addWidget(cTimer);
    stcWidget = new SavedTimerConfigs(db_man);
    ui->stc_wg_cont->layout()->addWidget(stcWidget);

    //timerTab->setLayout(new QGridLayout);
//    cTimer->show();
}



MainWindow::~MainWindow()
{
    delete ui;
}

