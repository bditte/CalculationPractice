#ifndef CALCULATIONCONFIG_H
#define CALCULATIONCONFIG_H

#include <QString>
#include <QRandomGenerator>

#define EASY_MIN 2
#define EASY_MAX 20
#define EASY_NB 5
#define EASY_OPERATORS "+-x"

#define MEDIUM_MIN 2
#define MEDIUM_MAX 20
#define MEDIUM_NB 5
#define MEDIUM_OPERATORS "+-x"


class CalculationConfig
{
public:
    CalculationConfig(const QString&);
    CalculationConfig(const int&, const int&);

    const int&     getMin() const;
    const int&     getMax() const;
    const long int&     getResult() const;

    void    setMin(const int&);
    void    setMax(const int&);

    void                createRandomCalculation();
    const QString&      getCalculationString() const;
private:

    void    setResult(const int&, const int&, const QChar&);
    void    setCalculationString(const int&, const int&, const QChar&);
    QChar   getOperator() const;
    int     generateRandomNumber() const;

    int                   m_min;
    int                   m_max;
    long int              m_result;

    QString     m_operators;
    QString     m_difficulty;
    QString     m_CalculationString;

    bool        m_allowNegativeNbrs;

};

#endif // CALCULATIONCONFIG_H
