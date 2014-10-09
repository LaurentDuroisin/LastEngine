#include "permanantData.h"

#include <iostream>
#include <cassert>

EXPORT const char ** symbolList(void)
{
    static const char * symbols[] = {"loadPermanantData", nullptr };
    return symbols;
}

EXPORT const NLP::InfoModule * loadPermanantData(const NLP::InfoModule * asked, NLP::IModuleManager & moduleManager)
{
    static NLP::InfoModule info = NLP::infoPermanantData();
    static NLP::PermanantData interface = NLP::PermanantData(moduleManager);
    info.changeInterface( (NLP::InterfaceModule) & interface);

    if( asked )
    {
        if( ! NLP::checkCompatibility( *asked ) )
        {
            return nullptr;
        }
    }


    return & info;
}

namespace NLP
{
    bool checkCompatibility(const InfoModule & info)
    {
        const InfoModule & m_info = infoPermanantData();
        if( info.author() != m_info.author() )
            return false;
        if( info.interfaceName() != m_info.interfaceName() )
            return false;
        if( info.version() > m_info.version() )
            return false;
        return true;
    }

    PermanantData::PermanantData(IModuleManager & moduleManager)
        : m_moduleManager(moduleManager)
    {
        std::cerr << "loaded" << std::endl;
    }

}
