#ifndef MenuButton_H
#define MenuButton_H

#include <QVBoxLayout>
#include <QList>
#include <QMainWindow>
#include <QStackedWidget>
#include <QSignalMapper>
#include "menubutton.h"

#define MENU_INDEX 0
#define EASY_INDEX 1
#define MEDIUM_INDEX 2

class MainWindow: public QMainWindow {


public:
    MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();

public slots:
    void            switchWidget(const int&);

private:
    void            createButtons(QVBoxLayout*);
    QWidget*        createMenu();

    QVBoxLayout*            m_layout;
    QList<MenuButton *>     m_buttons;
    QStackedWidget*         m_pagesWidgets;
    QSignalMapper*          m_sigmapper;

};

#endif // MenuButton_H
