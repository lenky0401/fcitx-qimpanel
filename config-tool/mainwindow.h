#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "config.h"
#ifdef IS_QT_5
    #include <QQuickWidget>
    #include <QQmlContext>
#endif
#ifdef IS_QT_4
    #include <QDeclarativeView>
    #include <QtDeclarative/QDeclarativeContext>
#endif
#include <QDialog>
#include <QSettings>
#include <QString>
#include <QVector>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QDBusInterface>
#include "skin/skinbase.h"
#include "skin/skinfcitx.h"
#include "main_model.h"
#include "candidate_word.h"
#include "editingskindialog.h"

namespace Ui {
class MainWindow;
}

struct SkinTypeEntry {
    QString name;
    QString absolutePath;
};

class MainWindow : public QDialog
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    QSettings *mSettings;
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QString skinPath;
    QList<SkinTypeEntry> allSkinType;
    SkinFcitx *mSkinFcitx;
    MainModel *mMainModer;
    #ifdef IS_QT_5
        QQuickWidget *qmlView;
    #endif
    #ifdef IS_QT_4
        QDeclarativeView *qmlView;
    #endif

    QHBoxLayout *mLayout;
    QString curtSkinType;
    QString localPath;
    QStringList systemSkin_list;
    QStringList localSkin_list;
    int idx;
    QDBusInterface * myInterface;
    bool listWidgetChangeClearFlag;

private:
    void searchAndSetSystemSkin( );
    void searchAndSetLocalSkin( );
    void loadMainConf();
    void saveMainConf();
    void loadSkinPreview();
    void changeMainWindowSize();
    void setSkinBase();
    void showListWidgetAllSkin();
    void setListWidgetAllSkin();
    void refreshListWidgetAllSkin();
    void linkQtDbusServer();

private slots:
    void sltOnPushButtonApply();
    void sltOnPushButtonCancel();
    void sltOnAllSkinItemDoubleClicked(QListWidgetItem *item);
    void sltOnCurrentChanged(QWidget *tab);  
    void on_radioButtonHorizontal_toggled(bool checked);
    void setListWidgetAllSkinIndex(int index);

    void on_listWidgetAllSkin_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

signals:
    void sigRestartQimpanel();
};

#endif // MAINWINDOW_H
