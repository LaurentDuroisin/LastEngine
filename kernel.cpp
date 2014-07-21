#include "kernel.h"
#include "VirtualModuleManager.h"

#include <cassert>
#include <windows.h> // TODO rewrite
#include <iostream>

namespace NLP
{
    Kernel::Kernel()
    {
        changeModuleManager();
        changeModulePreferences();
    }


    void Kernel::run(void)
    {
        do
        {
            m_restart = false;

            launchModuleManager();

        } while( m_restart );
    }

    void Kernel::launchModuleManager(void) // TODO rewrite
    {
        // load
        HINSTANCE handle = LoadLibrary( (m_moduleManagerFile + ".dll").c_str() );
        std::cerr << (m_moduleManagerFile + ".dll") << std::endl;
        assert( handle );

        MainFct fct = (MainFct)GetProcAddress(handle, "run");

        DWORD lastError = GetLastError();
        std::cerr << "General failure. GetLastError returned " << std::hex
        << lastError << ".";


        assert( fct );

        fct(this);

        // unload
        FreeLibrary(handle);
    }

    void Kernel::changeModuleManager(std::string filename)
    {
        m_moduleManagerFile = filename;
    }

    void Kernel::changeModulePreferences(std::string filename)
    {
        m_modulePreferencesFile = filename;
    }

    void Kernel::restart(void)
    {
        m_restart = true;
    }
}
