
#include "my_action.h"


MyAction::MyAction(const QString &text, QObject *parent) : QAction(text, parent)
{

}

MyAction::MyAction(const QIcon &icon, const QString &text,
    const KimpanelProperty &prop, QObject *parent) : QAction(icon, text, parent)
{
    this->mProp = prop;
}

MyAction::~MyAction()
{

}

KimpanelProperty MyAction::getProp()
{
    return this->mProp;
}
