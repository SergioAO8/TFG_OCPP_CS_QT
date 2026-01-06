#ifndef UNLOCKCONNECTOR_H
#define UNLOCKCONNECTOR_H

#include <QDialog>

namespace Ui {
class UnlockConnector;
}

class UnlockConnector : public QDialog
{
    Q_OBJECT

public:
    explicit UnlockConnector(int connectorId, QWidget *parent = nullptr);
    ~UnlockConnector();

private slots:
    void on_pushButton_clicked();

private:
    Ui::UnlockConnector *ui;
    int connectorId;
};

#endif // UNLOCKCONNECTOR_H
