
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

    void UpdateLookupTable(const QStringList &labels,
        const QStringList &candis, const QStringList &attrlists,
        bool has_prev, bool has_next);

public:
	MainModel* getModel() {
		return mModel;
	}
};

#endif // __MAIN_CONTROLLER_H__
