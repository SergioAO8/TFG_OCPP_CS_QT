#ifndef _WEB_SOCKET_THREAD_H_
#define _WEB_SOCKET_THREAD_H_

#include <QThread>

class WebSocketThread : public QThread
{
    Q_OBJECT
public:
    explicit WebSocketThread(QObject *parent = nullptr);

protected:
    void run() override;
};

#endif

