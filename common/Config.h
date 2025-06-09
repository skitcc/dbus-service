#ifndef CONFIG_H
#define CONFIG_H

#include <sdbus-c++/Types.h>
#include <string>

namespace dbus_daemon{

class Config {
public:
    static const sdbus::ServiceName getServiceName();
    static const std::string getBaseObjectPath();
    static const std::string_view getConfigurationDir();


private:
    static const inline sdbus::ServiceName m_serviceName{"com.system.configurationManager"};
    static const inline std::string m_baseObjectPath{"/com/system/configurationManager/Application"};
    static const inline std::string_view m_configurationDir{"../data/"};
};

}




#endif