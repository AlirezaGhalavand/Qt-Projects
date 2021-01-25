#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QTcpServer>
#include <QAbstractSocket>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    bool sendMessage(QByteArray message);
    QString port;

signals:
    void clientConnected(QString socketName);
    void clientDisconnected(QString socketName);
    void clientReadyRead(QString message,QString socketName);

public slots:
    void start();
    void quit();
    void newConnection();
    void disconnected();
    void readyRead();

private:
    QTcpServer tcpServer;
    QVector<QTcpSocket*> myClients;
    bool connectionFlag;
};

#endif // SERVER_H
