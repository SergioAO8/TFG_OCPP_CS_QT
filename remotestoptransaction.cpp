#include "remotestoptransaction.h"
#include "ui_remotestoptransaction.h"
#include "nucli_sistema/ocpp_cs/ws_server.h"

RemoteStopTransaction::RemoteStopTransaction(int connectorId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoteStopTransaction)
    , connectorId{connectorId}
{
    ui->setupUi(this);
}

RemoteStopTransaction::~RemoteStopTransaction()
{
    delete ui;
}

void RemoteStopTransaction::on_pushButton_clicked()
{
    char operation[256];
    snprintf(operation, sizeof(operation), "remoteStopTransaction:{\"transactionId\":%d}", ui->lineEdit->text().toInt());
    select_request(operation);
}

