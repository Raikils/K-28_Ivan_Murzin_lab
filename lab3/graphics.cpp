#include "graphics.h"
#include "ui_graphics.h"
#include "equations.h"

Graphics::Graphics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graphics)
{
    ui->setupUi(this);
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), SLOT(clicked_customplot(QMouseEvent*)));
    ui->customPlot->xAxis->setRange(-10,10);
    ui->customPlot->yAxis->setRange(-10,10);
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    xdata.push_back({});
    ydata.push_back({});
    xdata.push_back({});
    ydata.push_back({});
    xdata.push_back({});
    ydata.push_back({});
    xdata.push_back({});
    ydata.push_back({});
    xdata.push_back({});
    ydata.push_back({});
    xdata.push_back({});
    ydata.push_back({});
    xdata.push_back({});
    ydata.push_back({});
    xdata.push_back({});
    ydata.push_back({});
    xdata.push_back({});
    ydata.push_back({});
    xdata.push_back({});
    ydata.push_back({});
    xdata.push_back({});
    ydata.push_back({});
    ui->comboBox_col_graph->addItem("blue");
    ui->comboBox_col_graph->addItem("red");
    ui->comboBox_col_graph->addItem("green");
    ui->comboBox_col_graph->addItem("yellow");
    ui->comboBox_col_graph->addItem("pink");
    ui->comboBox_col_graph->addItem("aqua");
    ui->comboBox_col_graph->addItem("black");

    ui->comboBox_col_own->addItem("blue");
    ui->comboBox_col_own->addItem("red");
    ui->comboBox_col_own->addItem("green");
    ui->comboBox_col_own->addItem("yellow");
    ui->comboBox_col_own->addItem("pink");
    ui->comboBox_col_own->addItem("aqua");
    ui->comboBox_col_own->addItem("black");

    pens.push_back(QPen(QColor(0, 0, 255)));
    pens.push_back(QPen(QColor(0, 0, 255)));
    pens.push_back(QPen(QColor(0, 0, 255)));
    pens.push_back(QPen(QColor(0, 0, 255)));
    pens.push_back(QPen(QColor(0, 0, 255)));
    pens.push_back(QPen(QColor(0, 0, 255)));
    pens.push_back(QPen(QColor(0, 0, 255)));
    pens.push_back(QPen(QColor(0, 0, 255)));
    pens.push_back(QPen(QColor(0, 0, 255)));
    pens.push_back(QPen(QColor(0, 0, 255)));
    pens.push_back(QPen(QColor(0, 0, 255)));
    pens.push_back(QPen(QColor(0, 0, 255)));

    ui->comboBox_shapes->addItem("None");
    ui->comboBox_shapes->addItem("Cross");
    ui->comboBox_shapes->addItem("Plus");
    ui->comboBox_shapes->addItem("Circle");
    ui->comboBox_shapes->addItem("Disc");
    ui->comboBox_shapes->addItem("Square");
    ui->comboBox_shapes->addItem("Diamond");
    ui->comboBox_shapes->addItem("Star");
    ui->comboBox_shapes->addItem("Triangle");
    ui->comboBox_shapes->addItem("TriangleInverted");
    ui->comboBox_shapes->addItem("CrossSquare");
    ui->comboBox_shapes->addItem("PlusSquare");
    ui->comboBox_shapes->addItem("CrossCircle");
    ui->comboBox_shapes->addItem("PlusCircle");
    ui->comboBox_shapes->addItem("Peace");
    for (int i = 0; i < 10; i++) {
        shapes << QCPScatterStyle::ssNone;
    }
    col = QPen(QColor(0, 0, 255));
}

Graphics::~Graphics()
{
    delete ui;
}

