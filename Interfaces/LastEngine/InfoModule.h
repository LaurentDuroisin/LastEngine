#ifndef INFOMODULE_H
#define INFOMODULE_H

#include <cinttypes>
#include <string>
#include <vector>
#include <map>
#include <initializer_list>
#include <sstream>

#ifndef NO_TEST
    #include <LastEngine/IKernel.h>
    #include <iostream>
#endif

namespace LE
{
    typedef std::uint32_t Version;
    inline Version version(std::uint8_t major, std::uint8_t minor, std::uint8_t cl, std::uint8_t build);
    inline std::string versionToStr(Version v, std::size_t precision = sizeof(Version) );

    struct InfoModule
    {
        struct File {
            const Version version;
            const std::string date;
            const std::string giturl;

            struct Author {
                const std::string pseudo;
                const std::string email;
            };

            std::vector<Author> authors;

        } file;

        struct Module {
            const std::string name;
            const Version version;

            struct {
                const std::string name;
                const Version version;
            } api;
        };
        const std::vector<Module> modules;
    };


    class IKernel;
    inline void InfoModule_test(IKernel & k, const std::string & filename);

    namespace Info
    {
        InfoModule::File::Author author(std::string && pseudo, std::string && email)
        {
            return InfoModule::File::Author{std::move(pseudo), std::move(email)};
        }

        std::vector<InfoModule::File::Author> authors(std::initializer_list<InfoModule::File::Author> liste)
        {
            return std::vector<InfoModule::File::Author>(liste);
        }

        InfoModule::File file(Version version, std::string date, const std::string giturl, std::vector<InfoModule::File::Author> && authors)
        {
            return InfoModule::File{version, std::move(date), std::move(giturl), std::move(authors)};
        }

        InfoModule::Module module(std::string && name, Version version, std::string && api_name, Version api_version)
        {
            return InfoModule::Module{std::move(name), version, std::move(api_name), api_version};
        }

        std::vector<InfoModule::Module> modules(std::initializer_list<InfoModule::Module> liste)
        {
            return std::vector<InfoModule::Module>(liste);
        }

    }

    /*==========
     *==== Code
     *==========
     */

    void InfoModule_test(IKernel & k, const std::string & filename)
    {
        #ifndef NO_TEST
            IKernel::LibraryHandle handle = k.loadLibrary(filename);

            if( ! handle )
                throw std::system_error(EACCES, std::system_category(), filename);

            InfoModule * info = (InfoModule *)k.searchSymbol(handle, "info");

            if( ! info )
                throw std::system_error(ENOEXEC, std::system_category(), filename);

            std::cout << "=====" << filename << " info=====" << std::endl
                      << "Version : " << versionToStr(info->file.version) << " (" << info->file.date << ")" << std::endl
                      << "Git repo : " << info->file.giturl << std::endl;
            for( const auto & author : info->file.authors )
                std::cout << "author : " << author.pseudo << " (" << author.email << ")" << std::endl;
            for( const auto & module : info->modules )
                std::cout << "module : " << module.name << " (v. " << versionToStr(module.version) << ") "
                             "implements " << module.api.name << " (v. " << versionToStr(module.api.version, 2) << ")" << std::endl;
            std::cout << "===== end of " << filename << " info=====" << std::endl;

            k.closeLibrary(handle);
        #endif
    }


    Version version(std::uint8_t major, std::uint8_t minor, std::uint8_t cl, std::uint8_t build)
    {
        return (major << 24) | (minor << 16) | (cl << 8)| build;
    }

    std::string versionToStr(Version v, std::size_t precision)
    {
        std::stringstream result;

        for(int i = 0; i < precision ; ++i )
        {
            if( i ) result << '.';

            int octet = ( v >> (8*(sizeof(v) - 1) ) );
            result << octet;

            v <<= 8;
        }

        return result.str();
    }
}

#endif // INFOMODULE_H
