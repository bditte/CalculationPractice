#include "calculationconfig.h"
#include <QTextStream>

char    CalculationConfig::getOperator() const
{
    int     n = QRandomGenerator::global()->generate() % 4;

    if (n == 0)
        return '+';
    if (n == 1)
        return '-';
    if (n == 2)
        return '*';
    return '/';
}

void     CalculationConfig::setResult(const int& a, const int& b, const char& op)
{
    if (op == '*')
        m_result =  a * b;
    else if (op == '/')
        m_result = a / b;
    else if (op == '+')
        m_result = a + b;
    else
        m_result = a - b;
    return ;
}

void    CalculationConfig::setCalculationString(const int &a, const int &b, const char &op)
{
    m_CalculationString = QString::number(a) + " " + op + " " + QString::number(b);
}

void    CalculationConfig::createRandomCalculation()
{
    QTextStream out(stdout);

    int a = m_min + QRandomGenerator::global()->generate() % m_max;
    int b = m_min + QRandomGenerator::global()->generate() % m_max;
    char op = getOperator();

    setResult(a, b, op);
    setCalculationString(a, b, op);
}

CalculationConfig::CalculationConfig(const QString& difficulty):
    m_min(),
    m_max(),
    m_difficulty(difficulty)
{
    if (m_difficulty == "Easy")
    {
        m_min = EASY_MIN;
        m_max = EASY_MAX;
    }
}

CalculationConfig::CalculationConfig(const int& min, const int& max):
    m_min(min),
    m_max(max),
    m_difficulty("CUSTOM")
{
    srand(time(NULL));
}

const int&      CalculationConfig::getMin() const { return m_min; };
const int&      CalculationConfig::getMax() const { return m_max; };
const int&      CalculationConfig::getResult() const { return m_result; }
const QString&  CalculationConfig::getCalculationString() const { return m_CalculationString; }

void    CalculationConfig::setMin(const int& val) { m_min = val; }
void    CalculationConfig::setMax(const int& val) { m_max = val; }
