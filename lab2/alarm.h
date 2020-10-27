#ifndef ALARM_H
#define ALARM_H

#include <QDialog>

namespace Ui {
class alarm;
}

class alarm : public QDialog
{
    Q_OBJECT

public:
    explicit alarm(QWidget *parent = nullptr);
    ~alarm();

private slots:
    void Sound_on(QString path);

    void on_pushButton_Snooze_clicked();

    void on_pushButton_Dismiss_clicked();

private:
    Ui::alarm *ui;
};

#endif // ALARM_H
