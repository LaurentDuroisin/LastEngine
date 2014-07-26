#include "kernel.h"
#include "VirtualModuleManager.h"

#include <cassert>
#include <sstream>

#ifdef _WIN32
    #include <windows.h> // TODO rewrite
#else
    #include <dlfcn.h>
#endif

#include <iostream>

#if not defined _WIN32 and not defined __linux__
    #warning "Your OS may be not supported"
#endif

namespace NLP
{
    Kernel::Kernel()
    {
        changeModuleManager();
        changePreferences();
    }


    void Kernel::run(void)
    {
        do
        {
            m_restart = false;

            launchModuleManager();

        } while( m_restart );
    }

    void Kernel::launchModuleManager(void)
    {
        LibraryHandle handle = loadLibrary(m_moduleManagerFile);

        MainFct fct = (MainFct) searchSymbol(handle, "run");

        if( fct )
            fct( *this);
        else
            std::cerr << libraryError() << std::endl;

        closeLibrary(handle);
    }

    void Kernel::changeModuleManager(std::string filename)
    {
        m_moduleManagerFile = filename;
    }

    void Kernel::changePreferences(std::string filename)
    {
        m_preferencesFile = filename;
    }

    void Kernel::restart(void)
    {
        m_restart = true;
    }

#ifdef _WIN32

    const std::string Kernel::m_libraryExtension = ".dll";

    Kernel::LibraryHandle Kernel::loadLibrary(const std::string & filename) const
    {
        HINSTANCE handle = LoadLibrary( (filename + libraryExtension() ).c_str() );
        return handle ;
    }

    std::string Kernel::libraryError(void) const
    {
        DWORD lastError = GetLastError();
        std::stringstream ss("LibraryError Windows code : ");
        ss << (int)lastError;
        return ss.str();
    }

    Kernel::LibrarySymbol Kernel::searchSymbol(Kernel::LibraryHandle handle,
                                               const std::string & symbolName) const
    {
        if( ! handle )
            return nullptr;

        return (LibrarySymbol)GetProcAddress( (HINSTANCE)handle, symbolName.c_str() );
    }

    void Kernel::closeLibrary(Kernel::LibraryHandle handle) const
    {
        if( handle )
            FreeLibrary( (HINSTANCE)handle);
    }
#else
    #warning "not tested"

    const std::string Kernel::m_libraryExtension = ".so";

    Kernel::LibraryHandle Kernel::loadLibrary(const std::string & filename) const
    {
        LibraryHandle handle = dlopen( (filename + libraryExtension() ).c_str(), RTLD_NOW | RTLD_GLOBAL );
        return handle ;
    }

    std::string Kernel::libraryError(void) const
    {
        return dlerror();
    }

    Kernel::LibrarySymbol Kernel::searchSymbol(Kernel::LibraryHandle handle,
                                               const std::string & symbolName) const
    {
        if( ! handle )
            return nullptr;

        return (LibrarySymbol)dlsym( (void *)handle, symbolName.c_str() );
    }

    void Kernel::closeLibrary(Kernel::LibraryHandle handle) const
    {
        if( handle )
            dlclose( (void *)handle);
    }
#endif
}
