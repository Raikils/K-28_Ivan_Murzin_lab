#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addtimer.h"
#include "timer.h"
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void Timer_Action();

private slots:
    void on_AddButton_clicked();
    void Add_Timer(Timer timer);

private:
    Ui::MainWindow *ui;
    AddTimer *addwindow;
    QVector<Timer> timers;
};
#endif // MAINWINDOW_H
