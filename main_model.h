
#ifndef __MAIN_MODEL_H__
#define __MAIN_MODEL_H__

#include <QDeclarativeView>
#include <QObject>

class MainModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString inputString READ inputString WRITE setInputString 
        NOTIFY inputStringChanged)

public:
    MainModel();
    virtual ~MainModel();

public:
    void setInputString(const QString inputString);
    QString inputString() const;
signals:
    void inputStringChanged();
private:
    QString mInputString;

};

#endif // __MAIN_MODEL_H__
