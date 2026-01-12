#ifndef RESET_H
#define RESET_H

#include <QDialog>

namespace Ui {
class Reset;
}

class Reset : public QDialog
{
    Q_OBJECT

public:
    explicit Reset(int conectorId, QWidget *parent = nullptr);
    ~Reset();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Reset *ui;
    int connectorId;
};

#endif // RESET_H
