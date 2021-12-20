#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{

}

void Client::startCommunication()
{
    udpsocket = new QUdpSocket(this);
    udpsocket->connectToHost(QHostAddress(m_ip),m_port);

    connect(udpsocket,&QUdpSocket::readyRead,this,&Client::messageReceived);
    connect(udpsocket,&QUdpSocket::hostFound,this,&Client::onNewConnection);
    connect(udpsocket,&QUdpSocket::connected,this,&Client::connected);
    connect(udpsocket,&QUdpSocket::disconnected,this,&Client::disconnected);
    connect(udpsocket,&QUdpSocket::hostFound,this,&Client::hostFound);
    connect(udpsocket,&QUdpSocket::aboutToClose,this,&Client::closed);

    std::thread sendThread(&Client::process,this);
    sendThread.detach();
}

void Client::errorOccured()
{
    qDebug() << "error: " << udpsocket->errorString();
}
void Client::connected()
{
    qDebug() << "connected";
}
void Client::disconnected()
{
    qDebug() << "disconnected";
}

void Client::hostFound()
{
    qDebug() << "hostFound";
}

void Client::closed()
{
    qDebug() << "closed";
}

void Client::sendMessage(QString message)
{
    QByteArray Data;
    Data.append(message.toUtf8());

    udpsocket->writeDatagram(Data, QHostAddress(m_ip), m_port);
}

void Client::messageReceived()
{
    QByteArray buffer;
    buffer.resize(udpsocket->pendingDatagramSize());

    QHostAddress sender = QHostAddress(m_ip);
    quint16 senderPort = m_port;
    udpsocket->readDatagram(buffer.data(), buffer.size(), &sender,&senderPort);

    if(buffer.size() > 0)
    {
        qDebug() << "Message from: " << sender.toString() << ", Message port: " << senderPort << ", Message: " << buffer;
    }
    else
    {
        qDebug() << "Return message not received";
    }
}

void Client::process()
{
    string message;

    cout << "Enter message to server: " << endl;
    while(getline(cin,message))
    {
        sendMessage(QString::fromStdString(message));
    }
}

void Client::onNewConnection()
{
    qDebug() << "onNewConnection";
}

void Client::setPort(quint16 port)
{
    m_port = port;
}
quint16 Client::getPort()
{
    return m_port;
}

void Client::setIp(QString ip)
{
    m_ip = ip;
}
QString Client::getIp()
{
    return m_ip;
}
