#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QPushButton>
#include <calculationwindow.h>

class MenuButton : public QPushButton
{
    Q_OBJECT

public:
    MenuButton(QString name, QWidget *parent = NULL);
    ~MenuButton();

    QString     getName() const { return m_name; }
    void        setName(const QString& text) { m_name = text; }

public slots:
    void        createWindow();

private:
    QString     m_name;
    QWidget*    m_parent;

};
#endif // MENUBUTTON_H
