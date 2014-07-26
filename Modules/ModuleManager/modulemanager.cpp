#include "modulemanager.h"
#include "../PermanantData/IPermanantData.h"
#include <iostream>
#include <cassert>


EXPORT const char ** symbolList(void)
{
    static const char * symbols[] = {"", nullptr };
    return symbols;
}

namespace NLP
{
    bool checkCompatibility(const InfoModule & info)
    {
        const InfoModule & m_info = infoModuleManager();
        if( info.author() != m_info.author() )
            return false;
        if( info.interfaceName() != m_info.interfaceName() )
            return false;
        if( info.version() > m_info.version() )
            return false;
        return true;
    }

    ModuleManager::ModuleManager(VirtualKernel &kernel)
        : m_kernel(kernel)
    {
        InfoModule info = infoModuleManager();
        info.changeInterface( (InterfaceModule)this );
        info.changeCompatibility( checkCompatibility );
        m_loadedModules[info.interfaceName()] = info;
    }

    ModuleManager::~ModuleManager(void)
    {
        for( auto & pair : m_loadedModules )
        {
            if( pair.second )
                m_kernel.closeLibrary( pair.second.handle() );
        }
    }

    void ModuleManager::run(void)
    {
        load( infoPermanantData() );
        // ?? = load( preferences )
        // getModules
        // si !=, restart

        // load pre
        // si màj, restart

        // load all

        // game selector
    }

    InfoModule ModuleManager::load(const InfoModule & info)
    {
        auto it = m_loadedModules.find( info.interfaceName() );

        if( it != m_loadedModules.end() )
            return it->second;

        InfoModule loadedInfo;

        /* preferences
         * loadedInfo = load(preferences.file(), preferences.symbol(), info );
         */

        if( ! loadedInfo )
            loadedInfo = load( info.interfaceName(), "load" + info.interfaceName() );
        if( ! loadedInfo )
            loadedInfo = load( info.moduleName(), "load" + info.interfaceName() );

        if( ! loadedInfo )
            return loadedInfo;

        m_loadedModules[info.interfaceName()] = loadedInfo;
        return loadedInfo;
    }

    InfoModule ModuleManager::searchInfo(const std::string & file, const std::string & symbol)
    {
        InfoModule info = load(file, symbol);
        m_kernel.closeLibrary( info.handle() );
        return info;
    }

    InfoModule ModuleManager::load(const std::string &file, const std::string &symbolName)
    {
        InfoModule info;
        VirtualKernel::LibraryHandle handle = m_kernel.loadLibrary( file );
        if( handle )
        {
            VirtualKernel::LibrarySymbol symbol = m_kernel.searchSymbol(handle, symbolName );
            if( symbol )
            {

                InfoModule * infoPtr = nullptr;
                if( info )
                    infoPtr = &info;
                infoPtr = \
                        ((LoadFct)symbol)( infoPtr, *this );
                if( infoPtr )
                {
                    info = *(InfoModule *)infoPtr;
                    info.changeHandle(handle);
                }
            }
        }
        return info;
    }

    ModuleManager::SymbolList ModuleManager::searchSymbol(const std::string & file)
    {
        SymbolList list;
        VirtualKernel::LibraryHandle handle = m_kernel.loadLibrary( file );
        VirtualKernel::LibrarySymbol symbol = m_kernel.searchSymbol(handle, "symbolList");
        if( ! symbol )
            return list;
        SymbolListFct fct = (SymbolListFct)symbol;
        const char ** symbols = fct();
        while( *symbols )
        {
            list.push_back(*symbols);
            symbols++;
        }
        return list;
    }

}

void run(NLP::VirtualKernel & kernel)
{
    NLP::ModuleManager module( kernel );
    module.run();
}
