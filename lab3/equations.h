#ifndef EQUATIONS_H
#define EQUATIONS_H
#include <QVector>


class Equations
{
private:
    QVector<double> _powers;
    QVector<double> _numbers;
    int _num;
public:
    Equations();
    QVector<double> powers() const;
    void setPowers(const QVector<double> &powers);
    QVector<double> numbers() const;
    void setNumbers(const QVector<double> &numbers);
    int num() const;
    void setNum(int num);
    void add_power(double pow);
    void add_number(double num);
};

#endif // EQUATIONS_H
