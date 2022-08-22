#ifndef MenuButton_H
#define MenuButton_H

#include <QVBoxLayout>
#include <QList>
#include <QMainWindow>

#include "menubutton.h"

class MainWindow: public QMainWindow {
public:
    MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();

private:
    void            createButtons(QVBoxLayout*);

    QVBoxLayout*            m_layout;
    QList<MenuButton *>     m_buttons;

};

#endif // MenuButton_H
