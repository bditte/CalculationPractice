#ifndef MenuButton_H
#define MenuButton_H

#include <QVBoxLayout>
#include <QList>
#include <QMainWindow>
#include <QStackedWidget>
#include <QSignalMapper>
#include <QPushButton>

#include "calculationwindow.h"

#define MENU_INDEX 0
#define EASY_INDEX 1
#define MEDIUM_INDEX 2
#define CUSTOM_INDEX 3


class MainWindow: public QMainWindow {


public:
    MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();

public slots:
    void            switchWidget(const int&);
    void            startCustom();

private:
    void            setupMenuLayouts();
    void            createCustomButtons(QWidget*);
    QWidget*        createMenu();
    int             checkUserInput(CalculationWindow*);

    QVBoxLayout*            m_menuLayout;
    QHBoxLayout*            m_nbGamesLayout;
    QHBoxLayout*            m_buttonsLayout;
    QGridLayout*            m_optionsLayout;
    QStackedWidget*         m_pagesWidgets;
    CalculationWindow*      m_customWidget;
    QList<QWidget*>         m_userInputs;

};

#endif // MenuButton_H