void Graphics::on_lineEdit_textChanged(const QString &arg1)
{
    if (arg1.size() == 0) {
        x1.clear();
        y1.clear();
        plot();
        return;
    }
    bool q, d;
    QString x;
    int cur = 0;
    Equations equ;
    equ.setNum(0);
    while (true) {
        if (arg1[cur] == '-') q =false;
        else if (arg1[cur] == '+') q =true;
             else return;
        cur++;
        if (cur == arg1.size()) return;
        x.clear();
        d = true;
        while (arg1[cur] != 'x') {
            if (arg1[cur] < '0' && arg1[cur] > '9') {
                if (arg1[cur] == '.' && d) d =false;
                else return;
            }
            x.push_back(arg1[cur]);
            cur++;
            if (cur == arg1.size()) return;
        }
        if (q) {
            if (x.size() == 0) {
                equ.setNum(equ.num() + 1);
                equ.add_number(1);
            }
            else {
                equ.setNum(equ.num() + 1);
                equ.add_number(x.toDouble());
            }
        }
        else {
            if (x.size() == 0) {
                equ.setNum(equ.num() + 1);
                equ.add_number(-1);
            }
            else {
                equ.setNum(equ.num() + 1);
                equ.add_number(-x.toDouble());
            }
        }
        cur++;
        if (cur == arg1.size()) {
            equ.add_power(1);
            break;
        }
        if (arg1[cur] != '+' && arg1[cur] != '-' && arg1[cur] != '^') return;

        if (arg1[cur] == '^') {
            cur++;
            if (cur == arg1.size()) return;
            if (arg1[cur] == '-') { q =false; cur++; if (cur == arg1.size()) return; }
            else q =true;
            x.clear();
            d = true;
            while (arg1[cur] != '+' && arg1[cur] != '-') {
                if (arg1[cur] < '0' && arg1[cur] > '9') {
                    if (arg1[cur] == '.' && d) d =false;
                    else return;
                }
                x.push_back(arg1[cur]);
                cur++;
                if (cur == arg1.size()) {break; }
            }
            if (q) {
                if (x.size() == 0) {
                    return;
                }
                else {
                    equ.add_power(x.toDouble());
                }
            }
            else {
                if (x.size() == 0) {
                    return;
                }
                else {
                    equ.add_power(-x.toDouble());
                }
            }
            if (cur == arg1.size()) break;
        }
        else equ.add_power(1);

        if (cur == arg1.size()) break;
    }
    /*qDebug() << equ.num() << equ.numbers().size() << equ.powers().size();
    for (const auto &k : equ.numbers()) {
        qDebug() << k;
    }
    for (const auto &k : equ.powers()) {
        qDebug() << k;
    }*/
    QVector<double> numbers = equ.numbers(), powers = equ.powers();
    int n = equ.num();
    x1.clear();
    y1.clear();
    for (int  i = 0; i < 10001; i++) {
        x1.push_back((i + 0.0)/500 - 10);
        y1.push_back(0);
        for (int  j = 0; j < n; j++) {
            y1[i] += numbers[j] * pow(x1[i], powers[j]);
        }
    }
    plot();
}

void Graphics::on_pushButton_add_clicked()
{
    xdata[ui->spinBox->value() - 1].append(ui->doubleSpinBox_x->value());
    ydata[ui->spinBox->value() - 1].append(ui->doubleSpinBox_y->value());
    plot();
}

void Graphics::plot()
{
    ui->customPlot->graph(0)->setData(x1, y1);
    ui->customPlot->graph(0)->setPen(col);
    for (int i = 1; i <= 10; i++) {
        ui->customPlot->graph(i)->setData(xdata[i - 1], ydata[i - 1]);
        ui->customPlot->graph(i)->setPen(pens[i - 1]);
        ui->customPlot->graph(i)->setScatterStyle(QCPScatterStyle(shapes.at(i - 1), 10));
    }
    ui->customPlot->replot();
    ui->customPlot->update();
}

void Graphics::on_pushButton_clear_clicked()
{
    xdata[ui->spinBox->value() - 1].clear();
    ydata[ui->spinBox->value() - 1].clear();
    plot();
}

void Graphics::clicked_customplot(QMouseEvent *event)
{
    QPoint point = event->pos();
    xdata[ui->spinBox->value() - 1].append(ui->customPlot->xAxis->pixelToCoord(point.x()));
    ydata[ui->spinBox->value() - 1].append(ui->customPlot->yAxis->pixelToCoord(point.y()));
    plot();
}

