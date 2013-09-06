
#ifndef __SKIN_MENU_H__
#define __SKIN_MENU_H__

#include <QMenu>
#include <QIcon>
#include "../my_action.h"

class SkinMenu : public QMenu
{
    Q_OBJECT

public:
    SkinMenu(const QString &title, QWidget *parent);
    virtual ~SkinMenu();

private slots:
    void triggerUpdateSkinListMenu();
    void menuItemOnClick(QAction* action);

private:
    QString mCurtSkinLabel;

    MyAction *mSkinTypeMenu;
};

#endif // __SKIN_MENU_H__
