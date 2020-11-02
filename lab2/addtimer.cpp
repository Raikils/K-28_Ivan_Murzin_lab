#include "addtimer.h"
#include "ui_addtimer.h"
#include "timer.h"
#include <QTime>
#include <QDate>
#include <QDateTime>
#include <QDebug>
#include <QString>
#include <QMediaPlayer>
#include <QPixmap>
#include <QIcon>

AddTimer::AddTimer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTimer)
{
    ui->setupUi(this);
    ui->comboBoxSound->addItem("alarm1");
    ui->comboBoxSound->addItem("alarm2");
    ui->comboBoxSound->addItem("alarm3");
    ui->comboBoxSound->addItem("alarm4");
    played = "alarm1";
    is_played = false;
    QPixmap start(":/res/icon/start.png");
    //int h = ui->pushButtonPlay->height();
    //int w = ui->pushButtonStop->width();
    QIcon ButtonIcon(start);
    ui->pushButtonPlay->setIcon(ButtonIcon);
    ui->pushButtonPlay->setIconSize(start.rect().size());
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
    if (ui->radioButton_2->isChecked()) {
    x = x.addSecs(ui->spinBox_seconds->value() + 60 * ui->spinBox_minutes->value() + 3600 * ui->spinBox_hours->value());
    timer.setDate_end(x);
    timer.setIs_timer(true);
    }
    else {
        x.setDate(ui->calendarWidget->selectedDate());
        x.setTime(ui->timeEdit_alarm->time());
        timer.setDate_end(x);
        timer.setIs_timer(false);
    }
    timer.setTime_left(timer.date_start().secsTo(timer.date_end()));
    if (ui->comboBoxSound->currentText() == "alarm1") timer.setPath("qrc:/sound/alarm1.mp3");
    if (ui->comboBoxSound->currentText() == "alarm2") timer.setPath("qrc:/sound/alarm2.mp3");
    if (ui->comboBoxSound->currentText() == "alarm3") timer.setPath("qrc:/sound/alarm3.mp3");
    if (ui->comboBoxSound->currentText() == "alarm4") timer.setPath("qrc:/sound/alarm4.mp3");
    timer.setShould_delete(false);
    timer.setIs_active(true);
    timer.setName(ui->lineEdit->text());
    emit TimerAdded(timer);
    close();
}

void AddTimer::on_radioButton_2_clicked()
{
    ui->calendarWidget->setEnabled(false);
    ui->label_time->setEnabled(false);
    ui->timeEdit_alarm->setEnabled(false);

    ui->label_hours->setEnabled(true);
    ui->label_minutes->setEnabled(true);
    ui->label_seconds->setEnabled(true);
    ui->spinBox_hours->setEnabled(true);
    ui->spinBox_minutes->setEnabled(true);
    ui->spinBox_seconds->setEnabled(true);
}

void AddTimer::on_radioButton_clicked()
{
    ui->label_hours->setEnabled(false);
    ui->label_minutes->setEnabled(false);
    ui->label_seconds->setEnabled(false);
    ui->spinBox_hours->setEnabled(false);
    ui->spinBox_minutes->setEnabled(false);
    ui->spinBox_seconds->setEnabled(false);

    ui->calendarWidget->setEnabled(true);
    ui->label_time->setEnabled(true);
    ui->timeEdit_alarm->setEnabled(true);
}

void AddTimer::on_pushButtonPlay_clicked()
{
    if (!is_played) {
    sound = new QMediaPlayer(this);
    //sound->setMedia(QUrl("qrc:/sound/alarm1.mp3");
    if (ui->comboBoxSound->currentText() == "alarm1") sound->setMedia(QUrl("qrc:/sound/alarm1.mp3"));
    if (ui->comboBoxSound->currentText() == "alarm2") sound->setMedia(QUrl("qrc:/sound/alarm2.mp3"));
    if (ui->comboBoxSound->currentText() == "alarm3") sound->setMedia(QUrl("qrc:/sound/alarm3.mp3"));
    if (ui->comboBoxSound->currentText() == "alarm4") sound->setMedia(QUrl("qrc:/sound/alarm4.mp3"));
    played = ui->comboBoxSound->currentText();
    sound->play();
    is_played = true;
    } else {
        if (played == ui->comboBoxSound->currentText()) return;
        sound->stop();
        delete sound;
        sound = new QMediaPlayer(this);
        if (ui->comboBoxSound->currentText() == "alarm1") sound->setMedia(QUrl("qrc:/sound/alarm1.mp3"));
        if (ui->comboBoxSound->currentText() == "alarm2") sound->setMedia(QUrl("qrc:/sound/alarm2.mp3"));
        if (ui->comboBoxSound->currentText() == "alarm3") sound->setMedia(QUrl("qrc:/sound/alarm3.mp3"));
        if (ui->comboBoxSound->currentText() == "alarm4") sound->setMedia(QUrl("qrc:/sound/alarm4.mp3"));
        played = ui->comboBoxSound->currentText();
        sound->play();
    }
}

void AddTimer::on_pushButtonStop_clicked()
{
    sound->stop();
    delete sound;
    is_played = false;
}
