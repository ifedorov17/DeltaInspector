#include "adminmenu.h"
#include "QrEncoder.h"
#include "src/SmtpMime"


AdminMenu::AdminMenu(QWidget *parent)
    : QWidget(parent)
{
    f_LytMain = new QGridLayout(this);

    f_BtnBackToMenu = new QPushButton("Меню", this);
    connect(f_BtnBackToMenu, SIGNAL(clicked()), this, SLOT(backToMenu()));
    f_LytMain->addWidget(f_BtnBackToMenu,0,0,Qt::AlignmentFlag::AlignLeft);
    f_BtnBackToMenu->hide();

    f_LblErr = new QLabel("Все поля должны быть\nзаполнены или выбраны");
    f_LblErr->setStyleSheet("QLabel { color : rgb(254,192,0); }");

    f_LblDAOErr = new QLabel();
    f_LblDAOErr->setStyleSheet("QLabel { color : rgb(255,60,60); }");

    f_LytMain->addWidget(f_LblErr,7,0,Qt::AlignmentFlag::AlignCenter);
    f_LytMain->addWidget(f_LblDAOErr,8,0,Qt::AlignmentFlag::AlignCenter);

    f_LblErr->hide();
    f_LblDAOErr->hide();

    //menu lyt setup
    f_WidMenu = new QWidget(this);
    f_LytMenu = new QGridLayout();
    QLabel *LblMenu = new QLabel("Меню администратора", this);
    f_BtnManageSubject = new QPushButton("Управление предметами", this);
    f_BtnManageGroup = new QPushButton("Управление группами", this);
    f_BtnManageLesson = new QPushButton("Управление занятиями", this);
    f_BtnManageStudent = new QPushButton("Управление студентами", this);
    f_BtnAttCheck = new QPushButton("Проверка посещаемости", this);
    f_BtnLogout = new QPushButton("Выход", this);

    f_LytMenu->addWidget(LblMenu,0,0,Qt::AlignmentFlag::AlignCenter);
    f_LytMenu->addWidget(f_BtnManageSubject,2,0,Qt::AlignmentFlag::AlignCenter);
    f_LytMenu->addWidget(f_BtnManageGroup,3,0,Qt::AlignmentFlag::AlignCenter);
    f_LytMenu->addWidget(f_BtnManageLesson,4,0,Qt::AlignmentFlag::AlignCenter);
    f_LytMenu->addWidget(f_BtnManageStudent,5,0,Qt::AlignmentFlag::AlignCenter);
    f_LytMenu->addWidget(f_BtnAttCheck,6,0,Qt::AlignmentFlag::AlignCenter);
    f_LytMenu->addWidget(f_BtnLogout,7,0,Qt::AlignmentFlag::AlignCenter);

    f_WidMenu->setLayout(f_LytMenu);

    f_LytMain->addWidget(f_WidMenu,1,0,Qt::AlignmentFlag::AlignCenter);

    connect(f_BtnManageSubject, SIGNAL(clicked()), this, SLOT(onNewSubjectClicked()));
    connect(f_BtnManageGroup, SIGNAL(clicked()), this, SLOT(onNewGroupClicked()));
    connect(f_BtnManageLesson, SIGNAL(clicked()), this, SLOT(onNewLessonClicked()));
    connect(f_BtnManageStudent, SIGNAL(clicked()), this, SLOT(onNewStudentClicked()));
    connect(f_BtnAttCheck, SIGNAL(clicked()), this, SLOT(onAttCheckClicked()));
    connect(f_BtnLogout, SIGNAL(clicked()), this, SLOT(onLogoutClicked()));
    //

    //add student wid

    f_WidAddStudent = new QWidget(this);
    f_LytAddStudent = new QGridLayout();
    QLabel *LblAddStudent = new QLabel("Управление студентами");

    f_AllStudents = new QTableView();
    f_AllStudents->setSelectionBehavior(QAbstractItemView::SelectRows);
    f_AllStudents->setSelectionMode(QAbstractItemView::SingleSelection);

    QLabel *LblStEd = new QLabel("Добавление студента");

    f_LeStName = new QLineEdit(this);
    f_LvStGroup = new QListView();
    f_LvStGroup->setSelectionMode(QAbstractItemView::SingleSelection);

    f_LeStudNum = new QLineEdit(this);

    f_eMail = new QLineEdit(this);

    f_BtnAcceptStudent = new QPushButton("+", this);
    f_BtnRemoveStudent = new QPushButton("-", this);
    f_BtnAcceptStudent->setMinimumSize(30,30);
    f_BtnRemoveStudent->setMinimumSize(30,30);

    QLabel *LblStName = new QLabel("Имя:", this);
    QLabel *LblStGroup = new QLabel("Группа:", this);
    QLabel *LblStStudNum = new QLabel("Номер СБ:", this);
    QLabel *LblStMail = new QLabel("Эл. почта:", this);

    f_LytAddStudent->addWidget(LblAddStudent,0,0,Qt::AlignmentFlag::AlignCenter);
    f_LytAddStudent->addWidget(f_BtnRemoveStudent,0,1,Qt::AlignmentFlag::AlignRight);

    f_LytAddStudent->addWidget(f_AllStudents,1,0,1,2,Qt::AlignmentFlag::AlignCenter);

    f_LytAddStudent->addWidget(LblStEd,2,0,1,2,Qt::AlignmentFlag::AlignCenter);

    f_LytAddStudent->addWidget(LblStName,3,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddStudent->addWidget(f_LeStName,3,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAddStudent->addWidget(LblStGroup,4,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddStudent->addWidget(f_LvStGroup,4,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAddStudent->addWidget(LblStStudNum,5,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddStudent->addWidget(f_LeStudNum,5,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAddStudent->addWidget(LblStMail,6,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddStudent->addWidget(f_eMail,6,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAddStudent->addWidget(f_BtnAcceptStudent,7,0,1,2,Qt::AlignmentFlag::AlignCenter);

    f_WidAddStudent->setLayout(f_LytAddStudent);
    f_WidAddStudent->hide();

    f_LytMain->addWidget(f_WidAddStudent,2,0,Qt::AlignmentFlag::AlignCenter);

    connect(f_BtnAcceptStudent, SIGNAL(clicked()), this, SLOT(onAcceptStInfoClicked()));
    connect(f_BtnRemoveStudent, SIGNAL(clicked()), this, SLOT(onRemoveSt()));

   //

    //add group wid
    f_WidAddGroup = new QWidget(this);
    f_LytAddGroup = new QGridLayout();

    QLabel *LblAddGroup = new QLabel("Управление группами", this);

    f_AllGroups = new QListView();
    f_AllGroups->setSelectionMode(QAbstractItemView::SingleSelection);

    QLabel *LblGrEd = new QLabel("Добавление группы");

    f_BtnAcceptGroup = new QPushButton("+", this);
    f_BtnRemoveGroup = new QPushButton("-", this);

    f_BtnAcceptGroup->setMinimumSize(30,30);
    f_BtnRemoveGroup->setMinimumSize(30,30);

    QLabel *LblLeGroup = new QLabel("Номер группы:", this);
    f_LeGroup = new QLineEdit(this);

    f_LytAddGroup->addWidget(LblAddGroup,0,0,Qt::AlignmentFlag::AlignCenter);
    f_LytAddGroup->addWidget(f_BtnRemoveGroup,0,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAddGroup->addWidget(f_AllGroups,1,0,1,2,Qt::AlignmentFlag::AlignCenter);

    f_LytAddGroup->addWidget(LblGrEd,2,0,1,2,Qt::AlignmentFlag::AlignCenter);

    f_LytAddGroup->addWidget(LblLeGroup,3,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddGroup->addWidget(f_LeGroup,3,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAddGroup->addWidget(f_BtnAcceptGroup,4,0,1,2,Qt::AlignmentFlag::AlignCenter);

    f_WidAddGroup->setLayout(f_LytAddGroup);
    f_LytMain->addWidget(f_WidAddGroup,3,0,Qt::AlignmentFlag::AlignCenter);

    f_WidAddGroup->hide();

    connect(f_BtnAcceptGroup, SIGNAL(clicked()), this, SLOT(onAcceptGrInfoClicked()));
    connect(f_BtnRemoveGroup, SIGNAL(clicked()), this, SLOT(onRemoveGr()));
    //

    //add subject wid
    f_WidAddSubject = new QWidget(this);
    f_LytAddSubject = new QGridLayout();

    QLabel *LblAddSubj = new QLabel("Управление предметами", this);

    f_AllSubjects = new QListView();
    f_AllSubjects->setSelectionMode(QAbstractItemView::SingleSelection);

    QLabel *LblSubEd = new QLabel("Добавление предмета");

    f_BtnAcceptSubject = new QPushButton("+", this);
    f_BtnRemoveSubject = new QPushButton("-", this);
    f_BtnAcceptSubject->setMinimumSize(30,30);
    f_BtnRemoveSubject->setMinimumSize(30,30);


    QLabel *LblLeSubject = new QLabel("Название предмета:", this);
    f_LeSubject = new QLineEdit(this);

    f_LytAddSubject->addWidget(LblAddSubj,0,0,Qt::AlignmentFlag::AlignCenter);
    f_LytAddSubject->addWidget(f_BtnRemoveSubject,0,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAddSubject->addWidget(f_AllSubjects,1,0,1,2,Qt::AlignmentFlag::AlignCenter);

    f_LytAddSubject->addWidget(LblSubEd,2,0,1,2,Qt::AlignmentFlag::AlignCenter);

    f_LytAddSubject->addWidget(LblLeSubject,3,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddSubject->addWidget(f_LeSubject,3,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAddSubject->addWidget(f_BtnAcceptSubject,4,0,1,2,Qt::AlignmentFlag::AlignCenter);


    f_WidAddSubject->setLayout(f_LytAddSubject);
    f_LytMain->addWidget(f_WidAddSubject,4,0,Qt::AlignmentFlag::AlignCenter);

    f_WidAddSubject->hide();

    connect(f_BtnAcceptSubject, SIGNAL(clicked()), this, SLOT(onAcceptSubjInfoClicked()));
    connect(f_BtnRemoveSubject, SIGNAL(clicked()), this, SLOT(onRemoveSubj()));
    //

    //lesson wid
    f_WidAddLesson = new QWidget(this);
    f_LytAddLesson = new QGridLayout();

    QLabel *LblAddLess = new QLabel("Управление занятиями");

    f_AllLessons = new QTableView();
    f_AllLessons->setSelectionBehavior(QAbstractItemView::SelectRows);
    f_AllLessons->setSelectionMode(QAbstractItemView::SingleSelection);

    QLabel *LblLessEd = new QLabel("Добавление занятия");

    f_BtnAcceptLesson = new QPushButton("+", this);
    f_BtnRemoveLesson = new QPushButton("-", this);
    f_BtnAcceptLesson->setMinimumSize(30,30);
    f_BtnRemoveLesson->setMinimumSize(30,30);

    QLabel *LblAddLessonUsers = new QLabel("Доступные\nлогины\nпреподавателей", this);
    f_LvAddLessonUsers = new QListView();
    f_LvAddLessonUsers->setSelectionMode(QAbstractItemView::SingleSelection);

    QLabel *LblAddLessonGroups = new QLabel("Доступные\nгруппы", this);
    f_LvAddLessonGroups = new QListView();
    f_LvAddLessonGroups->setSelectionMode(QAbstractItemView::SingleSelection);

    QLabel *LblAddLessonSubj = new QLabel("Доступные\nпредметы", this);
    f_LvAddLessonSubj = new QListView();
    f_LvAddLessonSubj->setSelectionMode(QAbstractItemView::SingleSelection);

    QLabel *LblLessAmout = new QLabel("Количество занятий\nв семестре:", this);
    f_LessonsAmount = new QSpinBox(this);
    f_LessonsAmount->setMinimum(1);
    f_LessonsAmount->setMaximum(100);

    QLabel *LblLessDay = new QLabel("День:", this);
    f_AddLessonDay = new QComboBox(this);

    f_AddLessonDay->addItem("Пн");
    f_AddLessonDay->addItem("Вт");
    f_AddLessonDay->addItem("Ср");
    f_AddLessonDay->addItem("Чт");
    f_AddLessonDay->addItem("Пт");
    f_AddLessonDay->addItem("Вс");

    QLabel *LblLessTime = new QLabel("Начало:", this);
    f_AddLessonTime = new QComboBox(this);

    f_AddLessonTime->addItem("8:30");
    f_AddLessonTime->addItem("10:15");
    f_AddLessonTime->addItem("12:00");
    f_AddLessonTime->addItem("13:50");
    f_AddLessonTime->addItem("15:40");
    f_AddLessonTime->addItem("17:25");
    f_AddLessonTime->addItem("19:10");

    f_LytAddLesson->addWidget(LblAddLess,0,0,Qt::AlignmentFlag::AlignCenter);
    f_LytAddLesson->addWidget(f_BtnRemoveLesson,0,1,Qt::AlignmentFlag::AlignRight);

    f_LytAddLesson->addWidget(f_AllLessons,1,0,1,2,Qt::AlignmentFlag::AlignCenter);

    f_LytAddLesson->addWidget(LblLessEd,2,0,1,2,Qt::AlignmentFlag::AlignCenter);

    f_LytAddLesson->addWidget(LblAddLessonSubj,3,0,Qt::AlignmentFlag::AlignLeft);
    f_LytAddLesson->addWidget(f_LvAddLessonSubj,3,1,Qt::AlignmentFlag::AlignRight);

    f_LytAddLesson->addWidget(LblAddLessonUsers,4,0,Qt::AlignmentFlag::AlignCenter);
    f_LytAddLesson->addWidget(LblAddLessonGroups,4,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAddLesson->addWidget(f_LvAddLessonUsers,5,0,Qt::AlignmentFlag::AlignCenter);
    f_LytAddLesson->addWidget(f_LvAddLessonGroups,5,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAddLesson->addWidget(LblLessAmout,6,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddLesson->addWidget(f_LessonsAmount,6,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAddLesson->addWidget(LblLessDay,7,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddLesson->addWidget(f_AddLessonDay,7,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAddLesson->addWidget(LblLessTime,8,0,Qt::AlignmentFlag::AlignRight);
    f_LytAddLesson->addWidget(f_AddLessonTime,8,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAddLesson->addWidget(f_BtnAcceptLesson,9,0,1,2,Qt::AlignmentFlag::AlignRight);


    f_WidAddLesson->setLayout(f_LytAddLesson);
    f_LytMain->addWidget(f_WidAddLesson,5,0,Qt::AlignmentFlag::AlignCenter);

    f_WidAddLesson->hide();

    connect(f_BtnAcceptLesson, SIGNAL(clicked()), this, SLOT(onAcceptLessInfoClicked()));
    connect(f_BtnRemoveLesson, SIGNAL(clicked()), this, SLOT(onRemoveLess()));

    //

    //att check wid
    f_WidAttCheck = new QWidget(this);
    f_LytAttCheck = new QGridLayout();

    f_BtnRefresh = new QPushButton("Обновить",this);

    QLabel *LblAttCheck = new QLabel("Проверка посещаемости",this);

    f_TvAtt = new QTableView();

    QLabel *LblAttGroup = new QLabel("Доступные\nгруппы",this);
    f_Groups = new QListView();
    f_Groups->setSelectionMode(QAbstractItemView::SingleSelection);

    QLabel *LblSub = new QLabel("Доступные\nпредметы",this);
    f_Subjects = new QListView();
    f_Subjects->setSelectionMode(QAbstractItemView::SingleSelection);

    f_LytAttCheck->addWidget(LblAttCheck,0,0,1,2,Qt::AlignmentFlag::AlignCenter);
    f_LytAttCheck->addWidget(f_TvAtt,1,0,1,2,Qt::AlignmentFlag::AlignCenter);

    f_LytAttCheck->addWidget(LblAttGroup,2,0,Qt::AlignmentFlag::AlignRight);
    f_LytAttCheck->addWidget(f_Groups,2,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAttCheck->addWidget(LblSub,3,0,Qt::AlignmentFlag::AlignCenter);
    f_LytAttCheck->addWidget(f_Subjects,3,1,Qt::AlignmentFlag::AlignCenter);

    f_LytAttCheck->addWidget(f_BtnRefresh,4,0,1,2,Qt::AlignmentFlag::AlignCenter);

    f_WidAttCheck->setLayout(f_LytAttCheck);
    f_LytMain->addWidget(f_WidAttCheck,6,0,Qt::AlignmentFlag::AlignCenter);

    f_WidAttCheck->hide();

    connect(f_BtnRefresh, SIGNAL(clicked()), this, SLOT(refreshAttData()));

    f_LvAddLessonGroups->setMaximumSize(1000,1000);
    f_LvAddLessonSubj->setMaximumSize(1000,1000);
    f_LvAddLessonUsers->setMaximumSize(1000,1000);
    f_LvStGroup->setMaximumSize(1000,1000);
    f_TvAtt->setMaximumSize(1000,1000);
    f_AllGroups->setMaximumSize(1000,1000);
    f_AllLessons->setMaximumSize(1000,1000);
    f_AllStudents->setMaximumSize(1000,1000);
    f_AllSubjects->setMaximumSize(1000,1000);
    f_LvAddLessonGroups->setMaximumSize(1000,1000);
    f_LvAddLessonSubj->setMaximumSize(1000,1000);
    f_LvAddLessonUsers->setMaximumSize(1000,1000);
    f_Groups->setMaximumSize(1000,1000);
    f_Subjects->setMaximumSize(1000,1000);

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
"background-color: rgb(15,15,15);"
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
"alternate-background-color: rgb(15,15,15);"
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
    f_LblDAOErr->hide();
    f_WidAddGroup->hide();
    f_WidAddLesson->hide();
    f_WidAddStudent->hide();
    f_WidAddSubject->hide();
    f_WidAttCheck->hide();
    f_WidMenu->show();

    resetWidget();
}

void AdminMenu::refreshAttData()
{
    f_LblErr->hide();

    if(f_Groups->selectionModel()->selectedIndexes().size() == 0)
    {
        f_LblErr->show();
        return;
    }

    f_TvAtt->setModel(GeneralDAO::getInstance().getVisitingsByGroupSubj(
                f_Groups->model()->data(
                    f_Groups->selectionModel()->selectedIndexes().at(0)).toString(),
                f_Subjects->model()->data(
                    f_Subjects->selectionModel()->selectedIndexes().at(0)).toString()
                )
                      );
}

void AdminMenu::onNewSubjectClicked()
{
    f_WidMenu->hide();
    f_AllSubjects->setModel(
                GeneralDAO::getInstance().getAllSubjects()
                );
    f_WidAddSubject->show();
    f_BtnBackToMenu->show();
}

void AdminMenu::onNewGroupClicked()
{
    f_WidMenu->hide();
    f_AllGroups->setModel(
                GeneralDAO::getInstance().getAllGroupIds()
                );
    f_WidAddGroup->show();
    f_BtnBackToMenu->show();
}

void AdminMenu::onNewLessonClicked()
{
    f_AllLessons->setModel(
                GeneralDAO::getInstance().getAllLessons()
                );
    f_LvAddLessonGroups->setModel(
                GeneralDAO::getInstance().getAllGroupIds()
                );
    f_LvAddLessonUsers->setModel(
                GeneralDAO::getInstance().getAllTeacherLogins()
                );
    f_LvAddLessonSubj->setModel(
                GeneralDAO::getInstance().getAllSubjects()
                );
    f_WidMenu->hide();
    f_WidAddLesson->show();
    f_BtnBackToMenu->show();
}

void AdminMenu::onNewStudentClicked()
{
    f_AllStudents->setModel(
                GeneralDAO::getInstance().getAllStudents()
                );
    f_LvStGroup->setModel(
                GeneralDAO::getInstance().getAllGroupIds()
                );
    f_WidMenu->hide();
    f_WidAddStudent->show();
    f_BtnBackToMenu->show();
}

void AdminMenu::onAttCheckClicked()
{

    f_Groups->setModel(
                GeneralDAO::getInstance().getAllGroupIds()
                );
    f_Subjects->setModel(
                GeneralDAO::getInstance().getAllSubjects()
                );
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

        paintQR(f_LeStudNum->text());

    //DAO access add Student
        Student student;

        student.setGroup(f_LvStGroup->model()->data(f_LvStGroup->selectionModel()->selectedIndexes().at(0)).toString());
        student.setName(f_LeStName->text());
        student.setStudNum(f_LeStudNum->text());

        GeneralDAO::getInstance().addStudent(student);

        SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

                smtp.setUser("deltainspectortech@gmail.com");
                smtp.setPassword("xaxalesichka");

                MimeMessage message;

                message.setSender(new EmailAddress("deltainspectortech@gmail.com", "DeltaInspector"));
                message.addRecipient(new EmailAddress(f_eMail->text(), f_LeStName->text()));
                message.setSubject("Ваш регистрационный Qr код || DeltaInspector");

                MimeText text;
                text.setText("Добрый день, " + f_LeStName->text() + "!\n\n   Вот ваш регистрационный Qr код для использования приложения DeltaInspector.\n\nС уважением, команда DeltaInspector.");
                message.addPart(&text);

                MimeAttachment attachment (new QFile("QR.png"));
                message.addPart(&attachment);

                smtp.connectToHost();
                smtp.login();
                smtp.sendMail(message);
                smtp.quit();

                f_AllStudents->setModel(
                            GeneralDAO::getInstance().getAllStudents()
                            );
                f_LvStGroup->setModel(
                            GeneralDAO::getInstance().getAllGroupIds()
                            );
                resetWidget();

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
        GeneralDAO::getInstance().addGroup(f_LeGroup->text());

        f_AllGroups->setModel(
                    GeneralDAO::getInstance().getAllGroupIds()
                    );
        resetWidget();
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
        if(f_LvAddLessonUsers->selectionModel() == nullptr
                || f_LvAddLessonGroups->selectionModel() == nullptr
                || f_LvAddLessonSubj->selectionModel() == nullptr
                )
        {
            f_LblErr->show();
            return;
        }
        else
        {
            if(f_LvAddLessonUsers->selectionModel()->selectedRows().size() == 0
                    || f_LvAddLessonGroups->selectionModel()->selectedRows().size() == 0
                    || f_LvAddLessonSubj->selectionModel()->selectedRows().size() == 0
                    )
            {
                f_LblErr->show();
                return;
            }
        }

        //DAO access add Lesson
        Lesson less;

        less.setAmount(f_LessonsAmount->value());
        less.setGroup(f_LvAddLessonGroups->model()->data(f_LvAddLessonGroups->selectionModel()->selectedIndexes().at(0)).toString());
        less.setLessonTime(f_AddLessonDay->currentText() + " " + f_AddLessonTime->currentText());
        less.setName(f_LvAddLessonSubj->model()->data(f_LvAddLessonSubj->selectionModel()->selectedIndexes().at(0)).toString());           ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        less.setTeacher(f_LvAddLessonUsers->model()->data(f_LvAddLessonUsers->selectionModel()->selectedIndexes().at(0)).toString());

        GeneralDAO::getInstance().addLesson(less);

        f_AllLessons->setModel(
                    GeneralDAO::getInstance().getAllLessons()
                    );
        f_LvAddLessonGroups->setModel(
                    GeneralDAO::getInstance().getAllGroupIds()
                    );
        f_LvAddLessonUsers->setModel(
                    GeneralDAO::getInstance().getAllTeacherLogins()
                    );
        f_LvAddLessonSubj->setModel(
                    GeneralDAO::getInstance().getAllSubjects()
                    );
        resetWidget();
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
        GeneralDAO::getInstance().addSubject(f_LeSubject->text());
        f_AllSubjects->setModel(
                    GeneralDAO::getInstance().getAllSubjects()
                    );
        resetWidget();
    }
}

void AdminMenu::onRemoveSt()
{
    if(f_AllStudents->selectionModel() == nullptr)
    {
        f_LblErr->show();
        return;
    }
    else
    {
        if(f_AllStudents->selectionModel()->selectedRows().size() == 0)
        {
            f_LblErr->show();
            return;
        }
    }

    f_LblDAOErr->hide();
    QSqlError err = GeneralDAO::getInstance().removeStudent(
                f_AllStudents->model()->data(
                    f_AllStudents->selectionModel()->selectedIndexes().at(2)).toString()
                );

    if(err.type() != QSqlError::NoError)
    {
        f_LblDAOErr->setText("Не удается удалить студента,\nтак как на него ссылаются другие сущности!");
        f_LblDAOErr->show();
        return;
    }

    f_AllStudents->setModel(
                GeneralDAO::getInstance().getAllStudents()
                );

}

void AdminMenu::onRemoveGr()
{
    if(f_AllGroups->selectionModel() == nullptr)
    {
        f_LblErr->show();
        return;
    }
    else
    {
        if(f_AllGroups->selectionModel()->selectedRows().size() == 0)
        {
            f_LblErr->show();
            return;
        }
    }

    f_LblDAOErr->hide();
    QSqlError err = GeneralDAO::getInstance().removeGroup(
                f_AllGroups->model()->data(
                    f_AllGroups->selectionModel()->selectedIndexes().at(0)).toString()
                );
    if(err.type() != QSqlError::NoError)
    {
        f_LblDAOErr->setText("Не удается удалить группу,\nтак как на нее ссылаются другие сущности!");
        f_LblDAOErr->show();
        return;
    }

    f_AllGroups->setModel(
                GeneralDAO::getInstance().getAllGroupIds()
                );
}

void AdminMenu::onRemoveLess()
{
    if(f_AllLessons->selectionModel() == nullptr)
    {
        f_LblErr->show();
        return;
    }
    else
    {
        if(f_AllLessons->selectionModel()->selectedRows().size() == 0)
        {
            f_LblErr->show();
            return;
        }
    }


    f_LblDAOErr->hide();
    QSqlError err = GeneralDAO::getInstance().removeLesson(
                GeneralDAO::getInstance().getLessonIdByPK(
                    f_AllLessons->model()->data(
                        f_AllLessons->selectionModel()->selectedIndexes().at(2)).toString()
                    ,
                    f_AllLessons->model()->data(
                        f_AllLessons->selectionModel()->selectedIndexes().at(1)).toString()
                    )
                );
    if(err.type() != QSqlError::NoError)
    {
        f_LblDAOErr->setText("Не удается удалить занятие,\nтак как на него ссылаются другие сущности!");
        f_LblDAOErr->show();
        return;
    }

    f_AllLessons->setModel(
                GeneralDAO::getInstance().getAllLessons()
                );
    f_LvAddLessonGroups->setModel(
                GeneralDAO::getInstance().getAllGroupIds()
                );
    f_LvAddLessonUsers->setModel(
                GeneralDAO::getInstance().getAllTeacherLogins()
                );
    f_LvAddLessonSubj->setModel(
                GeneralDAO::getInstance().getAllSubjects()
                );
}

void AdminMenu::onRemoveSubj()
{
    if(f_AllSubjects->selectionModel() == nullptr)
    {
        f_LblErr->show();
        return;
    }
    else
    {
        if(f_AllSubjects->selectionModel()->selectedRows().size() == 0)
        {
            f_LblErr->show();
            return;
        }
    }

    f_LblDAOErr->hide();
    QSqlError err = GeneralDAO::getInstance().removeSubject(
                f_AllSubjects->model()->data(
                    f_AllSubjects->selectionModel()->selectedIndexes().at(0)).toString()
                );
    if(err.type() != QSqlError::NoError)
    {
        f_LblDAOErr->setText("Не удается удалить предмет,\nтак как на него ссылаются другие сущности!");
        f_LblDAOErr->show();
        return;
    }

    f_AllSubjects->setModel(
                GeneralDAO::getInstance().getAllSubjects()
                );
}

void AdminMenu::onRemoveSt()
{
    f_LblDAOErr->hide();
    QSqlError err = GeneralDAO::getInstance().removeStudent(
                f_AllStudents->model()->data(
                    f_AllStudents->selectionModel()->selectedIndexes().at(0)).toString()
                );

    if(err.type() != QSqlError::NoError)
    {
        f_LblDAOErr->setText(err.text());
        f_LblDAOErr->show();
        return;
    }

    f_AllStudents->setModel(
                GeneralDAO::getInstance().getAllStudents()
                );

}

void AdminMenu::onRemoveGr()
{
    f_LblDAOErr->hide();
    QSqlError err = GeneralDAO::getInstance().removeGroup(
                f_AllGroups->model()->data(
                    f_AllGroups->selectionModel()->selectedIndexes().at(0)).toString()
                );
    if(err.type() != QSqlError::NoError)
    {
        f_LblDAOErr->setText(err.text());
        f_LblDAOErr->show();
        return;
    }

    f_AllGroups->setModel(
                GeneralDAO::getInstance().getAllGroupIds()
                );
}

void AdminMenu::onRemoveLess()
{

    f_LblDAOErr->hide();
    QSqlError err = GeneralDAO::getInstance().removeLesson(
                GeneralDAO::getInstance().getLessonIdByPK(
                    f_AllLessons->model()->data(
                        f_AllLessons->selectionModel()->selectedIndexes().at(2)).toString()
                    ,
                    f_AllLessons->model()->data(
                        f_AllLessons->selectionModel()->selectedIndexes().at(1)).toString()
                    )
                );
    if(err.type() != QSqlError::NoError)
    {
        f_LblDAOErr->setText(err.text());
        f_LblDAOErr->show();
        return;
    }

    f_AllLessons->setModel(
                GeneralDAO::getInstance().getAllLessons()
                );
    f_LvAddLessonGroups->setModel(
                GeneralDAO::getInstance().getAllGroupIds()
                );
    f_LvAddLessonUsers->setModel(
                GeneralDAO::getInstance().getAllTeacherLogins()
                );
    f_LvAddLessonSubj->setModel(
                GeneralDAO::getInstance().getAllSubjects()
                );
}

void AdminMenu::onRemoveSubj()
{
    f_LblDAOErr->hide();
    QSqlError err = GeneralDAO::getInstance().removeSubject(
                f_AllSubjects->model()->data(
                    f_AllSubjects->selectionModel()->selectedIndexes().at(0)).toString()
                );
    if(err.type() != QSqlError::NoError)
    {
        f_LblDAOErr->setText(err.text());
        f_LblDAOErr->show();
        return;
    }

    f_AllSubjects->setModel(
                GeneralDAO::getInstance().getAllSubjects()
                );
}

