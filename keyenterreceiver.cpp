#include "keyenterreceiver.h"
#include <QKeyEvent>

keyEnterReceived::keyEnterReceived(MainWindow *window):
    m_window(window)
{

}

keyEnterReceived::~keyEnterReceived()
{

}

bool   keyEnterReceived::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type()==QEvent::KeyPress)
    {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) )
        {
            m_window->startCustom();
        }
        else
            return QObject::eventFilter(obj, event);
        return true;
    }
    else
        return QObject::eventFilter(obj, event);
    return false;
}
