#ifndef INFOFILE_H
#define INFOFILE_H

#include <cinttypes>
#include <string>
#include <vector>
#include <map>
#include <initializer_list>
#include <sstream>
#include <cassert>

#ifndef NO_TEST
    #include <LastEngine/IKernel.h>
    #include <iostream>
#endif

namespace LE
{
    class IKernel;

    namespace Module
    {
        namespace Info
        {

            class Version final
            {
                typedef std::uint32_t M_Version;
            public :
                inline Version(std::uint8_t major, std::uint8_t minor, std::uint8_t cl, std::uint8_t build);
                inline operator M_Version() const;
                inline std::string toString(std::size_t precision = sizeof(M_Version) ) const;
            private :
                std::uint8_t m_elements[sizeof(M_Version)];
            };


            struct Author final {

                const std::string pseudo;
                const std::string email;

                inline Author(std::string & pseudo, std::string & email);
                inline Author(std::string && pseudo, std::string && email);
                inline Author(Author &&);
                inline Author(const Author &);
            };


            typedef std::vector<Author> Authors;


            struct API final {

                const std::string name;
                const Version version;


                inline API(const std::string & name, const Version & version);
                inline API(std::string && name, Version && version);
                inline API(const API &);
                inline API(API &&);
            };


            struct Module final {

                const std::string name;
                const Info::Version version;
                API api;

                inline Module(const std::string & name, const Version & version, const API & api);
                inline Module(std::string && name, Version && version, API && api);
                inline Module(Module &&);
                inline Module(const Module &);
            };


            typedef const std::vector<Module> Modules;


            struct Date final {

                inline Date(std::uint16_t year, std::uint8_t month, std::uint8_t day);
                inline Date(const Date &);
                inline Date(Date &&);

                inline operator std::string() const;
            private :
                std::string m_date;
            };

            inline std::ostream & operator<<(std::ostream &, const Date &);

            struct File final {

                const Version version;
                const Date date;
                const std::string giturl;
                Authors authors;
                Modules modules;

                inline File(const Version & version, const Date &date, const std::string & giturl, const Authors & authors, const Modules & modules);
                inline File(Version && version, Date && date, std::string && giturl, Authors && authors, Modules && modules);
                inline File(const File &);
                inline File(File &&);

            };

            inline void InfoFile_test(IKernel & k, const std::string & filename);
            inline void InfoFile_test(const File &);

            /*==========
             *==== Code
             *==========
             */

            void InfoFile_test(const File & info)
            {
                #ifndef NO_TEST
                    std::cout << "Version : " << info.version.toString() << " (" << info.date << ")" << std::endl
                              << "Git repo : " << info.giturl << std::endl;
                    for( const auto & author : info.authors )
                        std::cout << "author : " << author.pseudo << " (" << author.email << ")" << std::endl;
                    for( const auto & module : info.modules )
                        std::cout << "module : " << module.name << " (v. " << module.version.toString() << ") "
                                     "implements " << module.api.name << " (v. " << module.api.version.toString(2) << ")" << std::endl;
                #endif
            }

            void InfoFile_test(IKernel & k, const std::string & filename)
            {
                #ifndef NO_TEST
                    IKernel::LibraryHandle handle = k.loadLibrary(filename);

                    if( ! handle )
                        throw std::system_error(EACCES, std::system_category(), filename + ", " + k.libraryError() );

                    File * info = (File *)k.searchSymbol(handle, "info");

                    if( ! info )
                        throw std::system_error(ENOEXEC, std::system_category(), filename + ", " + k.libraryError() );

                    std::cout << "=====" << filename << " info=====" << std::endl;
                    InfoFile_test(*info);
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
                assert(precision <= sizeof(M_Version));

                std::stringstream result;

                for(int i = 0; i < precision ; ++i )
                {
                    if( i ) result << '.';

                    result << (int) m_elements[i];
                }

                return result.str();
            }

            Author::Author(std::string & pseudo, std::string & email)
                : pseudo(pseudo), email(email)
            {

            }

            Author::Author(std::string && pseudo, std::string && email)
                : pseudo(std::move(pseudo) ), email( std::move(email) )
            {

            }

            Author::Author(const Author & o)
                : pseudo(o.pseudo), email(o.email)
            {

            }

            Author::Author(Author && o)
                : pseudo(std::move(pseudo) ), email( std::move(email) )
            {

            }


            API::API(const std::string & name, const Version & version)
                : name(name), version(version)
            {

            }

            API::API(std::string && name, Version && version)
                : name(std::move(name)), version(std::move(version))
            {

            }

            API::API(const API & o)
                : name(o.name), version(o.version)
            {

            }

            API::API(API && o)
                : name(std::move(o.name)), version(std::move(o.version))
            {

            }


            Module::Module(const std::string & name, const Version & version, const API & api)
                : name(name), version(version), api(api)
            {

            }

            Module::Module(std::string && name, Version && version, API && api)
                : name(std::move(name)), version(std::move(version)), api(std::move(api))
            {

            }

            Module::Module(const Module & o)
                : name(o.name), version(o.version), api(o.api)
            {

            }

            Module::Module(Module && o)
                : name(std::move(o.name)), version(std::move(o.version)), api(std::move(o.api))
            {

            }

            File::File(const Version & version, const Date & date, const std::string & giturl, const Authors & authors, const Modules & modules)
                : version(version), date(date), giturl(giturl), authors(authors), modules(modules)
            {

            }

            File::File(Version && version, Date &&date, std::string &&giturl, Authors && authors, Modules && modules)
                : version(std::move(version)), date(std::move(date)), giturl(std::move(giturl)), authors(std::move(authors)), modules(std::move(modules))
            {

            }

            File::File(const File & o)
                : version(o.version), date(o.date), giturl(o.giturl), authors(o.authors), modules(o.modules)
            {

            }

            File::File(File && o)
                : version(std::move(o.version)), date(std::move(o.date)), giturl(std::move(o.giturl)), authors(std::move(o.authors)), modules(std::move(o.modules))
            {

            }


            Date::Date(std::uint16_t year, std::uint8_t month, std::uint8_t day)
            {
                assert(year > 2013);
                assert(month && month <= 12);
                assert(day && day <= 31);

                std::stringstream ss;
                ss << year << "/" << (int)month << "/" << (int)day;
                m_date = ss.str();
            }

            Date::Date(const Date & o)
                : m_date(o.m_date)
            {

            }

            Date::Date(Date && o)
                : m_date(std::move(o.m_date) )
            {

            }

            Date::operator std::string() const
            {
                return m_date;
            }

            std::ostream & operator<<(std::ostream & stream, const Date & d)
            {
                return stream << (std::string)d;
            }
        }
    }
}

#endif // INFOFILE_H
