#include "plot.h"

QString Plot::name() const
{
    return _name;
}

void Plot::setName(const QString &name)
{
    _name = name;
}

QColor Plot::background() const
{
    return _background;
}

void Plot::setBackground(const QColor &background)
{
    _background = background;
}

int Plot::num() const
{
    return _num;
}

void Plot::setNum(int num)
{
    _num = num;
}

QVector<QColor> Plot::color_bars() const
{
    return _color_bars;
}

void Plot::setColor_bars(const QVector<QColor> &color_bars)
{
    _color_bars = color_bars;
}

QVector<QString> Plot::name_bars() const
{
    return _name_bars;
}

void Plot::setName_bars(const QVector<QString> &name_bars)
{
    _name_bars = name_bars;
}

QString Plot::xAxis() const
{
    return _xAxis;
}

void Plot::setXAxis(const QString &xAxis)
{
    _xAxis = xAxis;
}

QString Plot::yAxis() const
{
    return _yAxis;
}

void Plot::setYAxis(const QString &yAxis)
{
    _yAxis = yAxis;
}

bool Plot::main_x() const
{
    return _main_x;
}

void Plot::setMain_x(bool main_x)
{
    _main_x = main_x;
}

bool Plot::legend() const
{
    return _legend;
}

void Plot::setLegend(bool legend)
{
    _legend = legend;
}

QListWidgetItem *Plot::listWidgetItem() const
{
    return _listWidgetItem;
}

void Plot::setListWidgetItem(QListWidgetItem *listWidgetItem)
{
    _listWidgetItem = listWidgetItem;
}

QVector<QVector<double> > Plot::data() const
{
    return _data;
}

void Plot::setData(const QVector<QVector<double> > &data)
{
    _data = data;
}

QVector<double> Plot::ticker() const
{
    return _ticker;
}

void Plot::setTicker(const QVector<double> &ticker)
{
    _ticker = ticker;
}

int Plot::last() const
{
    return _last;
}

void Plot::setLast(int last)
{
    _last = last;
}

QVector<QString> Plot::ticks_name() const
{
    return _ticks_name;
}

void Plot::setTicks_name(const QVector<QString> &ticks_name)
{
    _ticks_name = ticks_name;
}

QDataStream &operator<<(QDataStream &out, const Plot &plot)
{
    out << QString(plot.name()) << QColor(plot.background()) << int(plot.num()) << int(plot.last());
    qDebug() << plot.last();
    for (const auto &k : plot.color_bars()) {
        out << QColor(k);
    }
    //out << plot.color_bars();
    for (const auto &k : plot.name_bars()) {
        out << QString(k);
    }
    out << QString(plot.xAxis()) << QString(plot.yAxis()) << bool(plot.main_x()) << bool(plot.legend());
    for (const auto &k : plot.data()) {
        for (const auto &j : k) {
            out << double(j);
        }
    }
    for (const auto &k : plot.ticker()) {
        out << double(k);
    }
    for (const auto &k : plot.ticks_name()) {
        out << QString(k);
    }
    return out;
}

QDataStream &operator>>(QDataStream &in, Plot &plot)
{
    QString name, xAxis, yAxis, y;
    QColor back, z;
    int num, last;
    bool main, leg;
    QVector<QColor> col;
    QVector<double> tick, u;
    QVector<QVector<double>> data;
    QVector<QString> name_tick, name_bars;
    double x;
    in >> name >> back >> num >> last;
    qDebug() << last;
    for (int i = 0; i < num; i++) {
        in >> z;
        col.push_back(z);
    }
    for (int i = 0; i < num; i++) {
        in >> y;
        name_bars.push_back(y);
    }
    in >> xAxis >> yAxis >> main >> leg;
    for (int i = 0; i < num; i++) {
        u.clear();
        for (int j = 0; j < last + 1; j++) {
            in >>x;
            u.push_back(x);
        }
        data.push_back(u);
    }
    for (int i = 0; i < last + 1; i++) {
        in >> x;
        tick.push_back(x);
    }
    for (int i = 0; i < last + 1; i++) {
        in >> y;
        name_tick.push_back(y);
    }
    plot.setName(name);
    plot.setBackground(back);
    plot.setNum(num);
    plot.setLast(last);
    plot.setColor_bars(col);
    plot.setName_bars(name_bars);
    plot.setXAxis(xAxis);
    plot.setYAxis(yAxis);
    plot.setMain_x(main);
    plot.setLegend(leg);
    plot.setData(data);
    plot.setTicker(tick);
    plot.setTicks_name(name_tick);
    return in;
}

Plot::Plot()
{
    
}
