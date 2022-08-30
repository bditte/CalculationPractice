#include "calculationwindow.h"
#include <QInputDialog>
#include <QIntValidator>
#include <QDebug>
#include <QHeaderView>

void    CalculationWindow::startGame()
{
    m_buttons[0]->setVisible(false);
    m_buttons[1]->setVisible(false);
    m_resultTable->setVisible(false);
    m_resultTable->clear();
    m_calculations.clear();

    m_nbCalculations = 0;
    m_score = 0;

    m_userInput->setVisible(true);
    m_calculationLabel->setVisible(true);

    doCalculation();
}

void    CalculationWindow::doCalculation()
{
    Calculation calcul;

    calcul = m_config.createRandomCalculation();
    while (calcul.result() < INT_MIN && INT_MAX < calcul.result())
        calcul = m_config.createRandomCalculation();

    m_calculations.push_back(calcul);
    m_calculationLabel->setText(calcul.calculationString());
}

void    CalculationWindow::displayResult()
{
    m_userInput->hide();

    QString resultString = "Final score : " + QString::number(m_score) + "/" + QString::number(m_totalCalculations);
    m_calculationLabel->setText(resultString);

    m_buttons[0]->setVisible(true);
    m_buttons[1]->setVisible(true);
    m_resultTable->setVisible(true);

    m_resultTable->setRowCount(m_calculations.size());
    for (int i = 0; i < m_calculations.size(); i++)
    {
        m_resultTable->setItem(i, 0, new QTableWidgetItem(m_calculations[i].calculationString()));
        m_resultTable->setItem(i, 1, new QTableWidgetItem(QString::number(m_calculations[i].result())));
        m_resultTable->setItem(i, 2, new QTableWidgetItem(QString::number(m_calculations[i].userResult())));

        if (m_calculations[i].isCorrect())
        {
            m_resultTable->item(i, 0)->setBackground(QColor(67, 220, 40));
            m_resultTable->item(i, 1)->setBackground(QColor(67, 220, 40));
            m_resultTable->item(i, 2)->setBackground(QColor(67, 220, 40));
        }
        else
        {
            m_resultTable->item(i, 0)->setBackground(QColor(216, 12, 12));
            m_resultTable->item(i, 1)->setBackground(QColor(216, 12, 12));
            m_resultTable->item(i, 2)->setBackground(QColor(216, 12, 12));
        }
        m_resultTable->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        m_resultTable->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        m_resultTable->item(i, 2)->setTextAlignment(Qt::AlignCenter);

    }
}

void    CalculationWindow::handleResult()
{
    m_calculations[m_nbCalculations].setUserResult(m_userInput->text().toInt());



    if (m_calculations[m_nbCalculations].isCorrect())
        m_score++;
    m_userInput->clear();
    if (++m_nbCalculations < m_totalCalculations)
        doCalculation();
    else
        displayResult();
}

void    CalculationWindow::restartGame()
{
    m_buttons[0]->hide();
    m_buttons[1]->hide();

    m_calculations.clear();
    m_score = 0;
    m_nbCalculations = 0;
    startGame();
}

void    CalculationWindow::backToMenu()
{
    emit    gameFinished();
}
void    CalculationWindow::createButtons()
{
    m_buttons.push_back(new QPushButton(this));
    m_buttons[0]->setText("Menu");
    m_layout->addWidget(m_buttons[0], Qt::AlignLeft);
    m_buttons[0]->hide();
    connect(m_buttons[0], &QPushButton::clicked, this, &CalculationWindow::backToMenu);

    m_buttons.push_back(new QPushButton(this));
    m_buttons[1]->setText("Play Again");
    m_layout->addWidget(m_buttons[1], Qt::AlignRight);
    m_buttons[1]->hide();
    connect(m_buttons[1], &QPushButton::pressed, this, &CalculationWindow::restartGame);
}

int   getTableWidth(QTableWidget* tbl)
{
    int w = tbl->verticalHeader()->width() + 4;

    for (int i = 0; i < tbl->columnCount(); i++)
     w += tbl->columnWidth(i);

    return w;
}

CalculationWindow::CalculationWindow(QString difficulty, QWidget *parent):
    QGroupBox(parent),
    m_parent(parent),
    m_config(difficulty),
    m_nbCalculations(0),
    m_score(0)
{
    //this->resize(300, 350);

    m_totalCalculations = 5;

    m_layout = new QVBoxLayout();
    setLayout(m_layout);

    m_userInput = new QLineEdit(this);
    m_userInput->setValidator(new QIntValidator(INT_MIN, INT_MAX, this));

    connect(m_userInput, &QLineEdit::editingFinished, this, &CalculationWindow::handleResult);

    m_calculationLabel = new QLabel();
    m_calculationLabel->setAlignment(Qt::AlignHCenter);

    m_resultTable = new QTableWidget(1, 3, this);
    m_resultTable->verticalHeader()->setVisible(false);
    m_resultTable->horizontalHeader()->setVisible(false);
    int width = getTableWidth(m_resultTable);

    m_resultTable->setColumnWidth(0, width * 0.6 + 4);
    m_resultTable->setColumnWidth(1, width * 0.2 + 4);
    m_resultTable->setColumnWidth(2, width * 0.2 + 3);

    m_resultTable->hide();
    m_layout->addWidget(m_calculationLabel);
    m_layout->addWidget(m_resultTable);
    m_layout->addWidget(m_userInput);

    createButtons();
}

CalculationWindow::~CalculationWindow()
{

}

void    CalculationWindow::setMin(int val) { m_config.setMin(val); }
void    CalculationWindow::setMax(int val) { m_config.setMax(val); }
void    CalculationWindow::setNbCalculations(int val) { m_totalCalculations = val; }
void    CalculationWindow::setOperators(const QString& val) { m_config.setOperators(val); }



