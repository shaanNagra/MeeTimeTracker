#ifndef SAVEDTIMERCONFIGS_H
#define SAVEDTIMERCONFIGS_H

#include <QWidget>

namespace Ui {
class SavedTimerConfigs;
}

class SavedTimerConfigs : public QWidget
{
    Q_OBJECT

public:
    explicit SavedTimerConfigs(QWidget *parent = nullptr);
    ~SavedTimerConfigs();

private:
    Ui::SavedTimerConfigs *ui;
};

#endif // SAVEDTIMERCONFIGS_H
