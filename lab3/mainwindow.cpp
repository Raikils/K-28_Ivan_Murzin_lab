#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    group = NULL;
    cur = -1;
    width << 0.3 << 0.3 << 0.15 << 0.15 << 0.1 << 0.1 << 0.06 << 0.06;
    QFile f("plots.dat");
    f.open(QIODevice::ReadOnly);
    QDataStream in(&f);
    while(!in.atEnd()) {
         Plot k;
         in >> k;
         k.setListWidgetItem(new QListWidgetItem(ui->listWidget));
         k.listWidgetItem()->setText(k.name());
         //qDebug() << k.name() << k.background() << k.num() << k.last() << k.color_bars() << k.name_bars() << k.xAxis() << k.yAxis()
         //         <<k.main_x() << k.legend() << k.data() << k.ticker() << k.ticks_name();
         plots.push_back(k);
    }
}

MainWindow::~MainWindow()
{
    QFile f("plots.dat");
    f.open(QIODevice::WriteOnly);
    QDataStream out(&f);
    for (const auto &k : plots) {
        out << Plot(k);
        //qDebug() << k.name() << k.background() << k.num() << k.last() << k.color_bars() << k.name_bars() << k.xAxis() << k.yAxis()
        //         <<k.main_x() << k.legend() << k.data() << k.ticker() << k.ticks_name();
    }
    delete ui;
}


void MainWindow::on_CreateButton_clicked()
{
    crpl = new CreatePlot(this);
    crpl->exec();
}

void MainWindow::CreateNewPlot(Plot p)
{
    delete crpl;

    p.setListWidgetItem(new QListWidgetItem(ui->listWidget));
    p.listWidgetItem()->setText(p.name());

    QVector<QVector<double>> data;
    for (int i = 0; i < p.num(); i++) {
        data.push_back({0});
    }
    p.setData(data);
    p.setTicker({1});
    p.setLast(0);
    p.setTicks_name({"1"});
    plots.push_back(p);
}

void MainWindow::DeleteCreatePlot()
{
    delete crpl;
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    int i = 0;
    for (i = 0; i < plots.size(); i++) {
        if(plots[i].listWidgetItem() == current) {
            rebuild(plots[i]);
            ui->customPlot->replot();
            ui->customPlot->update();
            cur = i;
            ui->spinBox_cur_tick->setValue(1);
            ui->spinBox_cur_tick->setMaximum(plots[i].last() + 1);
            ui->lineEdit_tick_name->setText(plots[i].ticks_name()[0]);
            ui->comboBox_cur_bar->setCurrentIndex(0);
            if (ui->comboBox_cur_bar->count() > plots[i].num())
            for (int j = 7; j >= plots[i].num(); j--) {
                ui->comboBox_cur_bar->removeItem(j);
            }
            else
            for (int l = ui->comboBox_cur_bar->count() + 1; l <= plots[i].num(); l++) {
                ui->comboBox_cur_bar->addItem(QString::number(l));
            }
            ui->doubleSpinBox_cur_data->setValue(plots[i].data()[0][0]);
            cur = i;
            ui->customPlot->update();
            ui->customPlot->replot();
            return;
        }
    }
}

void MainWindow::rebuild(Plot p)
{
    ui->customPlot->clearPlottables();
    ui->customPlot->clearGraphs();
    ui->customPlot->clearItems();
    bars.clear();
    if (group != NULL) group->clear();
    if (group != NULL) delete group;
    group = new QCPBarsGroup(ui->customPlot);
    num = p.num();
    gradient.setColorAt(0, p.background());
    gradient.setColorAt(1, p.background());
    col_bars.clear();
    col_bars = p.color_bars();
    name_bars.clear();
    name_bars = p.name_bars();
    x_name = p.xAxis();
    y_name = p.yAxis();
    main_x = p.main_x();
    legend = p.legend();

    for (int i = 0; i < num; i++) {
        if (main_x) bars.push_back(new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis));
        else bars.push_back(new QCPBars(ui->customPlot->yAxis, ui->customPlot->xAxis));
        bars[bars.size() - 1]->setAntialiased(false);
        bars[bars.size() - 1]->setStackingGap(1);
        bars[bars.size() - 1]->setName(name_bars[i]);
        bars[bars.size() - 1]->setBrush(col_bars[i]);
        bars[bars.size() - 1]->setWidth(width[p.num() - 1]);
        bars[bars.size() - 1]->setData(p.ticker(), p.data()[i]);
        bars[bars.size() - 1]->setBarsGroup(group);
    }
    ui->customPlot->setBackground(QBrush(gradient));
    ui->customPlot->xAxis->setRange(0, 4);
    ui->customPlot->yAxis->setRange(0, 10);
    ui->customPlot->xAxis->setLabel(x_name);
    ui->customPlot->yAxis->setLabel(y_name);

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(p.ticker(), p.ticks_name());
    ui->customPlot->xAxis->setTicker(textTicker);

    ui->customPlot->legend->setVisible(legend);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::on_spinBox_cur_tick_valueChanged(int arg1)
{
    ui->comboBox_cur_bar->setCurrentIndex(0);
    ui->lineEdit_tick_name->setText(plots[cur].ticks_name()[arg1 - 1]);
    if(cur >= 0) ui->doubleSpinBox_cur_data->setValue(plots[cur].data()[0][arg1 - 1]);
}

