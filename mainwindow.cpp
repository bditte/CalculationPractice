#include "mainwindow.h"
#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>
#include <QGroupBox>
#include <QValidator>
#include <QMessageBox>

MainWindow::MainWindow(QMainWindow *parent):
    QMainWindow(parent),
    m_pagesWidgets(new QStackedWidget(this))
{
    resize(300, 500);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                      Qt::AlignCenter,
                                      this->size(),
                                      QApplication::desktop()->availableGeometry()));

    m_layout = new QVBoxLayout();

    QWidget*                menuWidget = createMenu();
    CalculationWindow*      easyWidget = new CalculationWindow("Easy", this);
    CalculationWindow*      mediumWidget = new CalculationWindow("Medium", this);
    CalculationWindow*      customWidget = new CalculationWindow("Custom", this);

    m_customWidget = customWidget;

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
    //QVBoxLayout*    menuLayout = new QVBoxLayout();

    menu->setLayout(m_layout);

    QPushButton* easyButton = new QPushButton(menu);
    easyButton->setText("Easy");
    easyButton->move(100, 100);

    QPushButton* mediumButton = new QPushButton("Medium", menu);
    mediumButton->setText("Medium");
    mediumButton->move(0, 100);

    QPushButton* customButton = new QPushButton("Custom", menu);
    customButton->move(200, 100);

    connect(easyButton, &QPushButton::clicked, this, [this]{ switchWidget(EASY_INDEX); });
    connect(mediumButton, &QPushButton::clicked, this, [this]{ switchWidget(MEDIUM_INDEX); });
    connect(customButton, &QPushButton::clicked, this, [this]{ startCustom(); });

    return menu;
}

void    MainWindow::createCustomButtons(QWidget* menuWidget)
{
    QLineEdit*  lineEdit;
    QLabel*     label;

    lineEdit = new QLineEdit(menuWidget);
    lineEdit->setValidator(new QIntValidator(INT_MIN, INT_MAX, menuWidget));
    label = new QLabel(lineEdit);
    label->setText("Minimum:");

    m_layout->addWidget(lineEdit);
    m_userInputs.push_back(lineEdit);


    lineEdit = new QLineEdit(menuWidget);
    lineEdit->setValidator(new QIntValidator(INT_MIN, INT_MAX, menuWidget));
    label = new QLabel(lineEdit);
    label->setText("Maximum");

    m_layout->addWidget(lineEdit);
    m_userInputs.push_back(lineEdit);

    lineEdit = new QLineEdit(menuWidget);
    lineEdit->setValidator(new QIntValidator(1, INT_MAX, menuWidget));
    label = new QLabel(lineEdit);
    label->setText("Number of games");

    m_layout->addWidget(lineEdit);
    m_userInputs.push_back(lineEdit);
}

void    MainWindow::startCustom()
{
    QMessageBox msgBox;

    CalculationWindow*  customWidget = dynamic_cast<CalculationWindow*>(m_pagesWidgets->widget(CUSTOM_INDEX));

    if (m_userInputs[0]->text().length() == 0)
    {
        msgBox.setText("Minimum value can't be empty");
        msgBox.exec();
        return ;
    }
    int min = m_userInputs[0]->text().toInt();
    customWidget->setMin(min);

    if (m_userInputs[1]->text().length() == 0)
    {
        msgBox.setText("Maximum value can't be empty");
        msgBox.exec();
        return ;
    }
    int max = m_userInputs[1]->text().toInt();
    customWidget->setMax(max);

    if (m_userInputs[1]->text().length() == 0)
    {
        msgBox.setText("Numbers of games can't be empty");
        msgBox.exec();
        return ;
    }
    int nbGames = m_userInputs[2]->text().toInt();
    customWidget->setNbCalculations(nbGames);

    if (min > max)
    {
        msgBox.setText("Minimum value can't be superior to maximum");
        msgBox.exec();
        return ;
    }
    switchWidget(CUSTOM_INDEX);
}

void    MainWindow::switchWidget(const int& index)
{
    m_pagesWidgets->setCurrentIndex(index);
    CalculationWindow*  tmp;

    tmp = dynamic_cast<CalculationWindow*>(m_pagesWidgets->currentWidget());

    if (tmp)
        tmp->startGame();
}


MainWindow::~MainWindow()
{

}

