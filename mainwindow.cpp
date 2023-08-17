#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Widgets/countdowntimer.h"
#include "Widgets/savedtimerconfigs.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadWidgets();
}

CountdownTimer *cTimer;
SavedTimerConfigs *stcWidget;

void MainWindow::loadWidgets(){ 

    cTimer = new CountdownTimer();
    ui->ttt_wg_cont->layout()->addWidget(cTimer);
    stcWidget = new SavedTimerConfigs();
    ui->stc_wg_cont->layout()->addWidget(stcWidget);

    //timerTab->setLayout(new QGridLayout);
//    cTimer->show();
}



MainWindow::~MainWindow()
{
    delete ui;
}

