#include "alarm.h"
#include "ui_alarm.h"
#include <QDebug>
#include <QMediaPlayer>

alarm::alarm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alarm)
{
    ui->setupUi(this);
    sound = new QMediaPlayer(this);
    connect(parent,SIGNAL(Path(QString, int, QString)),this,SLOT(Sound_on(QString, int, QString)));
}

alarm::~alarm()
{
    delete ui;
}

void alarm::Sound_on(QString path, int i, QString name)
{
    sound->setMedia(QUrl(path));
    sound->play();
    iterator = i;
    ui->label->setText(name);
}

void alarm::on_pushButton_Snooze_clicked()
{
    sound->stop();
    delete sound;
    close();
    emit Snooze(iterator);
}

void alarm::on_pushButton_Dismiss_clicked()
{
    sound->stop();
    delete sound;
    close();
    emit Dismiss(iterator);
}

void alarm::on_pushButton_Stop_clicked()
{
    sound->stop();
    delete sound;
    close();
    emit Stop(iterator);
}
