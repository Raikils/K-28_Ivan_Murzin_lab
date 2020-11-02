#include "timer.h"

QDateTime Timer::date_start() const
{
    return _date_start;
}

void Timer::setDate_start(const QDateTime &date_start)
{
    _date_start = date_start;
}

QDateTime Timer::date_end() const
{
    return _date_end;
}

void Timer::setDate_end(const QDateTime &date_end)
{
    _date_end = date_end;
}

int Timer::time_left() const
{
    return _time_left;
}

void Timer::setTime_left(int time_left)
{
    _time_left = time_left;
}

QTreeWidgetItem *Timer::treawidgetitem() const
{
    return _treawidgetitem;
}

void Timer::setTreawidgetitem(QTreeWidgetItem *treawidgetitem)
{
    _treawidgetitem = treawidgetitem;
}

bool Timer::is_active() const
{
    return _is_active;
}

void Timer::setIs_active(bool is_active)
{
    _is_active = is_active;
}

QString Timer::getPath() const
{
    return path;
}

void Timer::setPath(const QString &value)
{
    path = value;
}

alarm *Timer::getAlarmwindow() const
{
    return alarmwindow;
}

void Timer::setAlarmwindow(alarm *value)
{
    alarmwindow = value;
}

bool Timer::getShould_delete() const
{
    return should_delete;
}

void Timer::setShould_delete(bool value)
{
    should_delete = value;
}

bool Timer::getIs_timer() const
{
    return _is_timer;
}

void Timer::setIs_timer(bool is_timer)
{
    _is_timer = is_timer;
}

QString Timer::getName() const
{
    return _name;
}

void Timer::setName(const QString &name)
{
    _name = name;
}

Timer::Timer()
{
    
}

QDataStream &operator<<(QDataStream &out, const Timer &timer)
{
    out << int(timer.time_left()) << QDateTime(timer.date_start()) << QDateTime(timer.date_end()) << bool(timer.is_active())
        << QString(timer.getPath()) << bool(timer.getShould_delete()) << bool(timer.getIs_timer()) <<   QString(timer.getName());
    return out;
}

QDataStream &operator>>(QDataStream &in, Timer &timer)
{
    int time_left;
    QDateTime date_start;
    QDateTime date_end;
    bool is_active;
    QString _path;
    bool _should_delete;
    bool is_timer;
    QString name;
    in >> time_left >> date_start >> date_end >> is_active >> _path >> _should_delete >> is_timer >> name;
    timer.setTime_left(time_left);
    timer.setDate_start(date_start);
    timer.setDate_end(date_end);
    timer.setIs_active(is_active);
    timer.setPath(_path);
    timer.setShould_delete(_should_delete);
    timer.setIs_timer(is_timer);
    timer.setName(name);
    return in;
}
