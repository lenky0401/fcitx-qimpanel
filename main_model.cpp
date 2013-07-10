
#include "main_model.h"

MainModel::MainModel()
{

}

MainModel::~MainModel()
{

}


void MainModel::setInputString(const QString inputString) {
	mInputString = inputString;
	emit inputStringChanged();
}

QString MainModel::inputString() const {
	return mInputString;
}
