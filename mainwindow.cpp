#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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
    connect(this, SIGNAL(sigLoginAccepted()), this, SLOT(onLoginAccepted()));
    //*********


    //making layout groups
    f_WidGroups = new QWidget(this);

    f_LytGroups = new QGridLayout(this);
    f_LvGroups = new QListView(this);
    f_LvGroups->setSelectionMode(QAbstractItemView::SingleSelection);
    f_BtnLogout = new QPushButton("Logout",this);

    f_LytGroups->addWidget(f_BtnLogout,0,0,Qt::AlignmentFlag::AlignLeft);
    f_LytGroups->addWidget(f_LvGroups,1,0,Qt::AlignmentFlag::AlignCenter);

    f_WidGroups->setLayout(f_LytGroups);
    f_LytMain->addWidget(f_WidGroups,0,0);

    f_WidGroups->hide();

    connect(f_BtnLogout, SIGNAL(clicked()), this, SLOT(onLogout()));
    connect(f_LvGroups, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onGroupSelected(const QModelIndex&)));
    //*********




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


        if(1 /*admin login*/)
        {
            f_AdmMenuIstc = new AdminMenu(this);
            setCentralWidget(f_AdmMenuIstc);
        }
        emit sigLoginAccepted();
        f_LePass->clear();
    }
    else
    {
        f_LblWrong->show();
        return;
    }
}

void MainWindow::onLoginAccepted()
{
    f_WidLogin->hide();
    f_currentLogin = f_LeLogin->text();
    //DAO access, get groups by login
    f_WidGroups->show();
}

void MainWindow::onLogout()
{
    f_WidGroups->hide();
    f_WidLogin->show();
}

void MainWindow::onGroupSelected(const QModelIndex&)
{
    QItemSelectionModel* select = f_LvGroups->selectionModel();

    QModelIndexList selectedRow = select->selectedRows();

    f_LvGroups->model()->data(selectedRow.at(0));
}

