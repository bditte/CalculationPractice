#include "calculation.h"

Calculation::Calculation():
    m_calculationString(),
    m_userResult(),
    m_result()
{

}

Calculation::Calculation(const QString& calculationString, const long int& result):
    m_calculationString(calculationString),
    m_userResult(0),
    m_result(result)
{

}

QString     Calculation::calculationString() const { return m_calculationString; }
int         Calculation::userResult() const { return m_userResult; }
int         Calculation::result() const{ return m_result; }

bool        Calculation::isCorrect() const { return m_userResult == m_result ? true : false; }

void        Calculation::setCalculationString(const QString &val){ m_calculationString = val; }
void        Calculation::setUserResult(const long int &val){ m_userResult = val; }
void        Calculation::setResult(const long int &val){ m_result = val; }
