#include "mainwindow.h"
#include <QAction>
#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>
#include <QGroupBox>

MainWindow::MainWindow(QMainWindow *parent):
    QMainWindow(parent),
    m_pagesWidgets(new QStackedWidget(this)),
    m_sigmapper(new QSignalMapper(this))
{
    resize(300, 200);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                      Qt::AlignCenter,
                                      this->size(),
                                      QApplication::desktop()->availableGeometry()));

    QWidget*                menuWidget = createMenu();
    CalculationWindow*      easyWidget = new CalculationWindow("Easy", this);
    CalculationWindow*      mediumWidget = new CalculationWindow("Medium", this);

    m_pagesWidgets->addWidget(menuWidget);
    m_pagesWidgets->addWidget(easyWidget);
    m_pagesWidgets->addWidget(mediumWidget);



    this->setCentralWidget(m_pagesWidgets);


    connect(easyWidget, &CalculationWindow::gameFinished, this, [this]{ switchWidget(MENU_INDEX); });
    connect(mediumWidget, &CalculationWindow::gameFinished, this, [this]{ switchWidget(MENU_INDEX); });

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

    connect(easyButton, &QPushButton::clicked, this, [this]{ switchWidget(EASY_INDEX); });
    connect(mediumButton, &QPushButton::clicked, this, [this]{ switchWidget(MEDIUM_INDEX); });

    return menu;
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

