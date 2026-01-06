#ifndef REMOTESTOPTRANSACTION_H
#define REMOTESTOPTRANSACTION_H

#include <QDialog>

namespace Ui {
class RemoteStopTransaction;
}

class RemoteStopTransaction : public QDialog
{
    Q_OBJECT

public:
    explicit RemoteStopTransaction(int connectorId, QWidget *parent = nullptr);
    ~RemoteStopTransaction();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RemoteStopTransaction *ui;
    int connectorId;
};

#endif // REMOTESTOPTRANSACTION_H
