#ifndef COUNTDOWNTIMER_H
#define COUNTDOWNTIMER_H

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

private:
    Ui::CountdownTimer *ui;
};

#endif // COUNTDOWNTIMER_H
