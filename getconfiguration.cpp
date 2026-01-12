#include "getconfiguration.h"
#include "ui_getconfiguration.h"
#include "nucli_sistema/ocpp_cs/ws_server.h"
#include <QString>

GetConfiguration::GetConfiguration(int connectorId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GetConfiguration)
    , connectorId{connectorId}
{
    ui->setupUi(this);
}

GetConfiguration::~GetConfiguration()
{
    delete ui;
}

void GetConfiguration::on_pushButton_clicked()
{
    char tmp[256];
    snprintf(tmp, sizeof(tmp), "getConfiguration:{\"connectorId\":%d,\"key\":[", connectorId);
    QString keys = tmp;

    if (ui->checkBox->isChecked())
        keys += '\"' + ui->checkBox->text() + '\"';
    if (ui->checkBox_2->isChecked())
        keys += ",\"" + ui->checkBox_2->text() + '\"';
    if (ui->checkBox_3->isChecked())
        keys += ",\"" + ui->checkBox_3->text() + '\"';
    if (ui->checkBox_4->isChecked())
        keys += ",\"" + ui->checkBox_4->text() + '\"';
    if (ui->checkBox_5->isChecked())
        keys += ",\"" + ui->checkBox_5->text() + '\"';
    if (ui->checkBox_6->isChecked())
        keys += ",\"" + ui->checkBox_6->text() + '\"';
    if (ui->checkBox_7->isChecked())
        keys += ",\"" + ui->checkBox_7->text() + '\"';
    if (ui->checkBox_8->isChecked())
        keys += ",\"" + ui->checkBox_8->text() + '\"';
    if (ui->checkBox_9->isChecked())
        keys += ",\"" + ui->checkBox_9->text() + '\"';
    if (ui->checkBox_10->isChecked())
        keys += ",\"" + ui->checkBox_10->text() + '\"';
    if (ui->checkBox_11->isChecked())
        keys += ",\"" + ui->checkBox_11->text() + '\"';
    if (ui->checkBox_12->isChecked())
        keys += ",\"" + ui->checkBox_12->text() + '\"';
    if (ui->checkBox_13->isChecked())
        keys += ",\"" + ui->checkBox_13->text() + '\"';
    if (ui->checkBox_14->isChecked())
        keys += ",\"" + ui->checkBox_14->text() + '\"';
    if (ui->checkBox_15->isChecked())
        keys += ",\"" + ui->checkBox_15->text() + '\"';
    if (ui->checkBox_16->isChecked())
        keys += ",\"" + ui->checkBox_16->text() + '\"';
    if (ui->checkBox_17->isChecked())
        keys += ",\"" + ui->checkBox_17->text() + '\"';
    if (ui->checkBox_18->isChecked())
        keys += ",\"" + ui->checkBox_18->text() + '\"';
    if (ui->checkBox_19->isChecked())
        keys += ",\"" + ui->checkBox_19->text() + '\"';
    if (ui->checkBox_20->isChecked())
        keys += ",\"" + ui->checkBox_20->text() + '\"';
    if (ui->checkBox_21->isChecked())
        keys += ",\"" + ui->checkBox_21->text() + '\"';

    keys += "]}";

    const char *operation = keys.toUtf8().constData();
    select_request(operation);
}

