#include "web_socket_thread.h"
#include "nucli_sistema/ocpp_cs/ws_server.h"


WebSocketThread::WebSocketThread(QObject *parent)
    : QThread(parent)
{
}

void WebSocketThread::run()
{
    web_socket_server();
}
