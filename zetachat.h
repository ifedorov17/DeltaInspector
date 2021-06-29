#ifndef ZETACHAT_H
#define ZETACHAT_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include "myclient.h"
#include <QMessageBox>
class MyClient;



namespace Ui {
class zetaChat;
}

class zetaChat : public QWidget
{
    Q_OBJECT

public:
    explicit zetaChat(QWidget *parent = nullptr);
    ~zetaChat();

public slots:

    void onSokConnected();
    void onSokDisconnected();
    void onSokReadyRead();
    void onSokDisplayError(QAbstractSocket::SocketError socketError);

    void on_pbConnect_clicked();
    void on_pbDisconnect_clicked();
    void on_cbToAll_clicked();
    void on_pbSend_clicked();

public slots:
    void setName(const QString&);
    void setIp(const QString&);
    void setPort(const QString&);

    void onLogoutClicked();


private:

    Ui::zetaChat *ui;

    QTcpSocket *_sok;
    quint16 _blockSize;
    QString _name;
    QString f_Ip;
    QString f_Port;
    void AddToLog(QString text, QColor color = Qt::black);

signals:

    void logoutSig();

};

#endif // ZETACHAT_H
