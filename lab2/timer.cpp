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

Timer::Timer()
{
    
}
