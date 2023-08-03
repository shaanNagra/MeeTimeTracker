#ifndef COUNTDOWNTIMER_H
#define COUNTDOWNTIMER_H

#include <QTime>
#include <QTimer>
#include <QWidget>

namespace Ui {
class CountdownTimer;
}

class CountdownTimer : public QWidget
{
    Q_OBJECT

public:
    explicit CountdownTimer(QWidget *parent = nullptr);
    ~CountdownTimer();

    void loadConfig();
private slots:
    void on_ct_PlayPauseButton_clicked();

    void on_ct_HourIn_valueChanged(int arg1);

    void on_ct_MinsIn_valueChanged(int arg1);

    void on_ct_SecsIn_valueChanged(int arg1);

    void on_ct_EndButton_clicked();

private:
    Ui::CountdownTimer *ui;

    int c_hours;
    int c_minutes;
    int c_seconds;

    enum cTimerState{
        Ready,
        Paused,
        Running,
        Completed,
    };

    enum cTimerState c_timer_state;

    QTimer *c_ticker;
    QTime c_set_duration;
    QTime c_duration;
    QTime c_zero;

    void inputTimeUpdated();
    void updateDuration();
    void timerTick();

    void startTimer();
    void pauseTimer();
    void resumeTimer();
    void resetTimer();
    void okTimer();

    void timeElapsed();

    void startAlarm();
    void stopAlarm();

    bool isValidTimeInput();
    void timeInputEnabled(bool enabled);
};

#endif // COUNTDOWNTIMER_H
