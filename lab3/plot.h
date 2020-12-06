#ifndef PLOT_H
#define PLOT_H
#include <qcustomplot.h>
#include <QListWidgetItem>

class Plot
{
private:
    QString _name;
    QColor _background;
    int _num;
    QVector<QColor> _color_bars;
    QVector<QString> _name_bars;
    QString _xAxis;
    QString _yAxis;
    bool _main_x;
    bool _legend;
    QListWidgetItem *_listWidgetItem;
    QVector<QVector<double>> _data;
    QVector<double> _ticker;
    int _last;
    QVector<QString> _ticks_name;
public:
    Plot();

    QString name() const;
    void setName(const QString &name);
    QColor background() const;
    void setBackground(const QColor &background);
    int num() const;
    void setNum(int num);
    QVector<QColor> color_bars() const;
    void setColor_bars(const QVector<QColor> &color_bars);
    QVector<QString> name_bars() const;
    void setName_bars(const QVector<QString> &name_bars);
    QString xAxis() const;
    void setXAxis(const QString &xAxis);
    QString yAxis() const;
    void setYAxis(const QString &yAxis);
    bool main_x() const;
    void setMain_x(bool main_x);
    bool legend() const;
    void setLegend(bool legend);
    QListWidgetItem *listWidgetItem() const;
    void setListWidgetItem(QListWidgetItem *listWidgetItem);
    QVector<QVector<double> > data() const;
    void setData(const QVector<QVector<double> > &data);
    QVector<double> ticker() const;
    void setTicker(const QVector<double> &ticker);
    int last() const;
    void setLast(int last);
    QVector<QString> ticks_name() const;
    void setTicks_name(const QVector<QString> &ticks_name);
};

QDataStream &operator<<(QDataStream &out, const Plot &plot);
QDataStream &operator>>(QDataStream &in, Plot &plot);

#endif // PLOT_H
