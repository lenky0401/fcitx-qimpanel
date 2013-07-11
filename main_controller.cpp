#include <QDebug>
#include <stdio.h>
#include "main_model.h"
#include "candidate_word.h"
#include "main_controller.h"
#include "kimpanelagent.h"

MainController::MainController()
    : mModel(0), mAgent(0)
{

}

bool MainController::init()
{
    qmlRegisterType<CandidateWord>();

    if ((mModel = new (std::nothrow)MainModel) == NULL)
        return false;

    if ((mAgent = new (std::nothrow)PanelAgent(this)) == NULL)
        return false;

    QObject::connect(mAgent,
        SIGNAL(updatePreeditText(QString, QList<TextAttribute>)),
        this, SLOT(updatePreeditText(QString, QList<TextAttribute>)));

    QObject::connect(mAgent,
        SIGNAL(updateLookupTable(KimpanelLookupTable)),
        this, SLOT(updateLookupTable(KimpanelLookupTable)));

    QObject::connect(mAgent,
        SIGNAL(updateLookupTableFull(KimpanelLookupTable, int, int)),
        this, SLOT(updateLookupTableFull(KimpanelLookupTable, int, int)));

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

void MainController::updateLookupTable(const KimpanelLookupTable &lookup_table)
{
//    QList<KimpanelLookupTable::Entry>::iterator iter;
//    QList<KimpanelLookupTable::Entry> entries = lookup_table.entries;
//
//    for (iter = entries.begin(); iter != entries.end(); ++ iter) {
//        qDebug("label value: %s", qPrintable(iter->label));
//        qDebug("text value: %s", qPrintable(iter->text));
//    }

    mModel->setCandidateWords(lookup_table);
}

void MainController::updateLookupTableFull(const KimpanelLookupTable &lookup_table,
    int cursor, int layout)
{
    updateLookupTable(lookup_table);
//    printf("cursor:%d, layout:%d\n", cursor, layout);
}

