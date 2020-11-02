#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addtimer.h"
#include "timer.h"
#include <QVector>
#include <QShowEvent>
#include <QWinTaskbarProgress>

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

protected:
      void showEvent(QShowEvent *ev);

signals:
    void Path(QString path, int i, QString name);

private slots:
    void Dismiss(int i);
    void Snooze(int i);
    void on_AddButton_clicked();
    void Add_Timer(Timer timer);
    void timer_finish(Timer &timer, int i);

    void on_delButton_clicked();

    void on_StopButton_clicked();

    void on_RunButton_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QVector<Timer> timers;
    QWinTaskbarProgress *progress;
};
#endif // MAINWINDOW_H
