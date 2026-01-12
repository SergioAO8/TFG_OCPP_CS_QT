#ifndef CLEARCACHE_H
#define CLEARCACHE_H

#include <QDialog>

namespace Ui {
class ClearCache;
}

class ClearCache : public QDialog
{
    Q_OBJECT

public:
    explicit ClearCache(int conectorId, QWidget *parent = nullptr);
    ~ClearCache();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::ClearCache *ui;
    int connectorId;
};

#endif // CLEARCACHE_H
