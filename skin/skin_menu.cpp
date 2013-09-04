#include <QDebug>
#include <QDir>

#include <fcitx-config/fcitx-config.h>

#include "skin_menu.h"
#include "../my_action.h"

SkinMenu::SkinMenu(const QString &title, QWidget *parent)
    : QMenu(title, parent)
{
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
    QDir skin_dir;
    bool checked = false;
    QAction *firstMenu = NULL, *menu;
    QFileInfoList list;
    QFileInfoList::Iterator list_iter;
    char **skin_path = FcitxXDGGetPathWithPrefix(&len, "skin");

    this->clear();
    for (i = 0; i < len; i ++) {
        skin_dir = QDir(skin_path[i]);
        if (!skin_dir.exists())
            continue;

        skin_dir.setFilter(QDir::Dirs);
        list = skin_dir.entryInfoList();
        for (list_iter = list.begin(); list_iter != list.end(); ++ list_iter) {
            if (list_iter->isDir() && "." != list_iter->fileName() && ".." != list_iter->fileName()) {
                menu = new MyAction(list_iter->fileName(), this);
                this->addAction(menu);
                if (firstMenu == NULL)
                    firstMenu = menu;
                menu->setCheckable(true);
                if (list_iter->fileName() == this->mCurtSkinLabel) {
                    checked = true;
                    menu->setChecked(true);
                }
            }
        }
    }
    if (!checked)
        firstMenu->setChecked(true);

    FcitxXDGFreePath(skin_path);
}

void SkinMenu::menuItemOnClick(QAction *action)
{
    MyAction *myAction = (MyAction *)action;
    mCurtSkinLabel = myAction->text();

    //更换皮肤逻辑
    qDebug() << myAction->text();
}
