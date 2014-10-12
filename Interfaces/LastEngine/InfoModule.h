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
    class IKernel;

    namespace Info
    {
        class Version final
        {
            typedef std::uint32_t M_Version;
        public :
            Version(std::uint8_t major, std::uint8_t minor, std::uint8_t cl, std::uint8_t build);
            operator M_Version() const;
            std::string toString(std::size_t precision = sizeof(M_Version) ) const;
        private :
            std::uint8_t m_elements[sizeof(M_Version)];
        };


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
                          << "Version : " << info->version.toString() << " (" << info->date << ")" << std::endl
                          << "Git repo : " << info->giturl << std::endl;
                for( const auto & author : info->authors )
                    std::cout << "author : " << author.pseudo << " (" << author.email << ")" << std::endl;
                for( const auto & module : info->modules )
                    std::cout << "module : " << module.name << " (v. " << module.version.toString() << ") "
                                 "implements " << module.api.name << " (v. " << module.api.version.toString(2) << ")" << std::endl;
                std::cout << "===== end of " << filename << " info=====" << std::endl;

                k.closeLibrary(handle);
            #endif
        }

        Version::Version(std::uint8_t major, std::uint8_t minor, std::uint8_t cl, std::uint8_t build)
            : m_elements{major, minor, cl, build}
        {
        }

        Version::operator Version::M_Version() const
        {
            M_Version result = 0;
            for(std::size_t i = 0; i < sizeof(M_Version); ++i)
            {
                result <<= 8;
                result |= m_elements[i];
            }

            return result;
        }

        std::string Version::toString(std::size_t precision) const
        {
            std::stringstream result;

            for(int i = 0; i < precision ; ++i )
            {
                if( i ) result << '.';

                result << (int) m_elements[i];
            }

            return result.str();
        }
    }
}

#endif // INFOMODULE_H
