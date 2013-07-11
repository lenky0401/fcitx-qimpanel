
#ifndef __MAIN_CONTROLLER_H__
#define __MAIN_CONTROLLER_H__

#include <QObject>
#include "main_model.h"
#include "kimpanelagent.h"

class MainController : public QObject
{
    Q_OBJECT

public:
    MainController();
    virtual ~MainController();
    bool init();

private:
    MainModel *mModel;
    PanelAgent *mAgent;

public
slots:
    void updatePreeditText(const QString inputString, 
        QList<TextAttribute> attributes);

    //lookup_table里存放各个候选词
    void updateLookupTable(const KimpanelLookupTable &lookup_table);
    void updateLookupTableFull(const KimpanelLookupTable &lookup_table,
        int cursor, int layout);

public:
	MainModel* getModel() {
		return mModel;
	}
};

#endif // __MAIN_CONTROLLER_H__
