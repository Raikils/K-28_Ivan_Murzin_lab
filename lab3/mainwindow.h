#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <createplot.h>
#include <plot.h>
#include <graphics.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_CreateButton_clicked();
    void CreateNewPlot(Plot p);
    void DeleteCreatePlot();

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void rebuild(Plot p);

    void on_spinBox_cur_tick_valueChanged(int arg1);

    void on_comboBox_cur_bar_currentIndexChanged(int index);

    void on_doubleSpinBox_cur_data_valueChanged(double arg1);

    void on_pushButton_Delete_clicked();

    void on_lineEdit_tick_name_textChanged(const QString &arg1);

    void on_pushButton_save_png_clicked();

    void on_pushButton_save_jpg_clicked();

    void on_pushButton_save_pdf_clicked();

    void on_pushButton_delete_plot_clicked();

    void on_pushButton_go_clicked();

private:
    Ui::MainWindow *ui;
    CreatePlot *crpl;
    QVector<Plot> plots;
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
    int cur;
    QVector<double> width;
    QVector<QString> labels;
    Graphics *gra;
};
#endif // MAINWINDOW_H
