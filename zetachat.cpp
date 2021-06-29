#include "zetachat.h"
#include "ui_zetachat.h"

#include <QtGui>
#include <QDebug>

zetaChat::zetaChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::zetaChat)
{
    _name = "";
    f_Port = "";
    f_Ip = "";

    ui->setupUi(this);
    _sok = new QTcpSocket(this);
    connect(_sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    connect(_sok, SIGNAL(connected()), this, SLOT(onSokConnected()));
    connect(_sok, SIGNAL(disconnected()), this, SLOT(onSokDisconnected()));
    connect(_sok, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSokDisplayError(QAbstractSocket::SocketError)));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onLogoutClicked()));
}

zetaChat::~zetaChat()
{
    delete ui;
}

void zetaChat::onSokDisplayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, "Error", "The host was not found");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, "Error", "The connection was refused by the peer.");
        break;
    default:
        QMessageBox::information(this, "Error", "The following error occurred: "+_sok->errorString());
    }
}

void zetaChat::onSokReadyRead()
{
    QDataStream in(_sok);
    //���� ��������� ����� ���� ������ 2 ����� ��� ��� ������
    if (_blockSize == 0) {
        //���� ������ ������ 2 ���� ���� ���� ����� 2 �����
        if (_sok->bytesAvailable() < (int)sizeof(quint16))
            return;
        //��������� ������ (2 �����)
        in >> _blockSize;
        qDebug() << "_blockSize now " << _blockSize;
    }
    //���� ���� ���� ������� ���������
    if (_sok->bytesAvailable() < _blockSize)
        return;
    else
        //����� ��������� ����� ����
        _blockSize = 0;
    //3 ���� - ������� �������
    quint8 command;
    in >> command;
    qDebug() << "Received command " << command;

    switch (command)
    {
        case MyClient::comAutchSuccess:
        {
            ui->pbSend->setEnabled(true);
            AddToLog("Enter as "+_name,Qt::green);
        }
        break;
        case MyClient::comUsersOnline:
        {
            ui->pbSend->setEnabled(true);
            QString users;
            in >> users;
            if (users == "")
                return;
            QStringList l =  users.split(",");
            ui->lwUsers->addItems(l);
        }
        break;
        case MyClient::comPublicServerMessage:
        {
            QString message;
            in >> message;
            AddToLog("[PublicServerMessage]: "+message, Qt::red);
        }
        break;
        case MyClient::comMessageToAll:
        {
            QString user;
            in >> user;
            QString message;
            in >> message;
            AddToLog("["+user+"]: "+message);
        }
        break;
        case MyClient::comMessageToUsers:
        {
            QString user;
            in >> user;
            QString message;
            in >> message;
            AddToLog("["+user+"] (private): "+message, Qt::blue);
        }
        break;
        case MyClient::comPrivateServerMessage:
        {
            QString message;
            in >> message;
            AddToLog("[PrivateServerMessage]: "+message, Qt::red);
        }
        break;
        case MyClient::comUserJoin:
        {
            QString name;
            in >> name;
            ui->lwUsers->addItem(name);
            AddToLog(name+" joined", Qt::green);
        }
        break;
        case MyClient::comUserLeft:
        {
            QString name;
            in >> name;
            for (int i = 0; i < ui->lwUsers->count(); ++i)
                if (ui->lwUsers->item(i)->text() == name)
                {
                    ui->lwUsers->takeItem(i);
                    AddToLog(name+" left", Qt::green);
                    break;
                }
        }
        break;
        case MyClient::comErrNameInvalid:
        {
            QMessageBox::information(this, "Error", "Invalid name.");
            _sok->disconnectFromHost();
        }
        break;
        case MyClient::comErrNameUsed:
        {
            QMessageBox::information(this, "Error", "This name is already taken.");
            _sok->disconnectFromHost();
        }
        break;
    }
}

void zetaChat::onSokConnected()
{
    _blockSize = 0;
    AddToLog("Connected to "+_sok->peerAddress().toString()+":"+QString::number(_sok->peerPort()),Qt::green);

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << (quint8)MyClient::comAutchReq;
    out << _name;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
}

void zetaChat::onSokDisconnected()
{
    ui->pbSend->setEnabled(false);
    ui->lwUsers->clear();
    AddToLog("Disconnected from: "+_sok->peerAddress().toString()+":"+QString::number(_sok->peerPort()), Qt::green);
}

void zetaChat::on_pbConnect_clicked()
{
    _sok->connectToHost(f_Ip, f_Port.toInt());
}

void zetaChat::on_pbDisconnect_clicked()
{
    _sok->disconnectFromHost();
}

void zetaChat::on_cbToAll_clicked()
{
    if (ui->cbToAll->isChecked())
        ui->pbSend->setText("Send to all");
    else
        ui->pbSend->setText("Send to selected");
}

void zetaChat::on_pbSend_clicked()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    if (ui->cbToAll->isChecked())
        out << (quint8)MyClient::comMessageToAll;
    else
    {
        out << (quint8)MyClient::comMessageToUsers;
        QString s;
        foreach (QListWidgetItem *i, ui->lwUsers->selectedItems())
            s += i->text()+",";
        s.remove(s.length()-1, 1);
        out << s;
    }

    out << ui->pteMessage->document()->toPlainText();
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
    ui->pteMessage->clear();
}

void zetaChat::setName(const QString & p_p)
{
    _name = p_p;
}

void zetaChat::setIp(const QString & p_p)
{
    f_Ip = p_p;
}

void zetaChat::setPort(const QString & p_p)
{
    f_Port = p_p;
}

void zetaChat::onLogoutClicked()
{
    emit logoutSig();
}

void zetaChat::AddToLog(QString text, QColor color)
{
    ui->lwLog->insertItem(0, QTime::currentTime().toString()+" "+text);
}
