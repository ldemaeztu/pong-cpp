#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H 

#include "mini/ini.h"

class ConfigLoader {
public:
    ConfigLoader(std::string filename);

    template <class T>
    T get(std::string section, std::string param) const
    {
        std::stringstream convert(m_config.get(section).get(param));
        T value;
        convert >> value;
        return value;    
    }

private:    
    mINI::INIStructure m_config;

};


#endif