void Graphics::on_comboBox_col_own_currentIndexChanged(const QString &arg1)
{
    if (pens.size() == 0) return;
    if (arg1 == "red") {
        pens[ui->spinBox->value() - 1] = QPen(QColor(255, 0, 0));
    }
    if (arg1 == "blue") {
        pens[ui->spinBox->value() - 1] = QPen(QColor(0, 0, 255));
    }
    if (arg1 == "green") {
        pens[ui->spinBox->value() - 1] = QPen(QColor(0, 255, 0));
    }
    if (arg1 == "yellow") {
        pens[ui->spinBox->value() - 1] = QPen(QColor(255, 255, 0));
    }
    if (arg1 == "pink") {
        pens[ui->spinBox->value() - 1] = QPen(QColor(255, 0, 255));
    }
    if (arg1 == "aqua") {
        pens[ui->spinBox->value() - 1] = QPen(QColor(0, 255, 255));
    }
    if (arg1 == "black") {
        pens[ui->spinBox->value() - 1] = QPen(QColor(0, 0, 0));
    }
    plot();
}

void Graphics::on_spinBox_valueChanged(int arg1)
{
    if (pens.size() == 0) return;
    if (pens[arg1 - 1] == QPen(QColor(255, 0, 0))) {
        ui->comboBox_col_own->setCurrentIndex(1);
    }
    if (pens[arg1 - 1] == QPen(QColor(0, 255, 0))) {
        ui->comboBox_col_own->setCurrentIndex(2);
    }
    if (pens[arg1 - 1] == QPen(QColor(0, 0, 255))) {
        ui->comboBox_col_own->setCurrentIndex(0);
    }
    if (pens[arg1 - 1] == QPen(QColor(255, 255, 0))) {
        ui->comboBox_col_own->setCurrentIndex(3);
    }
    if (pens[arg1 - 1] == QPen(QColor(255, 0, 255))) {
        ui->comboBox_col_own->setCurrentIndex(4);
    }
    if (pens[arg1 - 1] == QPen(QColor(0, 255, 255))) {
        ui->comboBox_col_own->setCurrentIndex(5);
    }
    if (pens[arg1 - 1] == QPen(QColor(0, 0, 0))) {
        ui->comboBox_col_own->setCurrentIndex(6);
    }
    if (shapes[arg1 - 1] == QCPScatterStyle::ssNone) {
        ui->comboBox_shapes->setCurrentIndex(0);
    }
    if (shapes[arg1 - 1] == QCPScatterStyle::ssCross) {
        ui->comboBox_shapes->setCurrentIndex(1);
    }
    if (shapes[arg1 - 1] == QCPScatterStyle::ssPlus) {
        ui->comboBox_shapes->setCurrentIndex(2);
    }
    if (shapes[arg1 - 1] == QCPScatterStyle::ssCircle) {
        ui->comboBox_shapes->setCurrentIndex(3);
    }
    if (shapes[arg1 - 1] == QCPScatterStyle::ssDisc) {
        ui->comboBox_shapes->setCurrentIndex(4);
    }
    if (shapes[arg1 - 1] == QCPScatterStyle::ssSquare) {
        ui->comboBox_shapes->setCurrentIndex(5);
    }
    if (shapes[arg1 - 1] == QCPScatterStyle::ssDiamond) {
        ui->comboBox_shapes->setCurrentIndex(6);
    }
    if (shapes[arg1 - 1] == QCPScatterStyle::ssStar) {
        ui->comboBox_shapes->setCurrentIndex(7);
    }
    if (shapes[arg1 - 1] == QCPScatterStyle::ssTriangle) {
        ui->comboBox_shapes->setCurrentIndex(8);
    }
    if (shapes[arg1 - 1] == QCPScatterStyle::ssTriangleInverted) {
        ui->comboBox_shapes->setCurrentIndex(9);
    }
    if (shapes[arg1 - 1] == QCPScatterStyle::ssCrossSquare) {
        ui->comboBox_shapes->setCurrentIndex(10);
    }
    if (shapes[arg1 - 1] == QCPScatterStyle::ssPlusSquare) {
        ui->comboBox_shapes->setCurrentIndex(11);
    }
    if (shapes[arg1 - 1] == QCPScatterStyle::ssCrossCircle) {
        ui->comboBox_shapes->setCurrentIndex(12);
    }
    if (shapes[arg1 - 1] == QCPScatterStyle::ssPlusCircle) {
        ui->comboBox_shapes->setCurrentIndex(13);
    }
    if (shapes[arg1 - 1] == QCPScatterStyle::ssPeace) {
        ui->comboBox_shapes->setCurrentIndex(14);
    }
}

