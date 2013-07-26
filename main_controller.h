
#ifndef __MAIN_CONTROLLER_H__
#define __MAIN_CONTROLLER_H__

#include <QObject>
#include <QApplication>
#include "main_model.h"
#include "kimpanelagent.h"

class MainController : public QApplication
{
    Q_OBJECT

public:
    MainController(int &argc, char **argv);
    virtual ~MainController();
    bool init();

private:
    MainModel *mModel;
    PanelAgent *mAgent;
    QDeclarativeView *mView;

public slots:
    void updatePreeditText(const QString inputString, 
        QList<TextAttribute> attributes);

    void updateLookupTable(const KimpanelLookupTable &lookup_table);
    void updateLookupTableFull(const KimpanelLookupTable &lookup_table,
        int cursor, int layout);

    void updateSpotLocation(int x, int y);
    void updateSpotRect(int x, int y, int w, int h);
    void showLookupTable(bool to_show);
    void updateLookupTableCursor(int pos);
    void updatePreeditCaret(int pos);

public:
    Q_INVOKABLE void getPrevPage();
    Q_INVOKABLE void getNextPage();
    Q_INVOKABLE void selectCandidate(int index);
};

#endif // __MAIN_CONTROLLER_H__
