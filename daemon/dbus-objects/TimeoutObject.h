#ifndef TIMEOUT_OBJECT_H
#define TIMEOUT_OBJECT_H


#include "BaseDbusObject.h"
#include <thread>


class TimeoutObject : public BaseDbusObject {
public:
    TimeoutObject(sdbus::IConnection& connection, sdbus::ObjectPath objectPath);

    void specificBehaviour() override;

    ~TimeoutObject();

private:
    void timerLoop();
    std::thread m_timerThread;
    bool m_running{true};


};




#endif