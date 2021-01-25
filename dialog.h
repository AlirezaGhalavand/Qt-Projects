#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void getCurrentDateTime();

private slots:
    void on_btnStart_clicked();
    void clientConnected(QString socketName);
    void clientDisconnected(QString socketName);
    void clientReadyRead(QString message,QString socketName);
    void portChanged();

    void on_btnSend_clicked();

private:
    Ui::Dialog *ui;
    Server *server;
};
#endif // DIALOG_H
