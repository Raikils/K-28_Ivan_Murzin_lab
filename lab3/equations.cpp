#include "equations.h"

QVector<double> Equations::powers() const
{
    return _powers;
}

void Equations::setPowers(const QVector<double> &powers)
{
    _powers = powers;
}

QVector<double> Equations::numbers() const
{
    return _numbers;
}

void Equations::setNumbers(const QVector<double> &numbers)
{
    _numbers = numbers;
}

int Equations::num() const
{
    return _num;
}

void Equations::setNum(int num)
{
    _num = num;
}

void Equations::add_power(double pow)
{
    _powers.push_back(pow);
}

void Equations::add_number(double num)
{
    _numbers.push_back(num);
}

Equations::Equations()
{

}
