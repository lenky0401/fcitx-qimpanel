
#ifndef __MAIN_APPLICATION_H__
#define __MAIN_APPLICATION_H__

#include <QApplication>

class MainApplication : public QApplication
{
    Q_OBJECT
    
public:
    MainApplication(int &argc, char **argv);
    virtual ~MainApplication();
    bool init();


};

#endif // __MAIN_APPLICATION_H__
