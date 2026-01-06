#ifndef CHANGEAVALILABILITY_H
#define CHANGEAVALILABILITY_H

#include <QDialog>

namespace Ui {
class ChangeAvalilability;
}

class ChangeAvalilability : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeAvalilability(int conectorId, QWidget *parent = nullptr);
    ~ChangeAvalilability();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChangeAvalilability *ui;
    int connectorId;
};

#endif // CHANGEAVALILABILITY_H