void Graphics::on_comboBox_shapes_currentIndexChanged(const QString &arg1)
{
    if (shapes.size() == 0) return;
    if (arg1 == "None") {
        shapes[ui->spinBox->value() - 1] = QCPScatterStyle::ssNone;
    }
    if (arg1 == "Cross") {
        shapes[ui->spinBox->value() - 1] = QCPScatterStyle::ssCross;
    }
    if (arg1 == "Plus") {
        shapes[ui->spinBox->value() - 1] = QCPScatterStyle::ssPlus;
    }
    if (arg1 == "Circle") {
        shapes[ui->spinBox->value() - 1] = QCPScatterStyle::ssCircle;
    }
    if (arg1 == "Disc") {
        shapes[ui->spinBox->value() - 1] = QCPScatterStyle::ssDisc;
    }
    if (arg1 == "Square") {
        shapes[ui->spinBox->value() - 1] = QCPScatterStyle::ssSquare;
    }
    if (arg1 == "Diamond") {
        shapes[ui->spinBox->value() - 1] = QCPScatterStyle::ssDiamond;
    }
    if (arg1 == "Star") {
        shapes[ui->spinBox->value() - 1] = QCPScatterStyle::ssStar;
    }
    if (arg1 == "Triangle") {
        shapes[ui->spinBox->value() - 1] = QCPScatterStyle::ssTriangle;
    }
    if (arg1 == "TriangleInverted") {
        shapes[ui->spinBox->value() - 1] = QCPScatterStyle::ssTriangleInverted;
    }
    if (arg1 == "CrossSquare") {
        shapes[ui->spinBox->value() - 1] = QCPScatterStyle::ssCrossSquare;
    }
    if (arg1 == "PlusSquare") {
        shapes[ui->spinBox->value() - 1] = QCPScatterStyle::ssPlusSquare;
    }
    if (arg1 == "CrossCircle") {
        shapes[ui->spinBox->value() - 1] = QCPScatterStyle::ssCrossCircle;
    }
    if (arg1 == "PlusCircle") {
        shapes[ui->spinBox->value() - 1] = QCPScatterStyle::ssPlusCircle;
    }
    if (arg1 == "Peace") {
        shapes[ui->spinBox->value() - 1] = QCPScatterStyle::ssPeace;
    }
    plot();
}

void Graphics::on_comboBox_col_graph_currentIndexChanged(const QString &arg1)
{
    if (pens.size() == 0) return;
    if (arg1 == "red") {
        col = QPen(QColor(255, 0, 0));
    }
    if (arg1 == "blue") {
        col = QPen(QColor(0, 0, 255));
    }
    if (arg1 == "green") {
        col = QPen(QColor(0, 255, 0));
    }
    if (arg1 == "yellow") {
        col = QPen(QColor(255, 255, 0));
    }
    if (arg1 == "pink") {
        col = QPen(QColor(255, 0, 255));
    }
    if (arg1 == "aqua") {
        col = QPen(QColor(0, 255, 255));
    }
    if (arg1 == "black") {
        col = QPen(QColor(0, 0, 0));
    }
    plot();
}

void Graphics::on_pushButton_png_clicked()
{
    ui->customPlot->savePng("plot.png",531,401);
}

void Graphics::on_pushButton_pdf_clicked()
{
    ui->customPlot->savePdf("plot.pdf",531,401);
}
