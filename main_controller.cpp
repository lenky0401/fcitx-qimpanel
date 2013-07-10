
#include "main_model.h"
#include "main_controller.h"
#include "kimpanelagent.h"

MainController::MainController()
    : mModel(0), mAgent(0)
{

}

bool MainController::init()
{
    if ((mModel = new (std::nothrow)MainModel) == NULL)
        return false;

    if ((mAgent = new (std::nothrow)PanelAgent(this)) == NULL)
        return false;

    QObject::connect(mAgent,
        SIGNAL(updatePreeditText(QString, QList<TextAttribute>)),
        this, SLOT(updatePreeditText(QString, QList<TextAttribute>)));

    QObject::connect(mAgent,
        SIGNAL(UpdateLookupTable(QStringList, QStringList, QStringList,
                bool, bool)),
        this, SLOT(UpdateLookupTable(QStringList, QStringList, QStringList,
                bool, bool)));

    mAgent->created();

	return true;
}

MainController::~MainController()
{
    if (mModel) {
        delete mModel;
    }
    
    if (mAgent) {
        delete mAgent;
    }
}

void MainController::updatePreeditText(const QString inputString,
    QList<TextAttribute> attributes)
{
    mModel->setInputString(inputString);
}

void MainController::UpdateLookupTable(const QStringList &labels,
    const QStringList &candis, const QStringList &attrlists,
    bool has_prev, bool has_next)
{

}

