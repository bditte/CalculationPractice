#ifndef MenuButton_H
#define MenuButton_H

#include <QVBoxLayout>
#include <QList>
#include <QMainWindow>
#include <QStackedWidget>
#include <QSignalMapper>
#include "menubutton.h"

class MainWindow: public QMainWindow {

Q_OBJECT

public:
    MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();

public slots:
    void            switchWidget(const int&);
private:
    void            createButtons(QVBoxLayout*);
    QWidget*        createMenu();
    QWidget*        createEasy();

    QVBoxLayout*            m_layout;
    QList<MenuButton *>     m_buttons;
    QStackedWidget*         m_pagesWidgets;
    QSignalMapper*          m_sigmapper;

};

#endif // MenuButton_H
