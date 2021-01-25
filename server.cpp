#include "server.h"
#include "dialog.h"

Server::Server(QObject *parent) : QObject(parent)
{
    connect(&tcpServer,&QTcpServer::newConnection,this,&Server::newConnection);
}

void Server::start()
{
    tcpServer.listen(QHostAddress::Any,port.toUShort());
}

void Server::quit()
{
    tcpServer.close();
}

void Server::newConnection()
{
    QTcpSocket* socket = tcpServer.nextPendingConnection();

    //Set random name to each client
    QString random = QString::number(qrand() % 1000);

    socket->setObjectName(random);

    myClients.push_back(socket);

    connect(socket,&QTcpSocket::disconnected,this,&Server::disconnected);
    connect(socket,&QTcpSocket::readyRead,this,&Server::readyRead);

    connectionFlag = 1;

    emit clientConnected(socket->objectName());
}

void Server::disconnected()
{
    connectionFlag = 0;

    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    emit clientDisconnected(socket->objectName());

    myClients.removeAll(socket);

    socket->deleteLater();
}

void Server::readyRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    QString message = (QString)socket->readAll();

    emit clientReadyRead(message,socket->objectName());
}

bool Server::sendMessage(QByteArray message)
{
    if(connectionFlag)
    {
        for(auto &client : myClients) {
            client->write(message);
          }
        return 1;
    }

    else
        return 0;
}
