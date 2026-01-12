#include "datatransfer.h"
#include "ui_datatransfer.h"
#include "nucli_sistema/ocpp_cs/ws_server.h"

DataTransfer::DataTransfer(int connectorId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DataTransfer)
    , connectorId{connectorId}
{
    ui->setupUi(this);
}

DataTransfer::~DataTransfer()
{
    delete ui;
}

void DataTransfer::on_pushButton_clicked()
{
    char operation[256];
    snprintf(operation, sizeof(operation), "dataTransfer:{\"connectorId\":%d,\"vendorId\":\"%s\",\"messageId\":\"%s\",\"data\":\"%s\"}", connectorId, ui->lineEdit->text().toUtf8().constData(), ui->lineEdit_2->text().toUtf8().constData(), ui->plainTextEdit->toPlainText().toUtf8().constData());
    select_request(operation);
}

