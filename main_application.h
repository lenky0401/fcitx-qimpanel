
#ifndef __MAIN_APPLICATION_H__
#define __MAIN_APPLICATION_H__

#include <QDeclarativeView>
#include <QApplication>
#include <QMouseEvent>
#include <QBoxLayout>
#include <QStackedWidget>
#include "kimpanelagent.h"

class MainApplication : public QApplication
{
    Q_OBJECT
public:
    MainApplication(int &argc, char **argv);
    virtual ~MainApplication();
    bool setup();

private:
    QDeclarativeView *m_view;
    PanelAgent *m_agent;
};

#endif // __MAIN_APPLICATION_H__
