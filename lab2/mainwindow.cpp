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
#include "timer.h"

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
    for(auto &t : timers) {
        if (t.is_active()) {
        int hour, minute, second;
        QDateTime x(QDate:: currentDate(),QTime:: currentTime());
        hour = x.secsTo(t.date_end()) / 3600;
        minute = (x.secsTo(t.date_end()) % 3600) / 60;
        second = (x.secsTo(t.date_end()) % 3600) % 60;
        if (hour + minute + second <= 0) {
            QMessageBox* msgBox = new QMessageBox( this );
               msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
               msgBox->setStandardButtons( QMessageBox::Ok );
               msgBox->setWindowTitle( tr("Error") );
               msgBox->setText( tr("Something happened!") );
               msgBox->setModal( false ); // if you want it non-modal
               msgBox->open( this, SLOT(msgBoxClosed(QAbstractButton*)) );
            t.setIs_active(false);
        }
        t.treawidgetitem()->setText(0,QString::number(hour) + ':' + QString::number(minute) + ':' + QString::number(second));
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
    timers.push_back(timer);
}
