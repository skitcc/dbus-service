#include "proxiesManager/ProxiesManager.h"

int main() {

    std::unique_ptr<ProxiesManager> manager = std::make_unique<ProxiesManager>();
    manager->runApplication();
}