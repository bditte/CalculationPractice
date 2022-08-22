#include "mainwindow.h"
#include <QAction>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
{
    QWidget*        centralWidget = new QWidget();
    this->setCentralWidget(centralWidget);

    m_layout = new QVBoxLayout();

    createButtons(m_layout);

    centralWidget->setLayout(m_layout);
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

