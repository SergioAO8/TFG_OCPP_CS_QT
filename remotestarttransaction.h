#ifndef REMOTESTARTTRANSACTION_H
#define REMOTESTARTTRANSACTION_H

#include <QDialog>

namespace Ui {
class RemoteStartTransaction;
}

class RemoteStartTransaction : public QDialog
{
    Q_OBJECT

public:
    explicit RemoteStartTransaction(int connectorId, QWidget *parent = nullptr);
    ~RemoteStartTransaction();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RemoteStartTransaction *ui;
    int connectorId;
};

#endif // REMOTESTARTTRANSACTION_H
