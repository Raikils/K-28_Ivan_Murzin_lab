#include "addtimer.h"
#include "ui_addtimer.h"
#include "timer.h"
#include <QTime>
#include <QDate>
#include <QDateTime>
#include <QDebug>
#include <QString>
#include <QMediaPlayer>

AddTimer::AddTimer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTimer)
{
    ui->setupUi(this);
}

AddTimer::~AddTimer()
{
    delete ui;
}

void AddTimer::on_CreateButton_clicked()
{
    Timer timer;
    QDateTime x(QDate:: currentDate(),QTime:: currentTime());
    timer.setDate_start(x);
    x = x.addSecs(ui->spinBox_seconds->value() + 60 * ui->spinBox_minutes->value() + 3600 * ui->spinBox_hours->value());
    timer.setDate_end(x);
    timer.setTime_left(timer.date_start().secsTo(timer.date_end()));
    /*QMediaPlayer *music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sound/alarm1.mp3"));
    timer.setAlarm_sound(music);*/
    timer.setPath("qrc:/sound/alarm1.mp3");
    emit TimerAdded(timer);
    close();
}
