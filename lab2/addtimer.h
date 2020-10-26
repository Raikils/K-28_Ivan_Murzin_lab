#ifndef ADDTIMER_H
#define ADDTIMER_H

#include <QDialog>
#include <QObject>
#include "timer.h"

namespace Ui {
class AddTimer;
}

class AddTimer : public QDialog
{
    Q_OBJECT

public:
    explicit AddTimer(QWidget *parent = nullptr);
    ~AddTimer();

signals:
    void TimerAdded(Timer timer);
    void test();

private slots:
    void on_CreateButton_clicked();

private:
    Ui::AddTimer *ui;
};

#endif // ADDTIMER_H
