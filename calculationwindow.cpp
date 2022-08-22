#include "calculationwindow.h"
#include <QInputDialog>
#include <QIntValidator>


void    CalculationWindow::startGame()
{
    bool ok;
    m_totalCalculations = QInputDialog::getInt(this, "How many calculations ?",
                                            "Number of calculations", 1, 1, 100, 1, &ok);
    if (!ok)
    {
        backToMenu();
        return ;
    }
    m_userInput->setVisible(true);
    m_calculationLabel->setVisible(true);

    doCalculation();
}

void    CalculationWindow::doCalculation()
{
    m_config.createRandomCalculation();
    m_calculationLabel->setText(m_config.getCalculationString());
}

void    CalculationWindow::displayResult()
{
    m_userInput->hide();
    QString resultString = "Final score : " + QString::number(m_score) + "/" + QString::number(m_totalCalculations);
    m_calculationLabel->setText(resultString);
    m_buttons[0]->setVisible(true);
    m_buttons[1]->setVisible(true);
}

void    CalculationWindow::handleResult()
{
    int result =  m_userInput->text().toInt();
    if (result == m_config.getResult())
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

    m_score = 0;
    m_nbCalculations = 0;
    startGame();
}

void    CalculationWindow::backToMenu()
{
    this->close();
    m_parent->setVisible(true);
}
void    CalculationWindow::createButtons()
{
    m_buttons.push_back(new QPushButton(this));
    m_buttons[0]->setText("Menu");
    m_layout->addWidget(m_buttons[0], Qt::AlignLeft);
    m_buttons[0]->hide();
    connect(m_buttons[0], &QPushButton::pressed, this, &CalculationWindow::backToMenu);

    m_buttons.push_back(new QPushButton(this));
    m_buttons[1]->setText("Play");
    m_layout->addWidget(m_buttons[1], Qt::AlignRight);
    m_buttons[1]->hide();
    connect(m_buttons[1], &QPushButton::pressed, this, &CalculationWindow::restartGame);
}

CalculationWindow::CalculationWindow(QString difficulty, QWidget *parent):
    QMainWindow(parent),
    m_parent(parent),
    m_config(difficulty),
    m_nbCalculations(0),
    m_score(0)
{
    QWidget*        centralWidget = new QWidget();
    this->setCentralWidget(centralWidget);

    m_layout = new QVBoxLayout();
    centralWidget->setLayout(m_layout);

    m_userInput = new QLineEdit(centralWidget);
    m_userInput->setValidator(new QIntValidator(INT_FAST16_MIN, INT_FAST16_MAX, this));
    m_userInput->hide();
    connect(m_userInput, &QLineEdit::editingFinished, this, &CalculationWindow::handleResult);

    m_calculationLabel = new QLabel();
    m_calculationLabel->setAlignment(Qt::AlignHCenter);
    m_calculationLabel->hide();

    m_layout->addWidget(m_calculationLabel);
    m_layout->addWidget(m_userInput);

    createButtons();
    startGame();
}

CalculationWindow::~CalculationWindow()
{

}

