#include <QDebug>
#include <QDir>

#include <fcitx-config/fcitx-config.h>

#include "skinmenu.h"
#include "../main_controller.h"
#include "../my_action.h"
#include "skinfcitx.h"

SkinMenu::SkinMenu(const QString &title, QWidget *parent)
    : QMenu(title, parent)
{
    mSkinTypeMenu = NULL;
    triggerUpdateSkinListMenu();

    if (mSkinTypeMenu)
        menuItemOnClick(mSkinTypeMenu);

    QObject::connect(this, SIGNAL(aboutToShow()), this,
        SLOT(triggerUpdateSkinListMenu()));

    QObject::connect(this, SIGNAL(triggered(QAction*)), this,
        SLOT(menuItemOnClick(QAction *)));
}

SkinMenu::~SkinMenu()
{

}

void SkinMenu::triggerUpdateSkinListMenu()
{
    int i;
    size_t len;
    QDir skinDir;
    bool checked = false;
    MyAction *firstMenu = NULL, *menu;
    QFileInfoList list;
    QFileInfoList::Iterator iter;
    char **skinPath = FcitxXDGGetPathWithPrefix(&len, "skin");
    QString skinType = MainController::self()->getSkinType();

    this->clear();
    for (i = 0; i < len; i ++) {
        skinDir = QDir(skinPath[i]);
        if (!skinDir.exists())
            continue;

        skinDir.setFilter(QDir::Dirs);
        list = skinDir.entryInfoList();
        for (iter = list.begin(); iter != list.end(); ++ iter) {
            if (iter->isDir() && "." != iter->fileName() && ".." != iter->fileName()) {
                menu = new MyAction(iter->fileName(), this);
                //qDebug() << iter->absoluteFilePath();
                menu->setSkinPath(iter->absoluteFilePath() + "/");
                this->addAction(menu);
                if (firstMenu == NULL)
                    firstMenu = menu;
                menu->setCheckable(true);
                if (iter->fileName() == skinType) {
                    checked = true;
                    menu->setChecked(true);
                    mSkinTypeMenu = menu;
                }
            }
        }
    }
    if (!checked)
        firstMenu->setChecked(true);

    if (mSkinTypeMenu == NULL)
        mSkinTypeMenu = firstMenu;

    FcitxXDGFreePath(skinPath);
}

void SkinMenu::menuItemOnClick(QAction *action)
{
    SkinBase *skin;
    MyAction *myAction = (MyAction *)action;
    mCurtSkinLabel = myAction->text();

    skin = new SkinFcitx;
    MainController::self()->setSkinBase(skin);
    skin->loadSkin(myAction->getSkinPath());
}
