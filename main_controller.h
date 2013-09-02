
#ifndef __MAIN_CONTROLLER_H__
#define __MAIN_CONTROLLER_H__

#include <QObject>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>
#include <QTimer>
#include "main_model.h"
#include "system_tray_menu.h"
#include "kimpanelagent.h"
#include "toplevel.h"

//必须与FcitxCandidateLayoutHint的定义一致
enum CandidateLayout {
    CLH_NotSet,
    CLH_Vertical,
    CLH_Horizontal
};

class MainController : public QApplication
{
    Q_OBJECT

public:
    MainController(int &argc, char **argv);
    virtual ~MainController();
    bool init();

private:
    TopLevel *mTopLevel;
    MainModel *mModel;
    PanelAgent *mAgent;
    QDeclarativeView *mView;
    QUrl mUrl;
    QTimer *mTimer;
    QSystemTrayIcon *mSystemTray;
    SystemTrayMenu *mTrayMenu;
    CandidateLayout mLayout;

public slots:
    void hideTips();
    void showTips(const QString tipsString);
    void updateProperty(const KimpanelProperty &prop);
    void updatePreeditText(const QString inputString, 
        QList<TextAttribute> attributes);

    void updateLookupTable(const KimpanelLookupTable &lookup_table);
    void updateLookupTableFull(const KimpanelLookupTable &lookup_table,
        int cursor, int layout);

    void updateSpotLocation(int x, int y);
    void updateSpotRect(int x, int y, int w, int h);
    void showPreedit(bool to_show);
    void showAux(bool to_show);
    void updateAux(const QString &text, const QList<TextAttribute> &attr);
    void showLookupTable(bool to_show);
    void updateLookupTableCursor(int pos);
    void updatePreeditCaret(int pos);

public:
    Q_INVOKABLE void getPrevPage();
    Q_INVOKABLE void getNextPage();
    Q_INVOKABLE void selectCandidate(int index);
};

#endif // __MAIN_CONTROLLER_H__
