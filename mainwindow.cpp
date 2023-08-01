#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Timers/countdowntimer.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadWidgets();
}

CountdownTimer *cTimer;

void MainWindow::loadWidgets(){
    QWidget *widge = ui->centralwidget;
    cTimer = new CountdownTimer(widge);
    cTimer->show();
}



MainWindow::~MainWindow()
{
    delete ui;
}

