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
#include <QWinTaskbarButton>
#include <QWinTaskbarProgress>
#include <QFile>
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *time = new QTimer(this);
    connect(time,SIGNAL(timeout()),this,SLOT(Timer_Action()));
    time->start(1000);
    QStringList colum;
    colum << "A/T" << "Name" << "Time" << "Active" << "End";
    ui->treeWidget->setHeaderLabels(colum);
    ui->treeWidget->setColumnWidth(0,15);
    ui->treeWidget->setColumnWidth(1,120);
    ui->treeWidget->setColumnWidth(2,100);
    ui->treeWidget->setColumnWidth(3,60);
    ui->treeWidget->setColumnWidth(4,200);
    QFile f("timers.dat");
    f.open(QIODevice::ReadOnly);
    QDataStream in(&f);
    while(!in.atEnd()) {
        Timer timer;
        in >> timer;
        Add_Timer(timer);
    }
    QFile g("disturb.dat");
    g.open(QIODevice::ReadOnly);
    QDataStream ing(&g);
    bool q;
    ing >> q;
    if (q) {
        ui->checkBox->setChecked(true);
        QTime t;
        ing >> t;
        ui->timeEditFrom->setTime(t);
        ing >> t;
        ui->timeEditTo->setTime(t);
    }
}

MainWindow::~MainWindow()
{
    QFile f("timers.dat");
    f.open(QIODevice::WriteOnly);
    QDataStream out(&f);
    for (const auto &k : timers) {
        out << Timer(k);
    }
    QFile g("disturb.dat");
    g.open(QIODevice::WriteOnly);
    QDataStream outg(&g);
    if (ui->checkBox->isChecked()) {
        outg << bool(true) << QTime(ui->timeEditFrom->time()) << QTime(ui->timeEditTo->time());
    }
    else outg << bool(false);
    delete ui;
}

void MainWindow::Timer_Action()
{
    QDateTime y(QDate:: currentDate(),QTime:: currentTime());
    int dtmin = -1;
    int min = 2147483647;
    for(int i = 0; i < timers.size(); i++) {
        if(timers[i].getShould_delete()) { timers.erase(timers.begin() + i); i--;}
        else if (timers[i].is_active()) {
        int hour, minute, second;
        QDateTime x(QDate:: currentDate(),QTime:: currentTime());
        hour = x.secsTo(timers[i].date_end()) / 3600;
        minute = (x.secsTo(timers[i].date_end()) % 3600) / 60;
        second = (x.secsTo(timers[i].date_end()) % 3600) % 60;
        if (x.secsTo(timers[i].date_end()) < min) {min = x.secsTo(timers[i].date_end()); dtmin = i; }
        if (hour + minute + second <= 0) {
            if (!ui->checkBox->isChecked()) {
            timers[i].setIs_active(false);
            timers[i].treawidgetitem()->setText(3,"-");
            timer_finish(timers[i], i);
            }
            else {
                QTime t(QTime::currentTime());
                if (t.secsTo(ui->timeEditFrom->time()) < 0 && t.secsTo(ui->timeEditTo->time()) > 0) {
                    timers[i].setIs_active(false);
                    timers[i].treawidgetitem()->setText(3,"-");
                }
                else {
                    timers[i].setIs_active(false);
                    timers[i].treawidgetitem()->setText(3,"-");
                    timer_finish(timers[i], i);
                }
            }
        }
        timers[i].treawidgetitem()->setText(2,QString::number(hour) + ':' + QString::number(minute) + ':' + QString::number(second));
        timers[i].setTime_left(x.secsTo(timers[i].date_end()));
        }
    }
    if(timers.size() == 0 || dtmin == -1) progress->setValue(0);
    else if(timers[dtmin].date_start().secsTo(timers[dtmin].date_end()) != 0) progress->setValue(100 * (timers[dtmin].date_start().secsTo(timers[dtmin].date_end()) - y.secsTo(timers[dtmin].date_end())) / timers[dtmin].date_start().secsTo(timers[dtmin].date_end())); else progress->setValue(100);
}

