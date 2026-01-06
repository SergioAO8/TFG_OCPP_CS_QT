#include <cstdio>
#include "changeavalilability.h"
#include "ui_changeavalilability.h"
#include "nucli_sistema/ocpp_cs/ws_server.h"

ChangeAvalilability::ChangeAvalilability(int connectorId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChangeAvalilability)
    , connectorId{connectorId}
{
    ui->setupUi(this);
}

ChangeAvalilability::~ChangeAvalilability()
{
    delete ui;
}

void ChangeAvalilability::on_pushButton_clicked()
{
    char operation[256];
    snprintf(operation, sizeof(operation), "changeAvailability:{\"connectorId\":%d,\"type\":\"%s\"}", connectorId, ui->comboBox->currentText().toUtf8().constData());
    select_request(operation);
}

