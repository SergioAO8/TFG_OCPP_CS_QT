#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "backend_notifier.h"
#include <QPixmap>
#include "changeavalilability.h"
#include "remotestarttransaction.h"
#include "remotestoptransaction.h"
#include "unlockconnector.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    iconos["charging"]    = QPixmap(":/resources/img/charging.png");
    iconos["fallada"]     = QPixmap(":/resources/img/fallada.png");
    iconos["unknown"]     = QPixmap(":/resources/img/unknown.png");
    iconos["disponible"]  = QPixmap(":/resources/img/disponible.png");
    iconos["finishing"]   = QPixmap(":/resources/img/finishing.png");
    iconos["preparing"]   = QPixmap(":/resources/img/preparing.png");
    iconos["no_disponible"]= QPixmap(":/resources/img/no_disponible.png");
    iconos["suspended_ev"]= QPixmap(":/resources/img/suspended_ev.png");
    iconos["suspended_evse"]= QPixmap(":/resources/img/suspended_evse.png");

    // pongo imagen predeterminada del estado de los cargadores
    //QPixmap icon(":/resources/img/unknown.png");
    ui->label_img_conector1->setPixmap(iconos["unknown"].scaled(100, 100, Qt::KeepAspectRatio));
    ui->label_img_conector2->setPixmap(iconos["unknown"].scaled(100, 100, Qt::KeepAspectRatio));

    connect(&BackendNotifier::instance(),
            &BackendNotifier::chargerConnected,
            this,
            &MainWindow::onChargerConnected);

    connect(&BackendNotifier::instance(),
            &BackendNotifier::chargerDisconnected,
            this,
            &MainWindow::onChargerDisconnected);

    connect(&BackendNotifier::instance(),
            &BackendNotifier::bootNotification,
            this,
            &MainWindow::onBootNotification);

    connect(&BackendNotifier::instance(),
            &BackendNotifier::statusNotification,
            this,
            &MainWindow::onStatusNotification);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onChargerConnected()
{
    ui->label_estado_general->setText(QString("ESTADO DEL CARGADOR 1: Conectado"));
}

void MainWindow::onChargerDisconnected()
{
    ui->label_estado_general->setText(QString("ESTADO DEL CARGADOR 1: No conectado"));
    ui->label_model->setText("(chargePointModel: cargador no conectado)");
    ui->label_vendor->setText("(chargePointVendor: cargador no conectado)");
    ui->label_img_conector1->setPixmap(iconos["unknown"].scaled(100, 100, Qt::KeepAspectRatio));
    ui->label_img_conector2->setPixmap(iconos["unknown"].scaled(100, 100, Qt::KeepAspectRatio));
}

void MainWindow::onBootNotification(const QString &model, const QString &vendor)
{
    ui->label_model->setText(QString("chargePointModel: %1").arg(model));
    ui->label_vendor->setText(QString("chargePointVendor: %1").arg(vendor));
}

void MainWindow::onStatusNotification(int64_t conn1, int64_t conn2, QString id_tag1, QString id_tag2, int64_t transaction1, int64_t transaction2)
{
    switch (conn1) {
    case 0:
        ui->label_img_conector1->setPixmap(iconos["disponible"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    case 1:
        ui->label_img_conector1->setPixmap(iconos["charging"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    case 2:
        ui->label_img_conector1->setPixmap(iconos["fallada"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    case 3:
        ui->label_img_conector1->setPixmap(iconos["finishing"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    case 4:
        ui->label_img_conector1->setPixmap(iconos["preparing"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    case 5:
        ui->label_img_conector1->setPixmap(iconos["suspended_evse"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    case 6:
        ui->label_img_conector1->setPixmap(iconos["suspended_ev"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    case 7:
        ui->label_img_conector1->setPixmap(iconos["no_disponible"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    case 8:
        ui->label_img_conector1->setPixmap(iconos["unknown"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    default:
        ui->label_img_conector1->setPixmap(iconos["unknown"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    }

    switch (conn2) {
    case 0:
        ui->label_img_conector2->setPixmap(iconos["disponible"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    case 1:
        ui->label_img_conector2->setPixmap(iconos["charging"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    case 2:
        ui->label_img_conector2->setPixmap(iconos["fallada"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    case 3:
        ui->label_img_conector2->setPixmap(iconos["finishing"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    case 4:
        ui->label_img_conector2->setPixmap(iconos["suspended_ev"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    case 5:
        ui->label_img_conector2->setPixmap(iconos["suspended_evse"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    case 6:
        ui->label_img_conector2->setPixmap(iconos["disponible"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    case 7:
        ui->label_img_conector2->setPixmap(iconos["no_disponible"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    case 8:
        ui->label_img_conector2->setPixmap(iconos["unknown"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    default:
        ui->label_img_conector2->setPixmap(iconos["unknown"].scaled(100, 100, Qt::KeepAspectRatio));
        break;
    }

    if (id_tag1 == "no_charging")
        ui->label_idTag1->setText("idTag: (cargador sin\nninguna transacción");
    else
        ui->label_idTag1->setText(QString("idTag: %1").arg(id_tag1));

    if (id_tag2 == "no_charging")
        ui->label_idTag2->setText("idTag: (cargador sin\nninguna transacción");
    else
        ui->label_idTag2->setText(QString("idTag: %1").arg(id_tag2));

    if (transaction1 == -1)
        ui->label_transactionId1->setText("transactionId: (cargador sin\nninguna transacción");
    else
        ui->label_transactionId1->setText(QString("transactionId: %1").arg(transaction1));

    if (transaction2 == -1)
        ui->label_transactionId2->setText("transactionId: (cargador sin\nninguna transacción");
    else
        ui->label_transactionId2->setText(QString("transactionId: %1").arg(transaction2));
}

void MainWindow::on_mostrar_operacion1_clicked()
{
    if (ui->operaciones1->currentText() == "ChangeAvailability") {
        ChangeAvalilability changeAvailability(1, this);
        changeAvailability.setModal(true);
        changeAvailability.exec();
    }
    else if (ui->operaciones1->currentText() == "RemoteStartTransaction") {
        RemoteStartTransaction remoteStartTransaction(1, this);
        remoteStartTransaction.setModal(true);
        remoteStartTransaction.exec();
    }
    else if (ui->operaciones1->currentText() == "RemoteStopTransaction") {
        RemoteStopTransaction remoteStopTransaction(1, this);
        remoteStopTransaction.setModal(true);
        remoteStopTransaction.exec();
    }
    else if (ui->operaciones1->currentText() == "UnlockConnector") {
        UnlockConnector unlockConnector(1, this);
        unlockConnector.setModal(true);
        unlockConnector.exec();
    }
}

