
#ifndef __MY_ACTION_H__
#define __MY_ACTION_H__

#include <QAction>
#include "kimpanelagent.h"

class MyAction : public QAction
{
    Q_OBJECT

public:
    MyAction(const QString &text, QObject *parent);
    MyAction(const QIcon &icon, const QString &text, const KimpanelProperty &prop, QObject *parent);
    virtual ~MyAction();

public:
    KimpanelProperty getProp();

private:
    KimpanelProperty mProp;
};

#endif // __MY_ACTION_H__
