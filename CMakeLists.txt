cmake_minimum_required(VERSION 3.19)
project(ocpp_cs_with_qt LANGUAGES C CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_resources(RESOURCES
    resources.qrc
)

qt_add_executable(ocpp_cs_with_qt
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    nucli_sistema/ocpp_cs/charger.cpp nucli_sistema/ocpp_cs/charger.h nucli_sistema/ocpp_cs/error_message.cpp nucli_sistema/ocpp_cs/error_message.h nucli_sistema/ocpp_cs/lib_json_includes.h nucli_sistema/ocpp_cs/utils.cpp nucli_sistema/ocpp_cs/utils.h nucli_sistema/ocpp_cs/ws_server.cpp nucli_sistema/ocpp_cs/ws_server.h
    web_socket_thread.cpp
    web_socket_thread.h
    backend_notifier.h
    ${RESOURCES}
    changeavalilability.h changeavalilability.cpp changeavalilability.ui

    remotestoptransaction.h remotestoptransaction.cpp remotestoptransaction.ui
    unlockconnector.h unlockconnector.cpp unlockconnector.ui
    remotestarttransaction.h remotestarttransaction.cpp remotestarttransaction.ui


)

# Crear librería estática
add_library(jsoncodec STATIC
    nucli_sistema/json_codec/AuthorizeConfJSON.c nucli_sistema/json_codec/AuthorizeConfJSON.h nucli_sistema/json_codec/AuthorizeReqJSON.c nucli_sistema/json_codec/AuthorizeReqJSON.h nucli_sistema/json_codec/BootNotificationConfJSON.c nucli_sistema/json_codec/BootNotificationConfJSON.h nucli_sistema/json_codec/BootNotificationReqJSON.c nucli_sistema/json_codec/BootNotificationReqJSON.h nucli_sistema/json_codec/ChangeAvailabilityConfJSON.c nucli_sistema/json_codec/ChangeAvailabilityConfJSON.h nucli_sistema/json_codec/ChangeAvailabilityReqJSON.c nucli_sistema/json_codec/ChangeAvailabilityReqJSON.h nucli_sistema/json_codec/ClearCacheConfJSON.c nucli_sistema/json_codec/ClearCacheConfJSON.h nucli_sistema/json_codec/ClearCacheReqJSON.c nucli_sistema/json_codec/ClearCacheReqJSON.h nucli_sistema/json_codec/DataTransferConfJSON.c nucli_sistema/json_codec/DataTransferConfJSON.h nucli_sistema/json_codec/DataTransferReqJSON.c nucli_sistema/json_codec/DataTransferReqJSON.h nucli_sistema/json_codec/GetConfigurationConfJSON.c nucli_sistema/json_codec/GetConfigurationConfJSON.h nucli_sistema/json_codec/GetConfigurationReqJSON.c nucli_sistema/json_codec/GetConfigurationReqJSON.h nucli_sistema/json_codec/HeartbeatConfJSON.c nucli_sistema/json_codec/HeartbeatConfJSON.h nucli_sistema/json_codec/HeartbeatReqJSON.c nucli_sistema/json_codec/HeartbeatReqJSON.h nucli_sistema/json_codec/MeterValuesConfJSON.c nucli_sistema/json_codec/MeterValuesConfJSON.h nucli_sistema/json_codec/MeterValuesReqJSON.c nucli_sistema/json_codec/MeterValuesReqJSON.h nucli_sistema/json_codec/mystrdup.c nucli_sistema/json_codec/mystrdup.h nucli_sistema/json_codec/RemoteStartTransactionConfJSON.c nucli_sistema/json_codec/RemoteStartTransactionConfJSON.h nucli_sistema/json_codec/RemoteStartTransactionReqJSON.c nucli_sistema/json_codec/RemoteStartTransactionReqJSON.h nucli_sistema/json_codec/RemoteStopTransactionConfJSON.c nucli_sistema/json_codec/RemoteStopTransactionConfJSON.h nucli_sistema/json_codec/RemoteStopTransactionReqJSON.c nucli_sistema/json_codec/RemoteStopTransactionReqJSON.h nucli_sistema/json_codec/ResetConfJSON.c nucli_sistema/json_codec/ResetConfJSON.h nucli_sistema/json_codec/ResetReqJSON.c nucli_sistema/json_codec/ResetReqJSON.h nucli_sistema/json_codec/StartTransactionConfJSON.c nucli_sistema/json_codec/StartTransactionConfJSON.h nucli_sistema/json_codec/StartTransactionReqJSON.c nucli_sistema/json_codec/StartTransactionReqJSON.h nucli_sistema/json_codec/StatusNotificationConfJSON.c nucli_sistema/json_codec/StatusNotificationConfJSON.h nucli_sistema/json_codec/StatusNotificationReqJSON.c nucli_sistema/json_codec/StatusNotificationReqJSON.h nucli_sistema/json_codec/StopTransactionConfJSON.c nucli_sistema/json_codec/StopTransactionConfJSON.h nucli_sistema/json_codec/StopTransactionReqJSON.c nucli_sistema/json_codec/StopTransactionReqJSON.h nucli_sistema/json_codec/TriggerMessageConfJSON.h nucli_sistema/json_codec/TriggerMessageReqJSON.h nucli_sistema/json_codec/UnlockConnectorConfJSON.c nucli_sistema/json_codec/UnlockConnectorConfJSON.h nucli_sistema/json_codec/UnlockConnectorReqJSON.c nucli_sistema/json_codec/UnlockConnectorReqJSON.h
)

target_include_directories(jsoncodec PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/nucli_sistema/json_codec
    /usr/include/cjson
)

target_include_directories(ocpp_cs_with_qt PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}                      # -I.
    /usr/include/cjson                                # librería del sistema
    /usr/local/include/wsserver                       # librería del sistema
)

find_package(Threads REQUIRED)  # para pthread

target_link_libraries(jsoncodec PUBLIC cjson)

target_link_libraries(ocpp_cs_with_qt PRIVATE
    Qt::Core
    Qt::Widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/nucli_sistema/lib_ws/libws.a
    cjson
    list
    sqlite3
    jsoncodec
    Threads::Threads
)

target_compile_options(ocpp_cs_with_qt PRIVATE
    -O2 -Wall -Wno-unused-function -g
)

include(GNUInstallDirs)

install(TARGETS ocpp_cs_with_qt
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ocpp_cs_with_qt
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
