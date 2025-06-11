#ifndef TIMEOUT_PROXY_H
#define TIMEOUT_PROXY_H

#include "BaseProxy.h"
#include <thread>

class TimeoutProxy : public BaseProxy {
public:
    TimeoutProxy(sdbus::IConnection& connection, sdbus::ServiceName serviceName, sdbus::ObjectPath objectPath);

    void specificBehaviour() override;

    ~TimeoutProxy();

private:
    void timerLoop();
    std::thread m_timerThread;
    bool m_running{true};
};



#endif