void MainWindow::on_comboBox_cur_bar_currentIndexChanged(int index)
{
    if(cur >= 0) ui->doubleSpinBox_cur_data->setValue(plots[cur].data()[index][ui->spinBox_cur_tick->value() - 1]);
}

void MainWindow::on_doubleSpinBox_cur_data_valueChanged(double arg1)
{
    if(cur >= 0) { QVector<QVector<double>> data = plots[cur].data();
    data[ui->comboBox_cur_bar->currentIndex()][ui->spinBox_cur_tick->value() - 1] = arg1;
    plots[cur].setData(data);
    if (plots[cur].last() == ui->spinBox_cur_tick->value() - 1) {
        plots[cur].setLast(plots[cur].last() + 1);
        ui->spinBox_cur_tick->setMaximum(plots[cur].last() + 1);
        QVector<QVector<double>> data1 = plots[cur].data();
        for (auto &k : data1) k << 0;
        plots[cur].setData(data1);
        QVector<double> tick = plots[cur].ticker();
        tick << plots[cur].last() + 1;
        plots[cur].setTicker(tick);
        QVector<QString> labels = plots[cur].ticks_name();
        labels << QString::number(plots[cur].last() + 1);
        plots[cur].setTicks_name(labels);
        qDebug() << plots[cur].data()[0].size();
    }
    rebuild(plots[cur]);
    ui->customPlot->update();
    ui->customPlot->replot();
    }
}

void MainWindow::on_pushButton_Delete_clicked()
{
    QVector<QVector<double>> data = plots[cur].data();
    for ( auto &k : data) {
        k[ui->spinBox_cur_tick->value() - 1] = 0;
    }
    plots[cur].setData(data);
    ui->doubleSpinBox_cur_data->setValue(0);
    rebuild(plots[cur]);
    ui->customPlot->update();
    ui->customPlot->replot();
}

void MainWindow::on_lineEdit_tick_name_textChanged(const QString &arg1)
{
    QVector<QString> labels = plots[cur].ticks_name();
    labels[ui->spinBox_cur_tick->value() - 1] = arg1;
    plots[cur].setTicks_name(labels);
    rebuild(plots[cur]);
    ui->customPlot->update();
    ui->customPlot->replot();
}

void MainWindow::on_pushButton_save_png_clicked()
{
    if(cur >= 0) ui->customPlot->savePng(plots[cur].name() + ".png",531,401);
}

void MainWindow::on_pushButton_save_jpg_clicked()
{
    if(cur >= 0) ui->customPlot->saveJpg(plots[cur].name() + ".jpg",531,401);
}

void MainWindow::on_pushButton_save_pdf_clicked()
{
    if(cur >= 0) ui->customPlot->savePdf(plots[cur].name() + ".pdf",531,401);
}

void MainWindow::on_pushButton_delete_plot_clicked()
{
    if (cur < 0) return;
    ui->customPlot->clearPlottables();
    ui->customPlot->clearGraphs();
    ui->customPlot->clearItems();
    ui->customPlot->update();
    ui->customPlot->replot();
    int c = cur;
    delete plots[cur].listWidgetItem();
    plots.erase(plots.begin() + c);
}

void MainWindow::on_pushButton_go_clicked()
{
    gra = new Graphics(this);
    gra->exec();
}
