#ifndef ALARM_H
#define ALARM_H

#include <QDialog>
#include <QMediaPlayer>

namespace Ui {
class alarm;
}

class alarm : public QDialog
{
    Q_OBJECT

public:
    explicit alarm(QWidget *parent = nullptr);
    ~alarm();

signals:
    void Dismiss(int i);
    void Snooze(int i);
    void Stop(int i);

private:
    QMediaPlayer *sound;
    int iterator;

private slots:
    void Sound_on(QString path, int i, QString name);

    void on_pushButton_Snooze_clicked();

    void on_pushButton_Dismiss_clicked();

    void on_pushButton_Stop_clicked();

private:
    Ui::alarm *ui;
};

#endif // ALARM_H
