#ifndef INFOMODULE_H
#define INFOMODULE_H

#include <string>
#include <functional>

#ifdef _WIN32
    #define EXPORT extern "C" __declspec(dllexport)
#else
    #define EXPORT extern "C" __attribute__((visibility("default")))
#endif

#include <iostream>

namespace NLP
{
    typedef void * InterfaceModule;

    class InfoModule final {
    public :
        typedef uint64_t VersionDate;
        typedef uint64_t Version;

        InfoModule(void)
            : m_versionDate(0),
              m_interface(nullptr),
              m_handle(nullptr)
        {

        }


        InfoModule(const std::string & author,          const std::string & urlModule,
                   const std::string & interfaceName,   const std::string & moduleName,
                   const Version & moduleVersion,       const VersionDate & versionDate,
                   const std::string & description,
                   InterfaceModule interface,
                   const std::string & loadFunctionName)
            : m_author(author),
              m_urlModule(urlModule),
              m_interfaceName(interfaceName),
              m_moduleName(moduleName),
              m_moduleVersion(moduleVersion),
              m_versionDate(versionDate),
              m_description(description),
              m_interface(interface),
              m_handle(nullptr),
              m_loadFunctionName(loadFunctionName)
        {

        }

        const std::string & author(void) const{ return m_author; }
        const std::string & urlModule(void) const{ return m_urlModule; }
        const std::string & interfaceName(void) const{ return m_interfaceName; }
        const std::string & moduleName(void) const{ return m_moduleName; }
        const Version & version(void) const { return m_moduleVersion; }
        const VersionDate & versionDate(void) const { return m_versionDate; }
        const std::string & description(void) const { return m_description; }
        InterfaceModule interface(void)const { return m_interface; }
        void * handle(void) const{ return m_handle; }
        const std::string & loadFunctionName(void) const { return m_loadFunctionName; }

        void changeHandle(void * handle){ m_handle = handle; }
        void changeInterface(InterfaceModule interface){ m_interface = interface; }

        bool operator!(void) const
        {
               return ! (bool)*this;
        }

        operator bool (void) const
        {
            if ( m_author.empty() )
                return false;
            if( m_urlModule.empty() )
                return false;
            if( m_interfaceName.empty() )
                return false;
            if( m_moduleName.empty() )
                return false;
            if( m_versionDate == 0)
                return false;
            if( ! m_interface)
                return false;
            if( ! m_handle )
                return false;
            if( m_loadFunctionName.empty() )
                return false;
            return true;
        }

    private :
        std::string m_author;
        std::string m_urlModule;
        std::string m_interfaceName;
        std::string m_moduleName;
        Version m_moduleVersion;
        VersionDate m_versionDate;
        std::string m_description;
        InterfaceModule m_interface;
        void * m_handle;
        std::string m_loadFunctionName;

    };
}

#endif // INFOMODULE_H
