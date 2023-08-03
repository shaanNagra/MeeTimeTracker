#include "countdowntimer.h"
#include "./ui_countdowntimer.h"


CountdownTimer::CountdownTimer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CountdownTimer)
{
    ui->setupUi(this);
    c_ticker = new QTimer();
    c_ticker->setInterval(1000);
    connect(c_ticker, &QTimer::timeout, [&](){
        timerTick();
    });
    c_duration.setHMS(0,0,0);
    c_zero.setHMS(0,0,0);
    c_timer_state = Ready;
    inputTimeUpdated();
}

CountdownTimer::~CountdownTimer()
{
    delete ui;
}

void CountdownTimer::timerTick(){
    if(c_zero == c_duration){
        timeElapsed();
    } else {
        c_duration = c_duration.addSecs(-1);
        updateDuration();
    }
}

void CountdownTimer::timeElapsed(){
    ui->ct_PlayPauseButton->setText("Ok");
    ui->ct_EndButton->setEnabled(false);

    startAlarm();
    c_ticker->stop();
    c_timer_state = Completed;
}

void CountdownTimer::startTimer(){
    ui->ct_PlayPauseButton->setText("Pause");
    ui->ct_EndButton->setEnabled(true);
    timeInputEnabled(false);

    c_ticker->start();
    c_timer_state = Running;
}

void CountdownTimer::pauseTimer(){
    ui->ct_PlayPauseButton->setText("Resume");

    c_ticker->stop();
    c_timer_state = Paused;
}

void CountdownTimer::resumeTimer(){
    ui->ct_PlayPauseButton->setText("Pause");

    c_ticker->start();
    c_timer_state = Running;
}

void CountdownTimer::resetTimer(){
    ui->ct_PlayPauseButton->setText("Start");
    ui->ct_EndButton->setEnabled(false);

    timeInputEnabled(true);
    inputTimeUpdated();
    c_ticker->stop();
    c_timer_state = Ready;

}

void CountdownTimer::timeInputEnabled(bool enabled){
    ui->ct_HourIn->setEnabled(enabled);
    ui->ct_MinsIn->setEnabled(enabled);
    ui->ct_SecsIn->setEnabled(enabled);
}

void CountdownTimer::startAlarm(){
    ui->ct_lcd->display("DohE");
}

void CountdownTimer::stopAlarm(){
    ui->ct_lcd->display("4A4");
}

void CountdownTimer::loadConfig(){

}

void CountdownTimer::inputTimeUpdated(){
    c_duration.setHMS(
        ui->ct_HourIn->value(),
        ui->ct_MinsIn->value(),
        ui->ct_SecsIn->value()
    );
    updateDuration();
    ui->ct_PlayPauseButton->setEnabled(isValidTimeInput());
}

void CountdownTimer::updateDuration(){
    ui->ct_lcd->display(c_duration.toString("hh:mm:ss"));
}

bool CountdownTimer::isValidTimeInput(){
    if(Ready == c_timer_state){
        if(c_zero == c_duration){
            return false;
        } else {
            return true;
        }
    }
    return true;
}

void CountdownTimer::on_ct_PlayPauseButton_clicked()
{
    switch(c_timer_state){
        case Ready:
            startTimer();
            break;
        case Paused:
            resumeTimer();
            break;
        case Running:
            pauseTimer();
            break;
        case Completed:
            resetTimer();
            stopAlarm();
            break;
    }
}


void CountdownTimer::on_ct_HourIn_valueChanged(int arg1)
{
    inputTimeUpdated();
}


void CountdownTimer::on_ct_MinsIn_valueChanged(int arg1)
{
    inputTimeUpdated();
}


void CountdownTimer::on_ct_SecsIn_valueChanged(int arg1)
{
    inputTimeUpdated();
}


void CountdownTimer::on_ct_EndButton_clicked()
{
    resetTimer();
}

