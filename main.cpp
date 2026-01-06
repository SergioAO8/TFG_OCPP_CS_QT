#include "mainwindow.h"
#include <QApplication>
#include "web_socket_thread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WebSocketThread wsThread;
    wsThread.start();

    MainWindow w;
    w.show();

    int return_value = a.exec();

    wsThread.quit();
    wsThread.wait();

    return return_value;
}
