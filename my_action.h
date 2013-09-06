
#ifndef __MY_ACTION_H__
#define __MY_ACTION_H__

#include <QAction>
#include "kimpanelagent.h"

class MyAction : public QAction
{
    Q_OBJECT

public:
    MyAction(const QString &text, QObject *parent);
    MyAction(const QIcon &icon, const QString &text, QObject *parent);
    virtual ~MyAction();

public:
    void setProp(const KimpanelProperty &prop);
    const KimpanelProperty& getProp();
    void setSkinPath(const QString skinPath);
    const QString getSkinPath();

private:

    KimpanelProperty mProp;
    QString mSkinPath;
};

#endif // __MY_ACTION_H__
