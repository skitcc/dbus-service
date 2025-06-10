#include "TimeoutObject.h"
#include "iostream"

TimeoutObject::TimeoutObject(sdbus::IConnection& connection, sdbus::ObjectPath objectPath) : BaseDbusObject(connection, objectPath) {}


void TimeoutObject::specificBehaviour() {
    if (!m_timerThread.joinable()) {
        m_timerThread = std::thread(&TimeoutObject::timerLoop, this);
    }
}


void TimeoutObject::timerLoop() {
    std::cout << "in timer loop!\n";
    while (m_running) {
        auto timeoutIt = m_conf.find("Timeout");
        auto phraseIt = m_conf.find("TimeoutPhrase");

        int currentTimeout = 0;
        std::string currentPhrase{};

        if (timeoutIt == m_conf.end() || phraseIt == m_conf.end()) {
            return;
        }

        if (std::holds_alternative<int>(timeoutIt->second)) {
            currentTimeout = std::get<int>(timeoutIt->second);
        } else {
            return;
        }

        if (std::holds_alternative<std::string>(phraseIt->second)) {
            currentPhrase = std::get<std::string>(phraseIt->second);
        } else {
            return;
        }

        std::cout << currentPhrase << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(currentTimeout));
    }
}

TimeoutObject::~TimeoutObject() {
    m_running = false;
    if (m_timerThread.joinable()) {
        m_timerThread.join();
    }
}