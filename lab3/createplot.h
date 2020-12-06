#ifndef CREATEPLOT_H
#define CREATEPLOT_H

#include <QDialog>
#include <plot.h>

namespace Ui {
class CreatePlot;
}

class CreatePlot : public QDialog
{
    Q_OBJECT

public:
    explicit CreatePlot(QWidget *parent = nullptr);
    ~CreatePlot();

signals:
    void CreateNewPlot(Plot p);
    void DeleteCreatePlot();

private slots:
    void on_OkButton_clicked();

    void on_CancelButton_clicked();

    void on_comboBox_backcolor_currentIndexChanged(const QString &arg1);

    void on_comboBox_barcolor_currentIndexChanged(const QString &arg1);

    void on_spinBox_num_bars_valueChanged(int arg1);

    void rebuild();

    void on_lineEdit_xAxis_textChanged(const QString &arg1);

    void on_checkBox_legend_stateChanged(int arg1);

    void on_lineEdit_bar_name_textChanged(const QString &arg1);

    void on_comboBox_cur_bar_currentIndexChanged(int index);

    void on_lineEdit_yAxis_textChanged(const QString &arg1);

private:
    Ui::CreatePlot *ui;
    Plot plot;
    QLinearGradient gradient;
    QVector<QCPBars*> bars;
    QCPBarsGroup *group;
    QVector<double> ticks;
    int num;
    QVector<QColor> col_bars;
    QVector<QString> name_bars;
    QString x_name;
    QString y_name;
    bool main_x;
    bool legend;
    QColor background;
    QVector<double> width;
};

#endif // CREATEPLOT_H
