/*
 *  FILE
 *      ws_server.c - servidor WebSocket del sistema de control
 *  PROJECT
 *      TFG - Implementació d'un Sistema de Control per Punts de Càrrega de Vehicles Elèctrics.
 *  DESCRIPTION
 *      Archivo donde se configura y se crea el servidor WebSocket del sistema de control.
 *      Tambien se gestiona el envio de peticiones al cargador por parte del usuario.
 *  AUTHOR
 *      Sergio Abate
 *  OPERATING SYSTEM
 *      Linux
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include <ws.h>
#include <QObject>
#include "ws_server.h"
#include "charger.h"
#include "BootNotificationConfJSON.h"
#include "../../backend_notifier.h"

#define RESET   "\e[0m"
#define YELLOW  "\e[0;33m"
#define RED     "\e[0;31m"
#define BLUE    "\e[0;34m"
#define CYAN    "\e[0;36m"
#define GREEN   "\e[0;32m"

uint8_t current_num_chargers = 0;

Charger charger1 = Charger(1, -1);

// Prototipos de las funciones
static void onopen(ws_cli_conn_t client);
static void onclose(ws_cli_conn_t client);
static void onmessage(ws_cli_conn_t client, const unsigned char *msg, uint64_t size, int type);
static int get_charger_index();
static int get_charger_index(int charger_id);
static void send_information1(Charger &ch);
static void send_information2(Charger &ch);

/*
 *  NAME
 *      main - main() del servidor y del sistema de control.
 *  SYNOPSIS
 *      int main(int argc, char* argv[])
 *  DESCRIPTION
 *      main() del servidor i del sistema de control. Crea un thread por cada
 *      conexión recibida.
 *  RETURN VALUE
 *      Nada.
 */
void web_socket_server()
{
    // configuro el syslog
    int loglevel = LOG_DEBUG;
    setlogmask(LOG_UPTO(loglevel));
    openlog(NULL, LOG_PID | LOG_NDELAY | LOG_PERROR, LOG_USER);

    // crea un thread por cada connexión, este se encarga de recibir las peticiones del cargador y los mensajes de la web
    struct ws_server ws;
    ws.host          = "localhost";
    ws.port          = 8080;
    ws.thread_loop   = 0; // de esta manera ws_socket() es bloqueante
    ws.timeout_ms    = 1000;
    ws.evs.onopen    = &onopen;
    ws.evs.onclose   = &onclose;
    ws.evs.onmessage = &onmessage;
    ws_socket(&ws);
}

/*
 *  NAME
 *      onopen - Inicializa cada connexión que se abre.
 *  SYNOPSIS
 *      onopen(ws_cli_conn_t client);
 *  DESCRIPTION
 *      Inicializa la connexión con el cliente y el sistema de control. Se ejecuta en abrir una connexión.
 *  RETURN VALUE
 *      Nada.
 */
static void onopen(ws_cli_conn_t client)
{
    char *cli;
    cli = ws_getaddress(client);
    syslog(LOG_NOTICE, "Connection opened, addr: %s\n", cli);

    // busco el primer index de cargador disponible y lo assigno si hay espacio
    int index = get_charger_index();
    printf("%s, index = %d\n", __func__, index);
    switch(index) {
        case 1:
            printf("set_client1\n");
            charger1.set_client(client);

            QMetaObject::invokeMethod(&BackendNotifier::instance(),
                                      "chargerConnected",
                                      Qt::QueuedConnection);
            break;
        default:
            syslog(LOG_WARNING, "%s: Warning: Cargador no existente\n", __func__);
            break;
    }
}

/*
 *  NAME
 *      onclose - Cierra la connexión con el cliente.
 *  SYNOPSIS
 *      void onclose(ws_cli_conn_t client);
 *  DESCRIPTION
 *      Cierra la connexión con el cliente. Se ejecuta al cerrar una connexión.
 *  RETURN VALUE
 *      Res.
 */
static void onclose(ws_cli_conn_t client)
{
    int index = get_charger_index(client);
    if (index != -1) {
        syslog(LOG_DEBUG, "%s: index = %d\n", __func__, index);
        char *cli;
        cli = ws_getaddress(client);
        syslog(LOG_NOTICE, "Connection closed, addr: %s\n", cli);

        // Reseteo la información de los cargadores que se muestra en la web
        switch(index) {
        case 1:
            charger1.set_client(-1);
            charger1.set_current_vendor("");
            charger1.set_current_model("");

            QMetaObject::invokeMethod(&BackendNotifier::instance(),
                                      "chargerDisconnected",
                                      Qt::QueuedConnection);
            break;
        default:
            syslog(LOG_WARNING, "%s: Cargador no existente\n", __func__);
            break;
        }
    }
    else
        syslog(LOG_WARNING, "%s: Warning: no se ha encontrado el cargador\n", __func__);
}

/*
 *  NAME
 *      onmessage - Recibe los mensajes del cargador.
 *  SYNOPSIS
 *      void onmessage(ws_cli_conn_t client, const unsigned char *msg, uint64_t size, int type);
 *  DESCRIPTION
 *      Recibe los mensajes del cargador y los envia al objecto Charger cosrrespondiente para gestionarlos.
 *  RETURN VALUE
 *      Nada.
 */
