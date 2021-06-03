#ifndef ADMINMENU_H
#define ADMINMENU_H

#include "generaldao.h"
#include "QtWidgets"





class AdminMenu : public QWidget
{
    Q_OBJECT
public:
    AdminMenu(QWidget *parent = nullptr);

    virtual ~AdminMenu() {};


private:

    //main lyt
    QGridLayout *f_LytMain;

    QPushButton* f_BtnBackToMenu;
    QLabel *f_LblErr;

    //admin menu wid
    QWidget *f_WidMenu;
    QGridLayout *f_LytMenu;
    QPushButton *f_BtnAddSubject;
    QPushButton *f_BtnAddStudent;
    QPushButton *f_BtnAddGroup;
    QPushButton *f_BtnAddLesson;
    QPushButton *f_BtnAttCheck;
    QPushButton *f_BtnLogout;

    //add student wid
    QWidget *f_WidAddStudent;
    QGridLayout *f_LytAddStudent;
    QLineEdit *f_LeStName;
    QListView *f_LvStGroup;
    QLineEdit *f_LeStudNum;
    QLineEdit *f_eMail;
    QPushButton *f_BtnAcceptStudent;

    //add group wid
    QWidget *f_WidAddGroup;
    QGridLayout *f_LytAddGroup;
    QLineEdit *f_LeGroup;
    QPushButton *f_BtnAcceptGroup;

    //add subject wid
    QWidget *f_WidAddSubject;
    QGridLayout *f_LytAddSubject;
    QLineEdit *f_LeSubject;
    QPushButton *f_BtnAcceptSubject;

    //add lesson wid
    QWidget *f_WidAddLesson;
    QGridLayout *f_LytAddLesson;
    QListView *f_LvAddLessonUsers;
    QListView *f_LvAddLessonGroups;
    QSpinBox *f_LessonsAmount;
    QComboBox *f_AddLessonDay;
    QComboBox *f_AddLessonTime;
    QPushButton *f_BtnAcceptLesson;

    //attendance check wid
    QWidget *f_WidAttCheck;
    QGridLayout *f_LytAttCheck;
    QTableView *f_TvAtt;
    QListView *f_Groups;
    QComboBox *f_Days;
    QComboBox *f_Times;
    QPushButton *f_BtnRefresh;


    void styling();


    friend class MainWindow;


public slots:

    void resetWidget();

    void backToMenu();
    void refreshAttData();

    void onNewSubjectClicked();
    void onNewGroupClicked();
    void onNewLessonClicked();
    void onNewStudentClicked();
    void onAttCheckClicked();
    void onLogoutClicked();

    void onAcceptStInfoClicked();
    void onAcceptGrInfoClicked();
    void onAcceptLessInfoClicked();
    void onAcceptSubjInfoClicked();

signals:

    void logout();



};

#endif // ADMINMENU_H
