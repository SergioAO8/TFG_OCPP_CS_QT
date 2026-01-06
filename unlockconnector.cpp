#include "unlockconnector.h"
#include "ui_unlockconnector.h"
#include "nucli_sistema/ocpp_cs/ws_server.h"

UnlockConnector::UnlockConnector(int connectorId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UnlockConnector)
    , connectorId{connectorId}
{
    ui->setupUi(this);
}

UnlockConnector::~UnlockConnector()
{
    delete ui;
}

void UnlockConnector::on_pushButton_clicked()
{
    char operation[256];
    snprintf(operation, sizeof(operation), "unlockConnector:{\"connectorId\":%d}", connectorId);
    select_request(operation);
}

