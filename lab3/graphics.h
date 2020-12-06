#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QDialog>
#include "qcustomplot.h"

namespace Ui {
class Graphics;
}

class Graphics : public QDialog
{
    Q_OBJECT

public:
    explicit Graphics(QWidget *parent = nullptr);
    ~Graphics();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_add_clicked();

    void plot();

    void on_pushButton_clear_clicked();

    void clicked_customplot(QMouseEvent *event);

    void on_comboBox_col_own_currentIndexChanged(const QString &arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_comboBox_shapes_currentIndexChanged(const QString &arg1);

    void on_comboBox_col_graph_currentIndexChanged(const QString &arg1);

    void on_pushButton_png_clicked();

    void on_pushButton_pdf_clicked();

private:
    Ui::Graphics *ui;
    QVector<QVector<double>> xdata;
    QVector<QVector<double>> ydata;
    QVector<double> x1;
    QVector<double> y1;
    QVector<QPen> pens;
    QVector<QCPScatterStyle::ScatterShape> shapes;
    QPen col;
};

#endif // GRAPHICS_H
