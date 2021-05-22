#include "mainwindow.h"

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

    f_LytGroups = new QGridLayout(this);
    QLabel *LblGroups = new QLabel("Select a group");
    f_LvGroups = new QListView(this);
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

    QLabel *LblTime = new QLabel("Select a time");
    f_LvTimes = new QListView(this);
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

    f_cam = new QQuickWidget(this);
    f_cam->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    f_cam->setResizeMode(QQuickWidget::SizeRootObjectToView);
    //f_LytCam->addWidget(f_cam);

    f_WidCam->setLayout(f_LytCam);
    f_LytMain->addWidget(f_cam,0,0);

    f_cam->hide();

    connect(f_cam, SIGNAL(qmlSignal(QString)),
                           this, SLOT(onTagGot(QString)));


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

void MainWindow::onAdminLogout()
{
    f_AdmMenuIstc->hide();
    f_WidLogin->show();
    f_AdmMenuIstc->resetWidget();
}

void MainWindow::onTagGot(QString tag)
{
    qDebug() << tag << "\n         !!!!!!!!!!!!";
}

