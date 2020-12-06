#include "createplot.h"
#include "ui_createplot.h"

CreatePlot::CreatePlot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreatePlot)
{
    ui->setupUi(this);
    connect(this,SIGNAL(CreateNewPlot(Plot)),parent,SLOT(CreateNewPlot(Plot)));
    connect(this,SIGNAL(DeleteCreatePlot()),parent,SLOT(DeleteCreatePlot()));
    ui->comboBox_backcolor->addItem("whiet");
    ui->comboBox_backcolor->addItem("red");
    ui->comboBox_backcolor->addItem("green");
    ui->comboBox_backcolor->addItem("blue");
    ui->comboBox_backcolor->addItem("yellow");
    ui->comboBox_backcolor->addItem("pink");
    ui->comboBox_backcolor->addItem("aqua");
    ui->comboBox_backcolor->addItem("black");

    ui->comboBox_barcolor->addItem("red");
    ui->comboBox_barcolor->addItem("green");
    ui->comboBox_barcolor->addItem("blue");
    ui->comboBox_barcolor->addItem("yellow");
    ui->comboBox_barcolor->addItem("pink");
    ui->comboBox_barcolor->addItem("aqua");
    ui->comboBox_barcolor->addItem("whiet");
    ui->comboBox_barcolor->addItem("black");
    ui->comboBox_cur_bar->addItem("1");
    gradient.setColorAt(0, QColor(255, 255, 255));
    gradient.setColorAt(1, QColor(255, 255, 255));
    ticks << 1 << 2 << 3;
    main_x = true;
    background = QColor(255, 255, 255);

    col_bars.push_back(QColor(255, 0, 0));
    name_bars.push_back("");
    num = 1;
    legend = false;
    group = NULL;
    width << 0.3 << 0.3 << 0.15 << 0.15 << 0.1 << 0.1 << 0.06 << 0.06;
    rebuild();
}

CreatePlot::~CreatePlot()
{
    delete ui;
}

void CreatePlot::on_OkButton_clicked()
{
    plot.setName(ui->lineEdit_name->text());
    plot.setBackground(background);
    plot.setNum(num);
    plot.setColor_bars(col_bars);
    plot.setName_bars(name_bars);
    plot.setXAxis(x_name);
    plot.setYAxis(y_name);
    plot.setMain_x(main_x);
    plot.setLegend(legend);
    close();
    emit CreateNewPlot(plot);
}

void CreatePlot::on_CancelButton_clicked()
{
    emit DeleteCreatePlot();
}

void CreatePlot::on_comboBox_backcolor_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "red") {
        gradient.setColorAt(0, QColor(255, 0, 0));
        gradient.setColorAt(1, QColor(255, 0, 0));
        background = QColor(255, 0, 0);
    }
    if (arg1 == "green") {
        gradient.setColorAt(0, QColor(0, 255, 0));
        gradient.setColorAt(1, QColor(0, 255, 0));
        background = QColor(0, 255, 0);
    }
    if (arg1 == "blue") {
        gradient.setColorAt(0, QColor(0, 0, 255));
        gradient.setColorAt(1, QColor(0, 0, 255));
        background = QColor(0, 0, 255);
    }
    if (arg1 == "whiet") {
        gradient.setColorAt(0, QColor(255, 255, 255));
        gradient.setColorAt(1, QColor(255, 255, 255));
        background = QColor(255, 255, 255);
    }
    if (arg1 == "yellow") {
        gradient.setColorAt(0, QColor(255, 255, 0));
        gradient.setColorAt(1, QColor(255, 255, 0));
        background = QColor(255, 255, 0);
    }
    if (arg1 == "pink") {
        gradient.setColorAt(0, QColor(255, 0, 255));
        gradient.setColorAt(1, QColor(255, 0, 255));
        background = QColor(255, 0, 255);
    }
    if (arg1 == "aqua") {
        gradient.setColorAt(0, QColor(0, 255, 255));
        gradient.setColorAt(1, QColor(0, 255, 255));
        background = QColor(0, 255, 255);
    }
    if (arg1 == "black") {
        gradient.setColorAt(0, QColor(0, 0, 0));
        gradient.setColorAt(1, QColor(0, 0, 0));
        background = QColor(0, 0, 0);
    }
    ui->customPlot->setBackground(QBrush(gradient));
    ui->customPlot->replot();
    ui->customPlot->update();
}

void CreatePlot::on_comboBox_barcolor_currentIndexChanged(const QString &arg1)
{
    if(bars.size() == 0) return;
    int i = ui->comboBox_cur_bar->currentIndex();
    if (arg1 == "red") {
        bars[i]->setBrush(QColor(255, 0, 0));
        col_bars[i] = QColor(255, 0, 0);
    }
    if (arg1 == "green") {
        bars[i]->setBrush(QColor(0, 255, 0));
        col_bars[i] = QColor(0, 255, 0);
    }
    if (arg1 == "blue") {
        bars[i]->setBrush(QColor(0, 0, 255));
        col_bars[i] = QColor(0, 0, 255);
    }
    if (arg1 == "whiet") {
        bars[i]->setBrush(QColor(255, 255, 255));
        col_bars[i] = QColor(255, 255, 255);
    }
    if (arg1 == "yellow") {
        bars[i]->setBrush(QColor(255, 255, 0));
        col_bars[i] = QColor(255, 255, 0);
    }
    if (arg1 == "pink") {
        bars[i]->setBrush(QColor(255, 0, 255));
        col_bars[i] = QColor(255, 0, 255);
    }
    if (arg1 == "aqua") {
        bars[i]->setBrush(QColor(0, 255, 255));
        col_bars[i] = QColor(0, 255, 255);
    }
    if (arg1 == "black") {
        bars[i]->setBrush(QColor(0, 0, 0));
        col_bars[i] = QColor(0, 0, 0);
    }
    ui->customPlot->replot();
    ui->customPlot->update();
}

