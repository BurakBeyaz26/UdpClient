#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QString>

#include <iostream>
#include <string>
#include <thread>

using namespace std;



class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void startCommunication();
    void process();
    void sendMessage(QString message);


    void setPort(quint16 port);
    quint16 getPort();

    void setIp(QString ip);
    QString getIp();

public slots:
    void errorOccured();
    void messageReceived();
    void onNewConnection();
    void connected();
    void disconnected();
    void hostFound();
    void closed();
private:
    QUdpSocket *udpsocket;
    quint16 m_port;
    QString m_ip;
signals:

};

#endif // CLIENT_H
