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
    QLabel *f_LblDAOErr;

    //admin menu wid
    QWidget *f_WidMenu;
    QGridLayout *f_LytMenu;
    QPushButton *f_BtnManageSubject;
    QPushButton *f_BtnManageStudent;
    QPushButton *f_BtnManageGroup;
    QPushButton *f_BtnManageLesson;
    QPushButton *f_BtnAttCheck;
    QPushButton *f_BtnLogout;

    //add student wid
    QTableView *f_AllStudents;
    QWidget *f_WidAddStudent;
    QGridLayout *f_LytAddStudent;
    QLineEdit *f_LeStName;
    QListView *f_LvStGroup;
    QLineEdit *f_LeStudNum;
    QLineEdit *f_eMail;
    QPushButton *f_BtnAcceptStudent;
    QPushButton *f_BtnRemoveStudent;

    //add group wid
    QListView *f_AllGroups;
    QWidget *f_WidAddGroup;
    QGridLayout *f_LytAddGroup;
    QLineEdit *f_LeGroup;
    QPushButton *f_BtnAcceptGroup;
    QPushButton *f_BtnRemoveGroup;

    //add subject wid
    QListView *f_AllSubjects;
    QWidget *f_WidAddSubject;
    QGridLayout *f_LytAddSubject;
    QLineEdit *f_LeSubject;
    QPushButton *f_BtnAcceptSubject;
    QPushButton *f_BtnRemoveSubject;

    //add lesson wid
    QTableView *f_AllLessons;
    QWidget *f_WidAddLesson;
    QGridLayout *f_LytAddLesson;
    QListView* f_LvAddLessonSubj;
    QListView *f_LvAddLessonUsers;
    QListView *f_LvAddLessonGroups;
    QSpinBox *f_LessonsAmount;
    QComboBox *f_AddLessonDay;
    QComboBox *f_AddLessonTime;
    QPushButton *f_BtnAcceptLesson;
    QPushButton *f_BtnRemoveLesson;

    //attendance check wid
    QWidget *f_WidAttCheck;
    QGridLayout *f_LytAttCheck;
    QTableView *f_TvAtt;
    QListView *f_Groups;
    QListView *f_Subjects;
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
    void onRemoveSt();
    void onRemoveGr();
    void onRemoveLess();
    void onRemoveSubj();

signals:

    void logout();



};

#endif // ADMINMENU_H