void CreatePlot::on_spinBox_num_bars_valueChanged(int arg1)
{
    if (bars.size() == 0) return;
    if (bars.size() == arg1) return;
    if (bars.size() > arg1) {
        col_bars.resize(arg1);
        name_bars.resize(arg1);
        int i = num;
        num = arg1;
        ui->comboBox_cur_bar->setCurrentIndex(0);
        while (i > arg1) {
            ui->comboBox_cur_bar->removeItem(i - 1);
            i--;
        }
        rebuild();
    }
    else {
        while (bars.size() < arg1) {
            if (main_x) bars.push_back(new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis));
            else bars.push_back(new QCPBars(ui->customPlot->yAxis, ui->customPlot->xAxis));
            bars[bars.size() - 1]->setAntialiased(false);
            bars[bars.size() - 1]->setStackingGap(1);
            bars[bars.size() - 1]->setName("");
            name_bars.push_back("");
            bars[bars.size() - 1]->setBrush(QColor(0, 255, 0));
            col_bars.push_back(QColor(0, 255, 0));
            bars[bars.size() - 1]->setWidth(0.3);
            QVector<double> data;
            data << 2 << 5 << 9;
            bars[bars.size() - 1]->setData(ticks, data);
            bars[bars.size() - 1]->setBarsGroup(group);
            ui->comboBox_cur_bar->addItem(QString::number(bars.size()));
            num++;
        }
    }
    rebuild();
    ui->customPlot->replot();
    ui->customPlot->update();
}

void CreatePlot::rebuild()
{
    ui->customPlot->clearPlottables();
    bars.clear();
    if (group != NULL) group->clear();
    if (group != NULL) delete group;
    group = new QCPBarsGroup(ui->customPlot);
    QVector<double> data;
    data << 2 << 5 << 9;
    for (int i = 0; i < num; i++) {
        if (main_x) bars.push_back(new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis));
        else bars.push_back(new QCPBars(ui->customPlot->yAxis, ui->customPlot->xAxis));
        bars[bars.size() - 1]->setAntialiased(false);
        bars[bars.size() - 1]->setStackingGap(1);
        bars[bars.size() - 1]->setName(name_bars[i]);
        bars[bars.size() - 1]->setBrush(col_bars[i]);
        bars[bars.size() - 1]->setWidth(width[num - 1]);
        bars[bars.size() - 1]->setData(ticks, data);
        bars[bars.size() - 1]->setBarsGroup(group);
    }
    ui->customPlot->setBackground(QBrush(gradient));
    ui->customPlot->xAxis->setRange(0, 4);
    ui->customPlot->yAxis->setRange(0, 10);
    ui->customPlot->xAxis->setLabel(ui->lineEdit_xAxis->text());
    ui->customPlot->yAxis->setLabel(ui->lineEdit_yAxis->text());
    QVector<QString> labels;
    labels << "1" << "2" << "3";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
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

void CreatePlot::on_lineEdit_xAxis_textChanged(const QString &arg1)
{
    ui->customPlot->xAxis->setLabel(arg1);
    ui->customPlot->replot();
    ui->customPlot->update();
}

void CreatePlot::on_checkBox_legend_stateChanged(int arg1)
{
    if (arg1) legend = true;
    else legend = false;
    rebuild();
    ui->customPlot->replot();
    ui->customPlot->update();
}

void CreatePlot::on_lineEdit_bar_name_textChanged(const QString &arg1)
{
    name_bars[ui->comboBox_cur_bar->currentIndex()] = arg1;
    rebuild();
    ui->customPlot->replot();
    ui->customPlot->update();
}

void CreatePlot::on_comboBox_cur_bar_currentIndexChanged(int index)
{
    if (col_bars.size() == 0) return;
    if (col_bars[index] == QColor(255,0,0)) {
        ui->comboBox_barcolor->setCurrentIndex(0);
    }
    if (col_bars[index] == QColor(0,255,0)) {
        ui->comboBox_barcolor->setCurrentIndex(1);
    }
    if (col_bars[index] == QColor(0,0,255)) {
        ui->comboBox_barcolor->setCurrentIndex(2);
    }
    if (col_bars[index] == QColor(255,255,0)) {
        ui->comboBox_barcolor->setCurrentIndex(3);
    }
    if (col_bars[index] == QColor(0,255,255)) {
        ui->comboBox_barcolor->setCurrentIndex(4);
    }
    if (col_bars[index] == QColor(255,0,255)) {
        ui->comboBox_barcolor->setCurrentIndex(5);
    }
    if (col_bars[index] == QColor(255,255,255)) {
        ui->comboBox_barcolor->setCurrentIndex(6);
    }
    if (col_bars[index] == QColor(0, 0, 0)) {
        ui->comboBox_barcolor->setCurrentIndex(7);
    }
    ui->lineEdit_bar_name->setText(name_bars[index]);
    rebuild();
    ui->customPlot->replot();
    ui->customPlot->update();
}

void CreatePlot::on_lineEdit_yAxis_textChanged(const QString &arg1)
{
    ui->customPlot->yAxis->setLabel(arg1);
    ui->customPlot->replot();
    ui->customPlot->update();
}
