#include "reset.h"
#include "ui_reset.h"
#include "nucli_sistema/ocpp_cs/ws_server.h"

Reset::Reset(int connectorId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Reset)
    , connectorId{connectorId}
{
    ui->setupUi(this);
}

Reset::~Reset()
{
    delete ui;
}

void Reset::on_pushButton_clicked()
{
    char operation[256];
    snprintf(operation, sizeof(operation), "reset:{\"connectorId\":%d,\"type\":\"%s\"}", connectorId, ui->comboBox->currentText().toUtf8().constData());
    select_request(operation);
}

