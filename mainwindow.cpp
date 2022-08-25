#include "mainwindow.h"
#include <QStyle>
#include <QScreen>
#include <QApplication>
#include <QGroupBox>
#include <QValidator>
#include <QMessageBox>
#include <QCheckBox>

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
    QCheckBox*  checkBox;
    QFont       font;
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

    label = new QLabel("Operators:");
    m_optionsLayout->addWidget(label, 1, 0);

    checkBox = new QCheckBox("+", menuWidget);
    m_optionsLayout->addWidget(checkBox, 1, 1);
    checkBox->setChecked(true);

    font = checkBox->font();
    font.setPointSize(14);
    checkBox->setFont(font);
    m_userInputs.push_back(checkBox);

    checkBox = new QCheckBox("-", menuWidget);
    m_optionsLayout->addWidget(checkBox, 1, 2);
    checkBox->setChecked(true);
    checkBox->setFont(font);
    m_userInputs.push_back(checkBox);

    checkBox = new QCheckBox("/", menuWidget);
    m_optionsLayout->addWidget(checkBox, 1, 3);
    checkBox->setChecked(true);
    checkBox->setFont(font);
    m_userInputs.push_back(checkBox);

    checkBox = new QCheckBox("x", menuWidget);
    m_optionsLayout->addWidget(checkBox, 1, 4);
    checkBox->setChecked(true);
    checkBox->setFont(font);
    m_userInputs.push_back(checkBox);

}

void    MainWindow::startCustom()
{
    QMessageBox msgBox;

    CalculationWindow*  customWidget = dynamic_cast<CalculationWindow*>(m_pagesWidgets->widget(CUSTOM_INDEX));

    if (checkUserInput(customWidget))
        return ;
    QLineEdit*          userInput;

    userInput = dynamic_cast<QLineEdit*>(m_userInputs[1]);

    int min = userInput->text().toInt();
    customWidget->setMin(min);

    userInput = dynamic_cast<QLineEdit*>(m_userInputs[2]);

    int max = userInput->text().toInt();
    customWidget->setMax(max);

    if (min > max)
    {
        msgBox.setText("Minimum value can't be superior to maximum");
        msgBox.exec();
        return ;
    }
    switchWidget(CUSTOM_INDEX);
}

int     MainWindow::checkUserInput(CalculationWindow* customWidget)
{
    QMessageBox msgBox;
    QLineEdit*          userInput;

    userInput = dynamic_cast<QLineEdit*>(m_userInputs[1]);
    if (userInput->text().length() == 0)
    {
        msgBox.setText("Minimum value can't be empty");
        msgBox.exec();
        return (1);
    }

    userInput = dynamic_cast<QLineEdit*>(m_userInputs[2]);
    if (userInput->text().length() == 0)
    {
        msgBox.setText("Maximum value can't be empty");
        msgBox.exec();
        return (1);
    }
    QString     operators;
    QCheckBox   *checkBox;
    for (int i = 3; i < 7; i++)
    {
        checkBox = dynamic_cast<QCheckBox*>(m_userInputs[i]);
        if (checkBox->isChecked())
            operators += checkBox->text();
    }
    if (operators.length() == 0)
    {
        msgBox.setText("Atleast one operator must be selected");
        msgBox.exec();
        return (1);
    }
    customWidget->setOperators(operators);
    return (0);
}

void    MainWindow::switchWidget(const int& index)
{
    if (index == MENU_INDEX)
    {
        m_pagesWidgets->setCurrentIndex(index);
        return ;
    }

    CalculationWindow*  tmp;
    QMessageBox         msgBox;
    QLineEdit*          userInput;

    userInput = dynamic_cast<QLineEdit*>(m_userInputs[0]);

    if (userInput->text().length() == 0)
    {
        msgBox.setText("Numbers of games can't be empty");
        msgBox.exec();
        return ;
    }

    int nbGames = userInput->text().toInt();
    if (nbGames == 0)
    {
        msgBox.setText("Numbers of games can't be 0");
        msgBox.exec();
        return ;
    }
    m_pagesWidgets->setCurrentIndex(index);
    tmp = dynamic_cast<CalculationWindow*>(m_pagesWidgets->currentWidget());

    if (tmp)
    {
        tmp->setNbCalculations(nbGames);
        tmp->startGame();
    }
}


MainWindow::~MainWindow()
{

}

