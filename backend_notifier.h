#ifndef BACKEND_NOTIFIER_H
#define BACKEND_NOTIFIER_H

#include <QObject>

class BackendNotifier : public QObject
{
    Q_OBJECT
public:
    static BackendNotifier& instance() {
        static BackendNotifier inst;
        return inst;
    }

signals:
    void chargerConnected();
    void chargerDisconnected();
    void bootNotification(const QString &model, const QString &vendor);
    void statusNotification(int64_t conn1, int64_t conn2, QString id_tag1, QString id_tag2, int64_t transaction1, int64_t transaction2);

private:
    BackendNotifier() = default;
    ~BackendNotifier() = default;
    BackendNotifier(const BackendNotifier&) = delete;
    BackendNotifier& operator=(const BackendNotifier&) = delete;
};

#endif // BACKEND_NOTIFIER_H
