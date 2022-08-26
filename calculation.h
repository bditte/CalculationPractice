#ifndef CALCULATION_H
#define CALCULATION_H

#include <QString>

class Calculation
{
public:
    Calculation();
    Calculation(const QString&, const long int&);

    QString         calculationString() const;
    int             userResult() const;
    int             result() const;

    bool            isCorrect() const;

    void            setCalculationString(const QString&);
    void            setUserResult(const long int&);
    void            setResult(const long int&);

private:
    QString             m_calculationString;
    long int            m_userResult;
    long int            m_result;
};

#endif // CALCULATION_H
