#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "generaldao.h"
#include <QtWidgets>
#include <QQuickWidget>
#include <QMainWindow>
#include "adminmenu.h"
#include "QZXing.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:

    //variables
    QString f_currentLogin;
    QString f_currentGroup;
    QString f_currentTime;
    QString f_StrDataRead;
    int f_currentLessonId;


    //main wid and lyt
    QWidget* f_CentralWidget;
    QGridLayout *f_LytMain;

    //login wid
    QWidget *f_WidLogin;
    QGridLayout *f_LytLogin;
    QLabel *f_LblWrong;
    QPushButton *f_BtnLogin;
    QLineEdit *f_LeLogin;
    QLineEdit *f_LePass;

    //group select wid
    QWidget *f_WidGroups;
    QGridLayout *f_LytGroups;
    QListView *f_LvGroups;
    QPushButton *f_BtnLogout;

    //time select wid
    QWidget *f_WidTime;
    QGridLayout *f_LytTime;
    QListView* f_LvTimes;
    QPushButton* f_BtnBackToGroups;

    //cam wid
    QWidget *f_WidCam;
    QGridLayout *f_LytCam;
    QPushButton *f_BtnBackToSelections;

    //verification wid
    QWidget *f_WidVer;
    QGridLayout *f_LytVer;
    QPushButton *f_BtnVerify;
    QPushButton *f_BtnDecline;
    QLabel *f_LblDataRead;



    //admin menu instance
    AdminMenu *f_AdmMenuIstc;




private:

    QQuickWidget* f_cam;

private:

    void styling();

protected:

    void dataCleanUp();
    void dataRefresh();

public slots:

    void onLoginBtnClicked();
    void onLoginAcceptedUser();
    void onLoginAcceptedAdmin();
    void onLogout();
    void onGroupSelected(const QModelIndex&);
    void onBackToGroups();
    void onTimeSelected(const QModelIndex&);
    void onBackToSelections();
    void onVerified();
    void onDeclined();
    void onAdminLogout();
    void onQueryError(const QString&);

    void onTagGot(QString);

signals:

    void sigLoginAcceptedAdmin();
    void sigLoginAcceptedUser();

};
#endif // MAINWINDOW_H
