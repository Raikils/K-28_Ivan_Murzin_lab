#ifndef ADDTIMER_H
#define ADDTIMER_H

#include <QDialog>
#include <QObject>
#include <QMediaPlayer>
#include <QString>
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

    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

    void on_pushButtonPlay_clicked();

    void on_pushButtonStop_clicked();

private:
    Ui::AddTimer *ui;
    QString played;
    bool is_played;
    QMediaPlayer *sound;
};

#endif // ADDTIMER_H