static void onmessage(ws_cli_conn_t client, const unsigned char *msg, uint64_t size, int type)
{
    // mensaje de un cargador
    int index = get_charger_index(client); // busca qué cargador es
    printf("%s, index = %d\n", __func__, index);
    if (index != -1) {
        char *cli;
        cli = ws_getaddress(client);
        syslog(LOG_INFO, "%sRECEIVED MESSAGE: %s (%lu), from: %s%s\n", BLUE, msg,
            size, cli, RESET);

        switch(index) {
        case 1:
            charger1.system_on_receive((char *) msg);
            break;
        default:
            syslog(LOG_WARNING, "%s: Warning: Cargador no existente\n", __func__);
        }
    }
    else
        syslog(LOG_ERR, "%s: Error: no se ha encontrado el cargador\n", __func__);
}


/*
 *  NAME
 *      ws_send - Envia los mensajes al cargador o al servidor web.
 *  SYNOPSIS
 *      void ws_send(const char *option, char *text, ws_cli_conn_t client)
 *  DESCRIPTION
 *      Envia los mensajes al cargador o al servidor web. Segun el tipo
 *      de mensaje a enviar, se imprime de un color diferent en el terminal.
 *  RETURN VALUE
 *      Nada.
 */
void ws_send(const char *option, char *text, ws_cli_conn_t client)
{
    if (strcmp(option, "CALL") == 0) {
        ws_sendframe_txt(client, text);
        syslog(LOG_INFO, "%sSENDING REQUEST: %s%s\n", CYAN, text, RESET);
    }
    else if (strcmp(option, "CALL RESULT") == 0) {
        ws_sendframe_txt(client, text);
        syslog(LOG_INFO, "%sSENDING CONFIRMATION: %s%s\n\n", YELLOW, text, RESET);
    }
    else if (strcmp(option, "CALL ERROR") == 0) {
        ws_sendframe_txt(client, text);
        syslog(LOG_INFO, "%sSENDING ERROR: %s%s\n", RED, text, RESET);
    }
}

/*
 *  NAME
 *      select_request - Permite al usuario enviar peticiones al cargador.
 *  SYNOPSIS
 *      void *select_request(ChargerVars *vars, const char *operation)
 *  DESCRIPTION
 *      El usuario escoge qué mensaje enviar, se envia al objecto Charger correspondiente
 *      para gestionarlo, y este posteriormente lo envia al cargador.
 *  RETURN VALUE
 *      Res.
 */
void select_request(const char *operation)
{
    char message[1024];
    memset(message, 0, 1024); // limpio el buffer
    snprintf(message, sizeof(message), "%s", operation);

    // se analiza el mensaje del servidor web para saber qué operación se tiene que enviar
    char *action = strtok(message, ":");
    syslog(LOG_DEBUG, "action: %s\n", action);
    if (strcmp(action, "changeAvailability") == 0) {
        char *request = strtok(0, "");
        charger1.send_request('1', request);
    }
    else if (strcmp(action, "clearCache") == 0) {
        char *request = strtok(0, "");
        charger1.send_request('2', request);
    }
    else if (strcmp(action, "dataTransfer") == 0) {
        char *request = strtok(0, "");
        charger1.send_request('3', request);
    }
    else if (strcmp(action, "getConfiguration") == 0) {
        char *request = strtok(0, "");
        charger1.send_request('4', request);
    }
    else if (strcmp(action, "remoteStartTransaction") == 0) {
        char *request = strtok(0, "");
        charger1.send_request('5', request);
    }
    else if (strcmp(action, "remoteStopTransaction") == 0) {
        char *request = strtok(0, "");
        charger1.send_request('6', request);
    }
    else if (strcmp(action, "reset") == 0) {
        char *request = strtok(0, "");
        charger1.send_request('7', request);
    }
    else if (strcmp(action, "unlockConnector") == 0) {
        char *request = strtok(0, "");
        charger1.send_request('8', request);
    }
    else
        syslog(LOG_DEBUG, "desconocido\n");

    memset(message, 0, 1024); // limpio el buffer
}


/*
 *  NAME
 *      get_charger_index - Devuelve el índice del primer Charger libre.
 *  SYNOPSIS
 *      int get_charger_index();
 *  DESCRIPTION
 *      Devuelve el índice del primer Charger libre.
 *  RETURN VALUE
 *      Si todo va bien, devuelve la primera posición libre.
 *      En caso contrario, retorna -1.
 */
static int get_charger_index()
{
    if (charger1.get_client() == static_cast<ws_cli_conn_t>(-1))
        return 1;
    else
        return -1; // no hay posiciones libres
}

/*
 *  NAME
 *      get_charger_index - Devuelve el índice del Charger con client igual al parámetro.
 *  SYNOPSIS
 *      int get_charger_index(int client);
 *  DESCRIPTION
 *      Devuelve el índice del Charger con client igual al parámetro.
 *  RETURN VALUE
 *      Si todo va bien, devuelve el índice del Charger con client igual al parámetro.
 *      En caso contrario, retorna -1.
 */
static int get_charger_index(int client)
{
    if (charger1.get_client() == static_cast<ws_cli_conn_t>(client))
        return 1;
    else
        return -1; // no hay posiciones libres
}

