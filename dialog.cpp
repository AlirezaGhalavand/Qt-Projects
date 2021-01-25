#include "dialog.h"
#include "ui_dialog.h"
#include <QDateTime>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //Start Button enability
    ui->btnStart->setEnabled(false);

    server = new Server(this);
    connect(server,SIGNAL(clientConnected(QString)),this,SLOT(clientConnected(QString)));
    connect(server,SIGNAL(clientDisconnected(QString)),this,SLOT(clientDisconnected(QString)));
    connect(server,SIGNAL(clientReadyRead(QString,QString)),this,SLOT(clientReadyRead(QString,QString)));

    //ui signals & slots
    connect(ui->txtPort,SIGNAL(textChanged(const QString &)),this,SLOT(portChanged()));
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btnStart_clicked()
{
    server->port = ui->txtPort->text();
    server->start();

    ui->textEdit->append(tr("<font color=\"green\"><b>Server started</b>, port </font>") + server->port + tr("<font color=\"green\"> is openned.</font>"));
    getCurrentDateTime();
    ui->textEdit->append("");

    ui->textEdit->append("Listening...");
    ui->textEdit->append("");

    ui->txtPort->clear();
}

void Dialog::clientConnected(QString socketName)
{    
    ui->textEdit->append("<font color=\"blue\"><b>Client </b></font>" + QString ("<font color=\"blue\">%1</font>").arg(socketName) + " <font color=\"blue\"><b> joined!</b></font>");
    getCurrentDateTime();
    ui->textEdit->append("");
}

void Dialog::clientDisconnected(QString socketName)
{    
    ui->textEdit->append("<font color=\"blue\"><b>Client </b></font>" + QString ("<font color=\"blue\">%1</font>").arg(socketName) + " <font color=\"blue\"><b> left!</b></font>");
    getCurrentDateTime();
    ui->textEdit->append("");
}

void Dialog::clientReadyRead(QString message,QString socketName)
{
    ui->textEdit->append("<font color=\"green\"><b>client </b></font>" + QString ("<font color=\"green\">%1</font>").arg(socketName + "<font color=\"green\"><b>: </b></font>") + message);    
    getCurrentDateTime();
    ui->textEdit->append("");
}

void Dialog::portChanged()
{
    //Start Button enability
    if(!ui->txtPort->text().isEmpty())
        ui->btnStart->setEnabled(true);
    else
        ui->btnStart->setEnabled(false);
}

void Dialog::on_btnSend_clicked()
{
    QByteArray m = ui->txtMessage->text().toLatin1();
    bool messageResult = server->sendMessage(m);
    if(messageResult)
    {
        ui->textEdit->append(m);
        getCurrentDateTime();
        ui->textEdit->append("");
        ui->txtMessage->clear();
    }
    else
        ui->textEdit->append("<font color=\"blue\"><b>No Connection!</b></font>");
}

void Dialog::getCurrentDateTime()
{
    ui->textEdit->append(QString ("<font color=\"red\"><small>%1</small></font>").arg(QDateTime::currentDateTime().toString()));
}
