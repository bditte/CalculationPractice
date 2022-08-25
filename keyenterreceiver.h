#ifndef KEYENTERRECEIVER_H
#define KEYENTERRECEIVER_H

#include <QObject>

#include "mainwindow.h"

class keyEnterReceived: public QObject
{
    Q_OBJECT
public:
    keyEnterReceived(MainWindow* = nullptr);
    virtual ~keyEnterReceived();
protected:
    bool eventFilter(QObject* obj, QEvent* event);

private:
    MainWindow*     m_window;
};

#endif // KEYENTERRECEIVER_H
