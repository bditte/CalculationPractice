#ifndef CALCULATIONCONFIG_H
#define CALCULATIONCONFIG_H

#include <QString>
#include <QRandomGenerator>

#define EASY_MIN 0
#define EASY_MAX 20
#define EASY_NB 5

class CalculationConfig
{
public:
    CalculationConfig(const QString&);
    CalculationConfig(const int&, const int&);

    const int&     getMin() const;
    const int&     getMax() const;
    const int&     getResult() const;

    void    setMin(const int&);
    void    setMax(const int&);

    void                createRandomCalculation();
    const QString&      getCalculationString() const;
private:

    void    setResult(const int&, const int&, const char&);
    void    setCalculationString(const int&, const int&, const char&);
    char    getOperator() const;

    int         m_min;
    int         m_max;
    int         m_result;

    QString     m_difficulty;
    QString     m_CalculationString;

};

#endif // CALCULATIONCONFIG_H
