#include "menubutton.h"
#include <QDebug>
#include <QLabel>

MenuButton::MenuButton(QString name, QWidget *parent):
    QPushButton(parent),
    m_name(name),
    m_parent(parent)
{
   setText(m_name);
}

MenuButton::~MenuButton()
{

}

void MenuButton::createWindow()
{
   m_parent->setVisible(false);
   CalculationWindow *newWindow = new CalculationWindow(m_name, m_parent);

   newWindow->show();

}
