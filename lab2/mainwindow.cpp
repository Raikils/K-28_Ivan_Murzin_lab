#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addtimer.h"
#include <QTreeWidgetItem>
#include <QTime>
#include <QDate>
#include <QDateTime>
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QMessageBox>
#include <QMediaPlayer>
#include "timer.h"
#include "alarm.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *time = new QTimer(this);
    connect(time,SIGNAL(timeout()),this,SLOT(Timer_Action()));
    time->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Timer_Action()
{
    for(int i = 0; i < timers.size(); i++) {
        if (timers[i].is_active()) {
        int hour, minute, second;
        QDateTime x(QDate:: currentDate(),QTime:: currentTime());
        hour = x.secsTo(timers[i].date_end()) / 3600;
        minute = (x.secsTo(timers[i].date_end()) % 3600) / 60;
        second = (x.secsTo(timers[i].date_end()) % 3600) % 60;
        if (hour + minute + second <= 0) {
            timers[i].setIs_active(false);
            timer_finish(timers[i]);
        }
        timers[i].treawidgetitem()->setText(0,QString::number(hour) + ':' + QString::number(minute) + ':' + QString::number(second));
        }
    }
}


void MainWindow::on_AddButton_clicked()
{
    AddTimer *addwindow;
    addwindow = new AddTimer(this);
    connect(addwindow,SIGNAL(TimerAdded(Timer)),
            this,SLOT(Add_Timer(Timer)));
    addwindow->show();
}

void MainWindow::Add_Timer(Timer timer)
{
    timer.setTreawidgetitem(new QTreeWidgetItem(ui->treeWidget));
    timer.treawidgetitem()->setText(1,timer.date_start().toString());
    timer.treawidgetitem()->setText(2,timer.date_end().toString());
    timer.setIs_active(true);
    int hour, minute, second;
    hour = timer.date_start().secsTo(timer.date_end()) / 3600;
    minute = (timer.date_start().secsTo(timer.date_end()) % 3600) / 60;
    second = (timer.date_start().secsTo(timer.date_end()) % 3600) % 60;
    timer.treawidgetitem()->setText(0,QString::number(hour) + ':' + QString::number(minute) + ':' + QString::number(second));
    /*QMessageBox* msgBox = new QMessageBox( this );
       msgBox->setAttribute( Qt::WA_DeleteOnClose );
       QPushButton *okButton = msgBox->addButton(QMessageBox::Ok);
       msgBox->setWindowTitle( tr("Error") );
       msgBox->setText( tr("Something happened!") );
       msgBox->setModal( false );
    timer.setDel_button(okButton);
    timer.setFinish_message(msgBox);
    timer.q = true;*/
    timers.push_back(timer);
}

void MainWindow::timer_finish(Timer timer)
{
    alarm *alarmwindow = new alarm(this);
    alarmwindow->show();
    emit Path(timer.getPath());
    //timer.finish_message()->show();
    /*QMediaPlayer *music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sound/alarm1.mp3"));
    music->play();
    QMessageBox* msgBox = new QMessageBox( this );
       msgBox->setAttribute( Qt::WA_DeleteOnClose );
       //msgBox->setStandardButtons( QMessageBox::Ok );
       QPushButton *abortButton = msgBox->addButton(QMessageBox::Ok);
       msgBox->setWindowTitle( tr("Error") );
       msgBox->setText( tr("Something happened!") );
       msgBox->setModal( false );
       msgBox->show();
    if (msgBox->clickedButton() == abortButton) qDebug() << "ewf";*/
}
