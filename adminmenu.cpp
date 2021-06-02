#include "adminmenu.h"

AdminMenu::AdminMenu(QWidget *parent)
    : QWidget(parent)
{
    f_LytMain = new QGridLayout(this);

    f_BtnBackToMenu = new QPushButton("Back to menu", this);
    connect(f_BtnBackToMenu, SIGNAL(clicked()), this, SLOT(backToMenu()));
    f_LytMain->addWidget(f_BtnBackToMenu,0,0,Qt::AlignmentFlag::AlignLeft);
    f_BtnBackToMenu->hide();

    f_LblErr = new QLabel("All the fields must be\nfilled or selected");
    f_LblErr->setStyleSheet("QLabel { color : red; }");

    f_LytMain->addWidget(f_LblErr,3,0,Qt::AlignmentFlag::AlignCenter);
    f_LblErr->hide();

    //menu lyt setup
    f_WidMenu = new QWidget(this);
    f_LytMenu = new QGridLayout(this);
    QLabel *LblMenu = new QLabel("Admin Menu", this);
    f_BtnAddSubject = new QPushButton("Add new subject", this);
    f_BtnAddGroup = new QPushButton("Add new group", this);
    f_BtnAddLesson = new QPushButton("Add new lesson", this);
    f_BtnAddStudent = new QPushButton("Add new student", this);
    f_BtnAttCheck = new QPushButton("Attendance check", this);
    f_BtnLogout = new QPushButton("Logout", this);

    f_LytMenu->addWidget(LblMenu,0,0,Qt::AlignmentFlag::AlignCenter);
    f_LytMenu->addWidget(f_BtnAddSubject,2,0,Qt::AlignmentFlag::AlignCenter);
    f_LytMenu->addWidget(f_BtnAddGroup,3,0,Qt::AlignmentFlag::AlignCenter);
    f_LytMenu->addWidget(f_BtnAddLesson,4,0,Qt::AlignmentFlag::AlignCenter);
    f_LytMenu->addWidget(f_BtnAddStudent,5,0,Qt::AlignmentFlag::AlignCenter);
    f_LytMenu->addWidget(f_BtnAttCheck,6,0,Qt::AlignmentFlag::AlignCenter);
    f_LytMenu->addWidget(f_BtnLogout,7,0,Qt::AlignmentFlag::AlignCenter);

    f_WidMenu->setLayout(f_LytMenu);

    f_LytMain->addWidget(f_WidMenu,1,0,Qt::AlignmentFlag::AlignCenter);

    connect(f_BtnAddSubject, SIGNAL(clicked()), this, SLOT(onNewSubjectClicked()));
    connect(f_BtnAddGroup, SIGNAL(clicked()), this, SLOT(onNewGroupClicked()));
    connect(f_BtnAddLesson, SIGNAL(clicked()), this, SLOT(onNewLessonClicked()));
    connect(f_BtnAddStudent, SIGNAL(clicked()), this, SLOT(onNewStudentClicked()));
    connect(f_BtnAttCheck, SIGNAL(clicked()), this, SLOT(onAttCheckClicked()));
    connect(f_BtnLogout, SIGNAL(clicked()), this, SLOT(onLogoutClicked()));
    //

    //add student wid
    f_WidAddStudent = new QWidget(this);
    f_LytAddStudent = new QGridLayout(this);
    QLabel *LblAddStudent = new QLabel("Add new student");
    f_LeStName = new QLineEdit(this);
    f_LvStGroup = new QListView(this);
    f_LeStudNum = new QLineEdit(this);
    f_eMail = new QLineEdit(this);
    f_BtnAcceptStudent = new QPushButton("Accept info",this);

    QLabel *LblStName = new QLabel("Name:");
    QLabel *LblStGroup = new QLabel("Group:");
    QLabel *LblStStudNum = new QLabel("Auth. number:");
    QLabel *LblStMail = new QLabel("Email:");

    f_LytAddStudent->addWidget(LblAddStudent,0,0,1,2,Qt::AlignmentFlag::AlignCenter);

    f_LytAddStudent->addWidget(LblStName,2,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddStudent->addWidget(f_LeStName,2,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAddStudent->addWidget(LblStGroup,3,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddStudent->addWidget(f_LvStGroup,3,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAddStudent->addWidget(LblStStudNum,4,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddStudent->addWidget(f_LeStudNum,4,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAddStudent->addWidget(LblStMail,5,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddStudent->addWidget(f_eMail,5,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAddStudent->addWidget(f_BtnAcceptStudent,6,0,1,2,Qt::AlignmentFlag::AlignCenter);

    f_LytMain->addWidget(f_WidAddStudent,1,0,Qt::AlignmentFlag::AlignCenter);

    f_WidAddStudent->setLayout(f_LytAddStudent);
    f_WidAddStudent->hide();

    connect(f_BtnAcceptStudent, SIGNAL(clicked()), this, SLOT(onAcceptStInfoClicked()));
    //

    //add group wid
    f_WidAddGroup = new QWidget(this);
    f_LytAddGroup = new QGridLayout(this);
    QLabel *LblAddGroup = new QLabel("Add new group");
    f_BtnAcceptGroup = new QPushButton("Accept info",this);
    QLabel *LblLeGroup = new QLabel("Group index:");
    f_LeGroup = new QLineEdit(this);

    f_LytAddGroup->addWidget(LblAddGroup,0,0,1,2,Qt::AlignmentFlag::AlignCenter);
    f_LytAddGroup->addWidget(LblLeGroup,2,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddGroup->addWidget(f_LeGroup,2,1,Qt::AlignmentFlag::AlignCenter);
    f_LytAddGroup->addWidget(f_BtnAcceptGroup,3,0,1,2,Qt::AlignmentFlag::AlignCenter);

    f_WidAddGroup->setLayout(f_LytAddGroup);
    f_LytMain->addWidget(f_WidAddGroup,1,0,Qt::AlignmentFlag::AlignCenter);

    f_WidAddGroup->hide();

    connect(f_BtnAcceptGroup, SIGNAL(clicked()), this, SLOT(onAcceptGrInfoClicked()));
    //

    //add subject wid
    f_WidAddSubject = new QWidget(this);
    f_LytAddSubject = new QGridLayout(this);
    QLabel *LblAddSubj = new QLabel("Add new subject");
    f_BtnAcceptSubject = new QPushButton("Accept info",this);
    QLabel *LblLeSubject = new QLabel("Subject name:");
    f_LeSubject = new QLineEdit(this);

    f_LytAddSubject->addWidget(LblAddSubj,0,0,1,2,Qt::AlignmentFlag::AlignCenter);
    f_LytAddSubject->addWidget(LblLeSubject,2,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddSubject->addWidget(f_LeSubject,2,1,Qt::AlignmentFlag::AlignCenter);
    f_LytAddSubject->addWidget(f_BtnAcceptSubject,3,0,1,2,Qt::AlignmentFlag::AlignCenter);

    f_WidAddSubject->setLayout(f_LytAddSubject);
    f_LytMain->addWidget(f_WidAddSubject,1,0,Qt::AlignmentFlag::AlignCenter);

    f_WidAddSubject->hide();

    connect(f_BtnAcceptSubject, SIGNAL(clicked()), this, SLOT(onAcceptSubjInfoClicked()));
    //

    //lesson wid
    f_WidAddLesson = new QWidget(this);
    f_LytAddLesson = new QGridLayout(this);
    QLabel *LblAddLess = new QLabel("Add new lesson");
    f_BtnAcceptLesson = new QPushButton("Accept info");
    QLabel *LblAddLessonUsers = new QLabel("Available\nteacher\nlogins");
    f_LvAddLessonUsers = new QListView(this);
    QLabel *LblAddLessonGroups = new QLabel("Available\ngroup\nindexes");
    f_LvAddLessonGroups = new QListView(this);
    QLabel *LblLessAmout = new QLabel("Amount of lessons\nduring semestre:");
    f_LessonsAmount = new QSpinBox(this);
    f_LessonsAmount->setMinimum(1);
    f_LessonsAmount->setMaximum(100);
    QLabel *LblLessDay = new QLabel("Day:");
    f_AddLessonDay = new QComboBox(this);

    f_AddLessonDay->addItem("Mon");
    f_AddLessonDay->addItem("Tue");
    f_AddLessonDay->addItem("Wen");
    f_AddLessonDay->addItem("Thu");
    f_AddLessonDay->addItem("Fri");
    f_AddLessonDay->addItem("Sat");

    QLabel *LblLessTime = new QLabel("Time:");
    f_AddLessonTime = new QComboBox(this);

    f_AddLessonTime->addItem("8:30");
    f_AddLessonTime->addItem("10:15");
    f_AddLessonTime->addItem("12:00");
    f_AddLessonTime->addItem("13:50");
    f_AddLessonTime->addItem("15:40");
    f_AddLessonTime->addItem("17:25");
    f_AddLessonTime->addItem("19:10");

    f_BtnAcceptLesson = new QPushButton("Accept info");

    f_LytAddLesson->addWidget(LblAddLess,0,0,1,2,Qt::AlignmentFlag::AlignCenter);
    f_LytAddLesson->addWidget(LblAddLessonUsers,2,0,Qt::AlignmentFlag::AlignCenter);
    f_LytAddLesson->addWidget(LblAddLessonGroups,2,1,Qt::AlignmentFlag::AlignCenter);
    f_LytAddLesson->addWidget(f_LvAddLessonUsers,3,0,Qt::AlignmentFlag::AlignCenter);
    f_LytAddLesson->addWidget(f_LvAddLessonGroups,3,1,Qt::AlignmentFlag::AlignCenter);
    f_LytAddLesson->addWidget(LblLessAmout,4,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddLesson->addWidget(f_LessonsAmount,4,1,Qt::AlignmentFlag::AlignCenter);
    f_LytAddLesson->addWidget(LblLessDay,5,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddLesson->addWidget(f_AddLessonDay,5,1,Qt::AlignmentFlag::AlignCenter);
    f_LytAddLesson->addWidget(LblLessTime,6,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddLesson->addWidget(f_AddLessonTime,6,1,Qt::AlignmentFlag::AlignCenter);
    f_LytAddLesson->addWidget(f_BtnAcceptLesson,7,0,1,2,Qt::AlignmentFlag::AlignCenter);

    f_WidAddLesson->setLayout(f_LytAddLesson);
    f_LytMain->addWidget(f_WidAddLesson,1,0,Qt::AlignmentFlag::AlignCenter);

    f_WidAddLesson->hide();

    connect(f_BtnAcceptLesson, SIGNAL(clicked()), this, SLOT(onAcceptLessInfoClicked()));
    //

    //att check wid
    f_WidAttCheck = new QWidget(this);
    f_LytAttCheck = new QGridLayout(this);
    f_BtnRefresh = new QPushButton("Refresh",this);
    QLabel *LblAttCheck = new QLabel("Attandance check");
    f_TvAtt = new QTableView(this);
    QLabel *LblAttGroup = new QLabel("Available\ngroup\nindexes");
    f_Groups = new QListView(this);

    QLabel *LblAttDay = new QLabel("Day:");
    f_Days = new QComboBox(this);

    f_Days->addItem("Mon");
    f_Days->addItem("Tue");
    f_Days->addItem("Wen");
    f_Days->addItem("Thu");
    f_Days->addItem("Fri");
    f_Days->addItem("Sat");

    QLabel *LblAttTimes = new QLabel("Time");
    f_Times = new QComboBox(this);

    f_Times->addItem("8:30");
    f_Times->addItem("10:15");
    f_Times->addItem("12:00");
    f_Times->addItem("13:50");
    f_Times->addItem("15:40");
    f_Times->addItem("17:25");
    f_Times->addItem("19:10");

    f_LytAttCheck->addWidget(LblAttCheck,0,0,1,2,Qt::AlignmentFlag::AlignCenter);
    f_LytAttCheck->addWidget(f_TvAtt,2,0,1,2,Qt::AlignmentFlag::AlignCenter);
    f_LytAttCheck->addWidget(LblAttGroup,3,0,Qt::AlignmentFlag::AlignRight);
    f_LytAttCheck->addWidget(f_Groups,3,1,Qt::AlignmentFlag::AlignCenter);
    f_LytAttCheck->addWidget(LblAttDay,4,0,Qt::AlignmentFlag::AlignRight);
    f_LytAttCheck->addWidget(f_Days,4,1,Qt::AlignmentFlag::AlignCenter);
    f_LytAttCheck->addWidget(LblAttTimes,5,0,Qt::AlignmentFlag::AlignRight);
    f_LytAttCheck->addWidget(f_Times,5,1,Qt::AlignmentFlag::AlignCenter);
    f_LytAttCheck->addWidget(f_BtnRefresh,6,1,1,2,Qt::AlignmentFlag::AlignCenter);

    f_WidAttCheck->setLayout(f_LytAttCheck);
    f_LytMain->addWidget(f_WidAttCheck,1,0,Qt::AlignmentFlag::AlignCenter);

    f_WidAttCheck->hide();

    //


    connect(f_BtnRefresh, SIGNAL(clicked()), this, SLOT(refreshAttData()));

    setLayout(f_LytMain);
}

void AdminMenu::styling()
{
    setStyleSheet(""
"QWidget {"
"background-color: rgb(32,32,32)"
"}"
""
"QLabel {"
"color: rgb(150,150,150);"
"font: bold 11px;"
"}"
""
"QLineEdit { "
"background-color: rgb(64,64,64);"
"border: 2px solid rgb(56,56,56);"
"border-radius: 4px;"
"selection-background-color: rgb(110,110,150); "
"color: rgb(150,150,150);"
"}"
""
"QPushButton {"
"background-color: rgb(25,25,25);"
"border-width: 2px solid;"
"border-radius: 4px;"
"font: bold 12px;"
"color: rgb(150,150,150);"
"padding: 6px;"
"}"
""
"QPushButton:pressed {"
"background-color: rgb(64, 64, 64);"
"}"
""
"QListView {"
"background-color: rgb(46,46,46);"
"alternate-background-color: rgb(32,32,32);"
"border: 2px solid rgb(56,56,56);"
"color: rgb(150,150,150);"
"}"
""
"QListView::item:selected {"
"border: 2px solid rgb(110,110,150);"
"}"
""
"QTableView {"
"background-color: rgb(46,46,46);"
"border: 2px solid rgb(56,56,56);"
"color: rgb(150,150,150);"
"}"
""
"QComboBox {"
"background-color: rgb(46,46,46);"
"border: 2px solid rgb(56,56,56);"
"border-radius: 3px"
"color: rgb(150,150,150);"
"font: bold 12px;"
"}"
""
);
}

void AdminMenu::resetWidget()
{
    f_LeGroup->clear();
    f_LeStName->clear();
    f_LeStudNum->clear();
    f_LeSubject->clear();
    f_eMail->clear();
}

void AdminMenu::backToMenu()
{
    f_BtnBackToMenu->hide();
    f_LblErr->hide();
    f_WidAddGroup->hide();
    f_WidAddLesson->hide();
    f_WidAddStudent->hide();
    f_WidAddSubject->hide();
    f_WidAttCheck->hide();
    f_WidMenu->show();

    resetWidget();
}

void AdminMenu::refreshListsData()
{
    QSqlQueryModel* model = GeneralDAO::getInstance().getAllGroupIds();
    f_LvAddLessonGroups->setModel(model);
    f_LvAddLessonUsers->setModel(GeneralDAO::getInstance().getAllTeacherLogins());
    f_LvStGroup->setModel(model);
    //DAO access filling in the data fields e.g. ListViews for groups and logins
}

void AdminMenu::refreshAttData()
{
    //f_TvAtt->setModel(GeneralDAO::getInstance().getVisitingsByGroupTime(f_Groups->model->data(f_Groups->selectionModel()->selectedIndexes().at(0)).toString(),));
    //DAO access filling in the data fields e.g. Filling the TableView for attendance
}

void AdminMenu::onNewSubjectClicked()
{
    f_WidMenu->hide();
    f_WidAddSubject->show();
    f_BtnBackToMenu->show();
}

void AdminMenu::onNewGroupClicked()
{
    f_WidMenu->hide();
    f_WidAddGroup->show();
    f_BtnBackToMenu->show();
}

void AdminMenu::onNewLessonClicked()
{
    f_WidMenu->hide();
    f_WidAddLesson->show();
    f_BtnBackToMenu->show();
}

void AdminMenu::onNewStudentClicked()
{
    f_WidMenu->hide();
    f_WidAddStudent->show();
    f_BtnBackToMenu->show();
}

void AdminMenu::onAttCheckClicked()
{
    f_WidMenu->hide();
    f_WidAttCheck->show();
    f_BtnBackToMenu->show();
}

void AdminMenu::onLogoutClicked()
{
    emit (logout());
}

void AdminMenu::onAcceptStInfoClicked()
{
    f_LblErr->hide();

    if(f_LeStName->text().isEmpty()
            ||f_LeStudNum->text().isEmpty()
            ||f_eMail->text().isEmpty()
            )
    {
        f_LblErr->show();
        return;
    }
    else
    {
        if(f_LvStGroup->selectionModel() == nullptr)
        {
            f_LblErr->show();
            return;
        }
        else
        {
            if(f_LvStGroup->selectionModel()->selectedRows().size() == 0)
            {
                f_LblErr->show();
                return;
            }
        }

    //DAO access add Student

        backToMenu();
    }
}

void AdminMenu::onAcceptGrInfoClicked()
{
    f_LblErr->hide();

    if(f_LeGroup->text().isEmpty())
    {
        f_LblErr->show();
        return;
    }
    else
    {
    //DAO access add Group
        backToMenu();
    }
}

void AdminMenu::onAcceptLessInfoClicked()
{
    f_LblErr->hide();

    if(f_LessonsAmount->value() < 1
            || f_AddLessonDay->currentText() == ""
            || f_AddLessonTime->currentText() == "")
    {
        f_LblErr->show();
        return;
    }
    else
    {
        if(f_LvAddLessonUsers->selectionModel() == nullptr || f_LvAddLessonGroups->selectionModel() == nullptr)
        {
            f_LblErr->show();
            return;
        }
        else
        {
            if(f_LvAddLessonUsers->selectionModel()->selectedRows().size() == 0 || f_LvAddLessonGroups->selectionModel()->selectedRows().size() == 0)
            {
                f_LblErr->show();
                return;
            }
        }

        //DAO access add Lesson

        backToMenu();
    }
}

void AdminMenu::onAcceptSubjInfoClicked()
{
    f_LblErr->hide();

    if(f_LeSubject->text().isEmpty())
    {
        f_LblErr->show();
        return;
    }
    else
    {
    //DAO access add Subject
        backToMenu();
    }
}

