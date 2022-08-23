#include "mainwindow.h"
#include <QAction>
#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>
#include <QGroupBox>

MainWindow::MainWindow(QMainWindow *parent):
    QMainWindow(parent),
    m_pagesWidgets(new QStackedWidget),
    m_sigmapper(new QSignalMapper(this))
{
    resize(300, 200);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                      Qt::AlignCenter,
                                      this->size(),
                                      QApplication::desktop()->availableGeometry()));

    QWidget*    menuWidget = createMenu();
    QWidget*    easyWidget = new CalculationWindow("Easy", this);

    m_pagesWidgets->addWidget(menuWidget);
    m_pagesWidgets->addWidget(easyWidget);





    this->setCentralWidget(m_pagesWidgets);

    //createButtons(m_layout);
    //m_layout = new QVBoxLayout();
    //m_pagesWidgets->currentWidget()->setLayout(m_layout);
}

QWidget*    MainWindow::createMenu()
{
    QGroupBox* menu = new QGroupBox("Menu", this);
    //QVBoxLayout*    menuLayout = new QVBoxLayout();

    QPushButton* easyButton = new QPushButton(menu);
    easyButton->setText("Easy");
    easyButton->move(100, 100);
    QPushButton* mediumButton = new QPushButton("Medium", menu);
    mediumButton->setText("Medium");
    mediumButton->move(0, 100);

    connect(easyButton, &QPushButton::clicked, this, [this]{ switchWidget(1); });

    return menu;
}

QWidget*    MainWindow::createEasy()
{
    QGroupBox* menu = new QGroupBox("Easy", this);
    //QVBoxLayout*    menuLayout = new QVBoxLayout();

    QPushButton* easyButton = new QPushButton(menu);
    connect(easyButton, &QPushButton::clicked, this, [this]{ switchWidget(0); });
    easyButton->setText("In game");
    easyButton->move(100, 100);
    return menu;
}

void    MainWindow::switchWidget(const int& index)
{
    m_pagesWidgets->setCurrentIndex(index);
    CalculationWindow*  tmp;

    try {
        tmp = dynamic_cast<CalculationWindow*>(m_pagesWidgets->currentWidget());
        tmp->startGame();
    } catch (...) {
    }
}

void    MainWindow::createButtons(QVBoxLayout* layout)
{
    QVector<QString>        buttonsNames;

    buttonsNames.push_back("Easy");
    buttonsNames.push_back("Medium");

    for (int i = 0; i < buttonsNames.size(); i++)
    {
        MenuButton* tmpButton = new MenuButton(buttonsNames[i], this);

        m_buttons.push_back(tmpButton);
        layout->addWidget(tmpButton);
        connect(tmpButton, &QPushButton::clicked, tmpButton, &MenuButton::createWindow);
    }
}

MainWindow::~MainWindow()
{

}

