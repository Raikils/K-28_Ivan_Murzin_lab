#include "alarm.h"
#include "ui_alarm.h"
#include <QDebug>
#include <QMediaPlayer>

alarm::alarm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alarm)
{
    ui->setupUi(this);
    connect(parent,SIGNAL(Path(QString)),this,SLOT(Sound_on(QString)));
}

alarm::~alarm()
{
    delete ui;
}

void alarm::Sound_on(QString path)
{
    QMediaPlayer *music = new QMediaPlayer(this);
    music->setMedia(QUrl(path));
    music->play();
}

void alarm::on_pushButton_Snooze_clicked()
{

}

void alarm::on_pushButton_Dismiss_clicked()
{

}
