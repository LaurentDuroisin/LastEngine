#ifndef IMODULEMANAGER_H
#define IMODULEMANAGER_H

#include <unordered_map>
#include <vector>
#include <string>

#include "InfoModule.h"

namespace NLP
{
    inline const InfoModule & infoModuleManager(void)
    {
        const static InfoModule infoModule("Neckara",
                                           "https://github.com/LastProject/LastEngine/tree/master/Modules/ModuleManager",
                                           "ModuleManager",
                                           "libModuleManager",
                                           0,
                                           1406288847,
                                           "",
                                           nullptr,
                                           nullptr,
                                           "");
        return infoModule;
    }

    class IModuleManager {
    public :
        typedef std::unordered_map<std::string, InfoModule> ModuleList;
        typedef std::vector<std::string> SymbolList;
        typedef InfoModule * (*LoadFct)(InfoModule *, IModuleManager &);
        typedef const char ** (*SymbolListFct)(void);

        virtual InfoModule load(const InfoModule &) = 0;
        virtual InfoModule searchInfo(const std::string & file, const std::string & symbol) = 0;
        virtual SymbolList searchSymbol(const std::string & file) = 0;

    };
}

#endif // IMODULEMANAGER_H