void MainWindow::showEvent(QShowEvent *ev)
{
    QMainWindow::showEvent(ev);
    QWinTaskbarButton *button = new QWinTaskbarButton(this);
    button->setWindow(this->windowHandle());
    //button->setOverlayIcon(QIcon(":/icon/alarm-clock.png"));
    progress = button->progress();
    progress->setVisible(true);
    progress->setValue(0);
}

void MainWindow::Dismiss(int i)
{
    delete timers[i].treawidgetitem();
    delete timers[i].getAlarmwindow();
    timers[i].setShould_delete(true);
}

void MainWindow::Snooze(int i)
{
    timers[i].setDate_end(timers[i].date_end().addSecs(600));
    timers[i].treawidgetitem()->setText(4,timers[i].date_end().toString());
    timers[i].setIs_active(true);
    timers[i].treawidgetitem()->setText(3,"+");
    delete timers[i].getAlarmwindow();
}

void MainWindow::Stop(int i)
{

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
    if(timer.getIs_timer()) timer.treawidgetitem()->setText(0,"T"); else timer.treawidgetitem()->setText(0,"A");
    timer.treawidgetitem()->setText(4,timer.date_end().toString());
    timer.treawidgetitem()->setText(1,timer.getName());
    if (timer.is_active()) timer.treawidgetitem()->setText(3,"+"); else timer.treawidgetitem()->setText(3,"-");
    int hour, minute, second;
    hour = timer.date_start().secsTo(timer.date_end()) / 3600;
    minute = (timer.date_start().secsTo(timer.date_end()) % 3600) / 60;
    second = (timer.date_start().secsTo(timer.date_end()) % 3600) % 60;
    timer.treawidgetitem()->setText(2,QString::number(hour) + ':' + QString::number(minute) + ':' + QString::number(second));
    timers.push_back(timer);
}

void MainWindow::timer_finish(Timer &timer, int i)
{
    timer.setAlarmwindow(new alarm(this));
    connect(timer.getAlarmwindow(),SIGNAL(Dismiss(int)),this,SLOT(Dismiss(int)));
    connect(timer.getAlarmwindow(),SIGNAL(Snooze(int)),this,SLOT(Snooze(int)));
    timer.getAlarmwindow()->show();
    emit Path(timer.getPath(), i, timer.getName());
}


void MainWindow::on_delButton_clicked()
{
    if (ui->treeWidget->currentItem() == NULL) return;
    for (int i = 0; i < timers.size(); i++) {
        if (ui->treeWidget->currentItem() == timers[i].treawidgetitem()) {
            delete timers[i].treawidgetitem();
            //timers[i].treawidgetitem()->setHidden(true);
            timers[i].setShould_delete(true);
            break;
        }
    }
}

void MainWindow::on_StopButton_clicked()
{
    if (ui->treeWidget->currentItem() == NULL) return;
    for (int i = 0; i < timers.size(); i++) {
        if (ui->treeWidget->currentItem() == timers[i].treawidgetitem()) {
            timers[i].setIs_active(false);
            timers[i].treawidgetitem()->setText(3,"-");
            break;
        }
    }
}

void MainWindow::on_RunButton_clicked()
{
    if (ui->treeWidget->currentItem() == NULL) return;
    for (int i = 0; i < timers.size(); i++) {
        if (ui->treeWidget->currentItem() == timers[i].treawidgetitem()) {
            timers[i].setIs_active(true);
            timers[i].treawidgetitem()->setText(3,"+");
            if (timers[i].getIs_timer()) {
                QDateTime x(QDate:: currentDate(),QTime:: currentTime());
                timers[i].setDate_end(x.addSecs(timers[i].time_left()));
                timers[i].treawidgetitem()->setText(4,timers[i].date_end().toString());
            }
            break;
        }
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (arg1 == 0) {
        ui->label_from->setEnabled(false);
        ui->label_to->setEnabled(false);
        ui->timeEditFrom->setEnabled(false);
        ui->timeEditTo->setEnabled(false);
    } else {
        ui->label_from->setEnabled(true);
        ui->label_to->setEnabled(true);
        ui->timeEditFrom->setEnabled(true);
        ui->timeEditTo->setEnabled(true);
    }
}
