#include <QCoreApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    QString port,ip;

    qDebug() << "UDP CLIENT!\nIf you use with argument --> <port> <ip>";

    if(argc>2)
    {
        qDebug() << "with arguments...";

        port = argv[1];
        ip = argv[2];

        client.setPort(port.toInt());
        client.setIp(ip);
        client.startCommunication();
    }
    else
    {
        qDebug() << "without argument...";

        client.setPort(7001);
        client.setIp("192.168.0.35");
        client.startCommunication();
    }

    return a.exec();
}
