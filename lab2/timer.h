#ifndef TIMER_H
#define TIMER_H
#include <QTime>
#include <QDate>
#include <QDateTime>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QMediaPlayer>

class Timer
{
private:
    int _time_left;
    QDateTime _date_start;
    QDateTime _date_end;
    QTreeWidgetItem *_treawidgetitem;
    bool _is_active;
    QString path;
public:
    Timer();
    QDateTime date_start() const;
    void setDate_start(const QDateTime &date_start);
    QDateTime date_end() const;
    void setDate_end(const QDateTime &date_end);
    int time_left() const;
    void setTime_left(int time_left);
    QTreeWidgetItem *treawidgetitem() const;
    void setTreawidgetitem(QTreeWidgetItem *treawidgetitem);
    bool is_active() const;
    void setIs_active(bool is_active);
    QString getPath() const;
    void setPath(const QString &value);
};

#endif // TIMER_H
