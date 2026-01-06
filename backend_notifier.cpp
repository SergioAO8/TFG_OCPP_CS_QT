#include "backend_notifier.h"

static BackendNotifier& instance() {
    static BackendNotifier inst;
    return inst;
}
