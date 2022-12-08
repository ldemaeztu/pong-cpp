#include "configloader.hpp"

ConfigLoader::ConfigLoader(std::string filename)
{
    mINI::INIFile file(filename);
    file.read(m_config);
}