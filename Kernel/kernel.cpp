#include "kernel.h"

#include <cassert>
#include <cerrno>
#include <fstream>

#ifdef _WIN32
    #include <windows.h>
    #include <sstream>
#else
    #include <dlfcn.h>
#endif

#if not defined _WIN32 and not defined __linux__
    #warning "Your OS may be not supported"
#endif

namespace LE
{
    const std::string Kernel::m_moduleExtension = ".lem";
    const std::string Kernel::m_initFilename = "init";


    void Kernel::run(void)
    {
        do
        {
            m_restart = false;

            launchInitPhase();

            if( ! m_new_init_file.empty() )
            {
                std::ofstream output(m_initFilename + m_moduleExtension, std::ios_base::out | std::ios_base::trunc);
                std::ifstream input(m_new_init_file + m_moduleExtension);

                if( ! output )
                    throw std::system_error(EACCES, std::system_category(), m_initFilename + m_moduleExtension);
                if( ! input )
                    throw std::system_error(EACCES, std::system_category(), m_new_init_file + m_moduleExtension);

                output << input.rdbuf();

                if( ! output )
                    throw std::system_error(1, std::system_category(), "Error when copying "+ m_new_init_file + m_moduleExtension +" to " + m_initFilename + m_moduleExtension + ".");
            }

        } while( m_restart );
    }

    void Kernel::launchInitPhase(void)
    {
        LibraryHandle handle = loadLibrary(m_initFilename);

        if( ! handle )
            throw std::system_error(EACCES, std::system_category(), m_initFilename + m_moduleExtension);

        IKernel::InitFunction fct = (IKernel::InitFunction) searchSymbol(handle, "init");

        if( ! fct )
            throw std::system_error(ENOEXEC, std::system_category(), m_initFilename + m_moduleExtension);
        fct( *this);

        closeLibrary(handle);
    }

    void Kernel::restart(bool restart, const std::string &new_init_file)
    {
        m_restart = restart;
        m_new_init_file = new_init_file;
    }

    void Kernel::restart(bool restart, const std::string &&new_init_file)
    {
        m_restart = restart;
        m_new_init_file = std::move(new_init_file);
    }

#ifdef _WIN32


    Kernel::LibraryHandle Kernel::loadLibrary(const std::string & filename) const
    {
        HINSTANCE handle = LoadLibrary( (filename  + m_moduleExtention ).c_str() );
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
        assert(handle);
        return (LibrarySymbol)GetProcAddress( (HINSTANCE)handle, symbolName.c_str() );
    }

    void Kernel::closeLibrary(Kernel::LibraryHandle handle) const
    {
        assert(handle);
        FreeLibrary( (HINSTANCE)handle);
    }
#else

    Kernel::LibraryHandle Kernel::loadLibrary(const std::string & filename) const
    {
        LibraryHandle handle = dlopen( (filename + m_moduleExtension ).c_str(), RTLD_NOW | RTLD_GLOBAL );
        return handle ;
    }

    std::string Kernel::libraryError(void) const
    {
        return dlerror();
    }

    Kernel::LibrarySymbol Kernel::searchSymbol(Kernel::LibraryHandle handle,
                                               const std::string & symbolName) const
    {
        assert(handle);

        return (LibrarySymbol)dlsym( (void *)handle, symbolName.c_str() );
    }

    void Kernel::closeLibrary(Kernel::LibraryHandle handle) const
    {
        assert(handle);
        dlclose( (void *)handle);
    }
#endif
}
