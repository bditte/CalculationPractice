#include "mainwindow.h"
#include <QStyle>
#include <QScreen>
#include <QApplication>
#include <QGroupBox>
#include <QValidator>
#include <QMessageBox>

MainWindow::MainWindow(QMainWindow *parent):
    QMainWindow(parent),
    m_pagesWidgets(new QStackedWidget(this))
{
    resize(150, 100);
    this->move(screen()->geometry().center() - frameGeometry().center());

    setupMenuLayouts();

    QWidget*                menuWidget = createMenu();
    CalculationWindow*      easyWidget = new CalculationWindow("Easy", this);
    CalculationWindow*      mediumWidget = new CalculationWindow("Medium", this);
    CalculationWindow*      customWidget = new CalculationWindow("Custom", this);

    m_customWidget = customWidget;

    menuWidget->setLayout(m_menuLayout);

    m_pagesWidgets->addWidget(menuWidget);
    m_pagesWidgets->addWidget(easyWidget);
    m_pagesWidgets->addWidget(mediumWidget);
    m_pagesWidgets->addWidget(customWidget);

    createCustomButtons(menuWidget);


    this->setCentralWidget(m_pagesWidgets);


    connect(easyWidget, &CalculationWindow::gameFinished, this, [this]{ switchWidget(MENU_INDEX); });
    connect(mediumWidget, &CalculationWindow::gameFinished, this, [this]{ switchWidget(MENU_INDEX); });
    connect(customWidget, &CalculationWindow::gameFinished, this, [this]{ switchWidget(MENU_INDEX); });

}

QWidget*    MainWindow::createMenu()
{
    QGroupBox* menu = new QGroupBox("Menu", this);

    QLineEdit* lineEdit = new QLineEdit(menu);
    lineEdit->setValidator(new QIntValidator(1, INT_MAX, lineEdit));
    QLabel* label = new QLabel(menu);
    lineEdit->setMaximumWidth(50);
    label->setText("Number of games");
    m_nbGamesLayout->addWidget(label);
    m_nbGamesLayout->addWidget(lineEdit);

    m_userInputs.push_back(lineEdit);

    QPushButton* easyButton = new QPushButton(menu);
    easyButton->setText("Easy");
    m_buttonsLayout->addWidget(easyButton);

    QPushButton* mediumButton = new QPushButton("Medium", menu);
    mediumButton->setText("Medium");
    m_buttonsLayout->addWidget(mediumButton);

    QPushButton* customButton = new QPushButton("Custom", menu);
    m_buttonsLayout->addWidget(customButton);

    connect(easyButton, &QPushButton::clicked, this, [this]{ switchWidget(EASY_INDEX); });
    connect(mediumButton, &QPushButton::clicked, this, [this]{ switchWidget(MEDIUM_INDEX); });
    connect(customButton, &QPushButton::clicked, this, [this]{ startCustom(); });

    return menu;
}

void    MainWindow::setupMenuLayouts()
{
    m_menuLayout = new QVBoxLayout();
    m_nbGamesLayout = new QHBoxLayout();
    m_buttonsLayout = new QHBoxLayout();
    m_optionsLayout = new QGridLayout();

    m_menuLayout->addLayout(m_nbGamesLayout);
    m_menuLayout->addLayout(m_buttonsLayout);
    m_menuLayout->addLayout(m_optionsLayout);

}

void    MainWindow::createCustomButtons(QWidget* menuWidget)
{
    QLineEdit*  lineEdit;
    QLabel*     label;

    lineEdit = new QLineEdit(menuWidget);
    lineEdit->setValidator(new QIntValidator(INT_MIN, INT_MAX, lineEdit));
    lineEdit->setMaximumWidth(50);
    label = new QLabel("Minimum", menuWidget);
    m_optionsLayout->addWidget(label, 0, 0);
    m_optionsLayout->addWidget(lineEdit, 0, 1);
    m_userInputs.push_back(lineEdit);


    lineEdit = new QLineEdit(menuWidget);
    lineEdit->setValidator(new QIntValidator(INT_MIN, INT_MAX, lineEdit));
    lineEdit->setMaximumWidth(50);
    label = new QLabel("Maxium", lineEdit);
    m_optionsLayout->addWidget(label, 0, 2);
    m_optionsLayout->addWidget(lineEdit, 0, 3);
    m_userInputs.push_back(lineEdit);

}

void    MainWindow::startCustom()
{
    QMessageBox msgBox;

    CalculationWindow*  customWidget = dynamic_cast<CalculationWindow*>(m_pagesWidgets->widget(CUSTOM_INDEX));

    if (checkUserInput())
        return ;

    int min = m_userInputs[1]->text().toInt();
    customWidget->setMin(min);

    int max = m_userInputs[2]->text().toInt();
    customWidget->setMax(max);

    if (min > max)
    {
        msgBox.setText("Minimum value can't be superior to maximum");
        msgBox.exec();
        return ;
    }
    switchWidget(CUSTOM_INDEX);
}

int     MainWindow::checkUserInput()
{
    QMessageBox msgBox;

    if (m_userInputs[1]->text().length() == 0)
    {
        msgBox.setText("Minimum value can't be empty");
        msgBox.exec();
        return (1);
    }

    if (m_userInputs[2]->text().length() == 0)
    {
        msgBox.setText("Maximum value can't be empty");
        msgBox.exec();
        return (1);
    }
    return (0);
}

void    MainWindow::switchWidget(const int& index)
{
    if (m_userInputs[0]->text().length() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Numbers of games can't be empty");
        msgBox.exec();
        return ;
    }
    CalculationWindow*  tmp;

    m_pagesWidgets->setCurrentIndex(index);

    int nbGames = m_userInputs[0]->text().toInt();
    tmp = dynamic_cast<CalculationWindow*>(m_pagesWidgets->currentWidget());


    if (tmp)
    {
        tmp->startGame();
        tmp->setNbCalculations(nbGames);
    }
}


MainWindow::~MainWindow()
{

}

