#include "mainwindow.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QZXing::registerQMLTypes();
    //pre init
    f_CentralWidget = new QWidget;
    f_LytMain = new QGridLayout;
    f_CentralWidget->setLayout(f_LytMain);
    //*********

    //making login layout
    f_WidLogin = new QWidget(this);

    f_LytLogin = new QGridLayout(this);
    f_BtnLogin = new QPushButton("Login", this);
    f_LeLogin = new QLineEdit(this);
    f_LePass = new QLineEdit(this);

    QLabel* LblLogin = new QLabel("Login:", this);
    QLabel* LblPass = new QLabel("Password:", this);
    f_LblWrong = new QLabel("Wrong login or password.", this);
    f_LblWrong->setStyleSheet("QLabel { color : red; }");


    f_LytLogin->addWidget(LblLogin,0,0,Qt::AlignmentFlag::AlignCenter);
    f_LytLogin->addWidget(f_LeLogin,1,0,Qt::AlignmentFlag::AlignCenter);

    f_LytLogin->addWidget(LblPass,2,0,Qt::AlignmentFlag::AlignCenter);
    f_LytLogin->addWidget(f_LePass,3,0,Qt::AlignmentFlag::AlignCenter);

    f_LytLogin->addWidget(f_BtnLogin,4,0,Qt::AlignmentFlag::AlignCenter);
    f_LytLogin->addWidget(f_LblWrong,5,0,Qt::AlignmentFlag::AlignCenter);
    f_LblWrong->hide();

    f_WidLogin->setLayout(f_LytLogin);
    f_LytMain->addWidget(f_WidLogin,0,0);

    connect(f_BtnLogin, SIGNAL(clicked()), this, SLOT(onLoginBtnClicked()));
    connect(this, SIGNAL(sigLoginAcceptedUser()), this, SLOT(onLoginAcceptedUser()));
    connect(this, SIGNAL(sigLoginAcceptedAdmin()), this, SLOT(onLoginAcceptedAdmin()));
    //*********


    //making layout groups
    f_WidGroups = new QWidget(this);

    QStringList *tempGroupsSL = new QStringList;
    tempGroupsSL->push_back("group1");
    tempGroupsSL->push_back("group2");
    tempGroupsSL->push_back("group3");

    QStringListModel *tempGroupsSLM = new QStringListModel(this);
    tempGroupsSLM->setStringList(*tempGroupsSL);

    f_LytGroups = new QGridLayout(this);
    QLabel *LblGroups = new QLabel("Select a group");
    f_LvGroups = new QListView(this);

    f_LvGroups->setModel(tempGroupsSLM);

    f_LvGroups->setSelectionMode(QAbstractItemView::SingleSelection);
    f_BtnLogout = new QPushButton("Logout",this);

    f_LytGroups->addWidget(f_BtnLogout,0,0,Qt::AlignmentFlag::AlignLeft);
    f_LytGroups->addWidget(LblGroups,1,0,Qt::AlignmentFlag::AlignCenter);
    f_LytGroups->addWidget(f_LvGroups,2,0,Qt::AlignmentFlag::AlignCenter);

    f_WidGroups->setLayout(f_LytGroups);
    f_LytMain->addWidget(f_WidGroups,0,0);

    f_WidGroups->hide();

    connect(f_BtnLogout, SIGNAL(clicked()), this, SLOT(onLogout()));
    connect(f_LvGroups, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onGroupSelected(const QModelIndex&)));
    //*********

    //making layout times
    f_WidTime = new QWidget(this);
    f_LytTime = new QGridLayout(this);

    QStringList *tempTimesSL = new QStringList;
    tempTimesSL->push_back("10");
    tempTimesSL->push_back("12");
    tempTimesSL->push_back("13");

    QStringListModel *tempTimesSLM = new QStringListModel(this);
    tempTimesSLM->setStringList(*tempTimesSL);

    QLabel *LblTime = new QLabel("Select a time");
    f_LvTimes = new QListView(this);


    f_LvTimes->setModel(tempTimesSLM);


    f_LvTimes->setSelectionMode(QAbstractItemView::SingleSelection);
    f_BtnBackToGroups = new QPushButton("Back");

    f_LytTime->addWidget(f_BtnBackToGroups,0,0,Qt::AlignmentFlag::AlignLeft);
    f_LytTime->addWidget(LblTime,1,0,Qt::AlignmentFlag::AlignCenter);
    f_LytTime->addWidget(f_LvTimes,2,0,Qt::AlignmentFlag::AlignCenter);

    f_WidTime->setLayout(f_LytTime);
    f_LytMain->addWidget(f_WidTime,0,0);

    f_WidTime->hide();

    connect(f_LvTimes, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTimeSelected(const QModelIndex&)));
    connect(f_BtnBackToGroups, SIGNAL(clicked()), this, SLOT(onBackToGroups()));
    //

    //making cam lyt;
    f_WidCam = new QWidget(this);
    f_LytCam = new QGridLayout(this);
    f_BtnBackToSelections = new QPushButton("Back",this);

    connect(f_BtnBackToSelections, SIGNAL(clicked()), this, SLOT(onBackToSelections()));


    f_cam = new QQuickWidget(this);
    f_cam->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    f_cam->setResizeMode(QQuickWidget::SizeRootObjectToView);    
    f_cam->rootContext()->setContextProperty("w", this);

    f_LytCam->addWidget(f_cam,1,0,1,2,Qt::AlignmentFlag::AlignCenter);
    f_LytCam->addWidget(f_BtnBackToSelections,0,0,1,1,Qt::AlignmentFlag::AlignLeft);

    f_WidCam->setLayout(f_LytCam);

    f_LytMain->addWidget(f_WidCam,0,0);

    f_WidCam->hide();
    //

    //making verification lyt
    f_WidVer = new QWidget(this);
    f_LytVer = new QGridLayout(this);
    f_BtnVerify = new QPushButton("Verify", this);
    f_BtnDecline = new QPushButton("Decline", this);

    connect(f_BtnVerify, SIGNAL(clicked()), this, SLOT(onVerified()));
    connect(f_BtnDecline, SIGNAL(clicked()), this, SLOT(onDeclined()));

    f_LblDataRead = new QLabel(this);

    f_LytVer->addWidget(f_LblDataRead,0,0,1,2,Qt::AlignmentFlag::AlignCenter);
    f_LytVer->addWidget(f_BtnVerify,1,0,1,1,Qt::AlignmentFlag::AlignCenter);
    f_LytVer->addWidget(f_BtnDecline,1,1,1,1,Qt::AlignmentFlag::AlignCenter);

    f_WidVer->setLayout(f_LytVer);

    f_LytMain->addWidget(f_WidVer,0,0);

    f_WidVer->hide();

    //

    //admin menu instance
    f_AdmMenuIstc = new AdminMenu(this);
    f_LytMain->addWidget(f_AdmMenuIstc,0,0);
    f_AdmMenuIstc->hide();
    connect(f_AdmMenuIstc, SIGNAL(logout()), this, SLOT(onAdminLogout()));
    //

    this->setCentralWidget(f_CentralWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::dataCleanUp()
{
    f_currentLogin.clear();
    f_currentTime.clear();
    f_currentGroup.clear();
    f_StrDataRead.clear();
    f_currentLessonId = -1;
}

void MainWindow::onLoginBtnClicked()
{
    //DAO access, validate login/pass
    f_LblWrong->hide();

    if(1 /*Valid login*/)
    {
        emit sigLoginAcceptedUser();
        f_LePass->clear();
    }
    else if(1 /*admin login*/)
    {
        emit sigLoginAcceptedAdmin();
        f_LePass->clear();
    }
    else
    {
        f_LblWrong->show();
        return;
    }
}

void MainWindow::onLoginAcceptedUser()
{
    f_WidLogin->hide();
    f_currentLogin = f_LeLogin->text();
    //DAO access, get groups by login
    f_WidGroups->show();
}

void MainWindow::onLoginAcceptedAdmin()
{
    f_WidLogin->hide();
    f_currentLogin = f_LeLogin->text();
    f_AdmMenuIstc->show();
}

void MainWindow::onLogout()
{
    dataCleanUp();
    f_WidGroups->hide();
    f_WidLogin->show();
}

void MainWindow::onGroupSelected(const QModelIndex& idx)
{
    f_currentGroup = f_LvGroups->model()->data(idx).toString();

    qDebug() << f_currentGroup;

    f_WidGroups->hide();
    f_WidTime->show();
}

void MainWindow::onBackToGroups()
{
    dataCleanUp();
    f_WidGroups->show();
    f_WidTime->hide();
}

void MainWindow::onTimeSelected(const QModelIndex &idx)
{
    f_currentTime = f_LvTimes->model()->data(idx).toString();

    qDebug() << f_currentTime;

    f_WidTime->hide();
    f_WidCam->show();

}

void MainWindow::onBackToSelections()
{
    dataCleanUp();
    f_WidCam->hide();
    f_WidGroups->show();
}

void MainWindow::onVerified()
{
    //DAO access, add attendance
    f_LblDataRead->setText("");
    f_StrDataRead.clear();

    f_WidVer->hide();
    f_WidCam->show();
}

void MainWindow::onDeclined()
{
    f_LblDataRead->setText("");
    f_StrDataRead.clear();

    f_WidVer->hide();
    f_WidCam->show();
}

void MainWindow::onAdminLogout()
{
    f_AdmMenuIstc->hide();
    f_WidLogin->show();
    f_AdmMenuIstc->resetWidget();
}

void MainWindow::onTagGot(QString tag)
{
    qDebug()<< "\n              !*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!" << tag << "\n              !*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!";
    f_WidCam->hide();

    f_StrDataRead = tag;
    f_LblDataRead->setText(f_StrDataRead);

    f_WidVer->show();
}

