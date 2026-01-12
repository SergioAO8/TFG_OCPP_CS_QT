#ifndef GETCONFIGURATION_H
#define GETCONFIGURATION_H

#include <QDialog>

namespace Ui {
class GetConfiguration;
}

class GetConfiguration : public QDialog
{
    Q_OBJECT

public:
    explicit GetConfiguration(int conectorId, QWidget *parent = nullptr);
    ~GetConfiguration();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GetConfiguration *ui;
    int connectorId;
};

#endif // GETCONFIGURATION_H
