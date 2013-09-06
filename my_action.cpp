
#include "my_action.h"


MyAction::MyAction(const QString &text, QObject *parent) : QAction(text, parent)
{

}

MyAction::MyAction(const QIcon &icon, const QString &text, QObject *parent)
    : QAction(icon, text, parent)
{

}

MyAction::~MyAction()
{

}

void MyAction::setProp(const KimpanelProperty &prop)
{
    this->mProp = prop;
}

const KimpanelProperty& MyAction::getProp()
{
    return this->mProp;
}

void MyAction::setSkinPath(const QString skinPath)
{
    this->mSkinPath = skinPath;
}

const QString MyAction::getSkinPath()
{
    return this->mSkinPath;
}

