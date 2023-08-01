#include "countdowntimer.h"
#include "./ui_countdowntimer.h"

CountdownTimer::CountdownTimer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CountdownTimer)
{
    ui->setupUi(this);
}

CountdownTimer::~CountdownTimer()
{
    delete ui;
}
