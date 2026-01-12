#include "clearcache.h"
#include "ui_clearcache.h"
#include "nucli_sistema/ocpp_cs/ws_server.h"

ClearCache::ClearCache(int connectorId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ClearCache)
    , connectorId{connectorId}
{
    ui->setupUi(this);
}

ClearCache::~ClearCache()
{
    delete ui;
}

void ClearCache::on_pushButton_2_clicked()
{
    char operation[256];
    snprintf(operation, sizeof(operation), "clearCache:{\"connectorId\":%d}", connectorId);
    select_request(operation);
}

