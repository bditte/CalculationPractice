#ifndef CALCULATIONCONFIG_H
#define CALCULATIONCONFIG_H

#include <QString>
#include <QRandomGenerator>

#include "calculation.h"

#define EASY_MIN 2
#define EASY_MAX 20
#define EASY_NB 5
#define EASY_OPERATORS "+-x"

#define MEDIUM_MIN -5
#define MEDIUM_MAX 20
#define MEDIUM_NB 5
#define MEDIUM_OPERATORS "+-x"

#define HARD_MIN -50
#define HARD_MAX 50
#define HARD_NB 5
#define HARD_OPERATORS "+-x"


class CalculationConfig
{
public:
    CalculationConfig(const QString&);
    CalculationConfig(const int&, const int&);

    const int&          getMin() const;
    const int&          getMax() const;

    void    setMin(const int&);
    void    setMax(const int&);
    void    setOperators(const QString& );

    Calculation         createRandomCalculation() const;

private:

    long int        getResult(const int&, const int&, const QChar&) const;
    QString         getCalculationString(const int&, const int&, const QChar&) const;
    QChar           getOperator() const;
    int             generateRandomNumber() const;

    int                   m_min;
    int                   m_max;

    QString     m_operators;
    QString     m_difficulty;

};

#endif // CALCULATIONCONFIG_H
