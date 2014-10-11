#ifndef INFOMODULE_H
#define INFOMODULE_H

#include <cinttypes>
#include <string>
#include <vector>
#include <map>


#ifndef NO_TEST
    #include <LastEngine/IKernel.h>
    #include <iostream>
#endif

namespace LE
{
    struct InfoModule
    {
        struct File {
            const std::uint32_t version;
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
            const std::uint32_t version;

            struct {
                const std::string name;
                const std::uint32_t version;
            } api;
        };

        const std::vector<Module> modules;

    };

    class IKernel;

    inline void InfoModule_test(IKernel & k, const std::string & filename)
    {
        #ifndef NO_TEST
            IKernel::LibraryHandle handle = k.loadLibrary(filename);

            if( ! handle )
                throw std::system_error(EACCES, std::system_category(), filename);

            InfoModule * info = (InfoModule *)k.searchSymbol(handle, "info");

            if( ! info )
                throw std::system_error(ENOEXEC, std::system_category(), filename);

            std::cout << "=====" << filename << " info=====" << std::endl
                      << "Version : " << std::hex << info->file.version << std::dec << " (" << info->file.date << ")" << std::endl
                      << "Git repo : " << info->file.giturl << std::endl;
            for( const auto & author : info->file.authors )
                std::cout << "author : " << author.pseudo << " (" << author.email << ")" << std::endl;
            for( const auto & module : info->modules )
                std::cout << "module : " << module.name << " (v." << std::hex << module.version << std::dec << ") "
                             "implements " << module.api.name << " (v." << std::hex << module.api.version << ")" << std::endl;
            std::cout << "===== end of " << filename << " info=====" << std::endl;

            k.closeLibrary(handle);
        #endif
    }

}

#endif // INFOMODULE_H
