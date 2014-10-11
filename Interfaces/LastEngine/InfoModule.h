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

    namespace Info
    {
        typedef std::uint32_t Version;
        inline Version version(std::uint8_t major, std::uint8_t minor, std::uint8_t cl, std::uint8_t build);
        inline std::string versionToStr(Version v, std::size_t precision = sizeof(Version) );



        struct Author {
            const std::string pseudo;
            const std::string email;
        };

        typedef std::vector<Author> Authors;


        struct API {
            const std::string name;
            const Info::Version version;
        };

        struct Module {
            const std::string name;
            const Info::Version version;

            API api;
        };

        typedef const std::vector<Module> Modules;

        struct File {
            const Info::Version version;
            const std::string date;
            const std::string giturl;
            Info::Authors authors;
            Info::Modules modules;

        };

    }


    class IKernel;

    namespace Info
    {
        inline void InfoModule_test(IKernel & k, const std::string & filename);

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

                File * info = (File *)k.searchSymbol(handle, "info");

                if( ! info )
                    throw std::system_error(ENOEXEC, std::system_category(), filename);

                std::cout << "=====" << filename << " info=====" << std::endl
                          << "Version : " << Info::versionToStr(info->version) << " (" << info->date << ")" << std::endl
                          << "Git repo : " << info->giturl << std::endl;
                for( const auto & author : info->authors )
                    std::cout << "author : " << author.pseudo << " (" << author.email << ")" << std::endl;
                for( const auto & module : info->modules )
                    std::cout << "module : " << module.name << " (v. " << Info::versionToStr(module.version) << ") "
                                 "implements " << module.api.name << " (v. " << Info::versionToStr(module.api.version, 2) << ")" << std::endl;
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
}

#endif // INFOMODULE_H
