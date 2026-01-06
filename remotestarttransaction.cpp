#include "remotestarttransaction.h"
#include "ui_remotestarttransaction.h"
#include "nucli_sistema/ocpp_cs/ws_server.h"

RemoteStartTransaction::RemoteStartTransaction(int connectorId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoteStartTransaction)
    , connectorId{connectorId}
{
    ui->setupUi(this);
}

RemoteStartTransaction::~RemoteStartTransaction()
{
    delete ui;
}

void RemoteStartTransaction::on_pushButton_clicked()
{
    char operation[256];
    snprintf(operation, sizeof(operation), "remoteStartTransaction:{\"connectorId\":%d,\"idTag\":\"%s\"}", connectorId, ui->lineEdit->text().toUtf8().constData());
    select_request(operation);
}

