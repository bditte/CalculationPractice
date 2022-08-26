#ifndef CALCULATIONWINDOW_H
#define CALCULATIONWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QList>
#include <QPushButton>
#include <QGroupBox>

#include "calculation.h"
#include "calculationconfig.h"

class CalculationWindow: public QGroupBox
{
    Q_OBJECT

public:
    CalculationWindow(QString difficulty, QWidget *parent = nullptr);
    ~CalculationWindow();

    int     getMin() const;
    int     getMax() const;
    int     getNbCalculations() const;

    void    setMin(int);
    void    setMax(int);
    void    setNbCalculations(int);
    void    setOperators(const QString&);

    void    startGame();

signals:
    void    gameFinished();

private slots:
    void    handleResult();
    void    restartGame();
    void    backToMenu();

private:
    void                doCalculation();
    void                displayResult();
    void                createButtons();

    QWidget*            m_parent;

    CalculationConfig   m_config;

    int                 m_nbCalculations;
    int                 m_totalCalculations;
    int                 m_score;
    QString             m_difficulty;

    QVBoxLayout*            m_layout;
    QList<QPushButton *>    m_buttons;
    QLineEdit*              m_userInput;
    QLabel*                 m_calculationLabel;
    QList<Calculation>      m_calculations;
};

#endif // CALCULATIONWINDOW_H
