#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onChargerConnected();
    void onChargerDisconnected();
    void onBootNotification(const QString &model, const QString &vendor);
    void onStatusNotification(int64_t conn1, int64_t conn2, QString id_tag1, QString id_tag2, int64_t transaction1, int64_t transaction2);

private slots:
    void on_mostrar_operacion1_clicked();

private:
    Ui::MainWindow *ui;
    QMap<QString, QPixmap> iconos;
};
#endif // MAINWINDOW_H
