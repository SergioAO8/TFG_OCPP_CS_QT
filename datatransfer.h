#ifndef DATATRANSFER_H
#define DATATRANSFER_H

#include <QDialog>

namespace Ui {
class DataTransfer;
}

class DataTransfer : public QDialog
{
    Q_OBJECT

public:
    explicit DataTransfer(int conectorId, QWidget *parent = nullptr);
    ~DataTransfer();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DataTransfer *ui;
    int connectorId;
};

#endif // DATATRANSFER_H
