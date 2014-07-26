#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include "IModuleManager.h"

#include "../../Kernel/VirtualModuleManager.h"

namespace NLP
{

    class ModuleManager : public VirtualModuleManager, public IModuleManager
    {
    public:

        ModuleManager(VirtualKernel & kernel);
        virtual ~ModuleManager(void);

        /** @brief Load others modules */
        void run(void);

        InfoModule load(const InfoModule &info);
        InfoModule searchInfo(const std::string & file, const std::string & symbol);
        SymbolList searchSymbol(const std::string & file);

    private :
        InfoModule load(const std::string & file, const std::string & symbol,
                        const InfoModule * infoPtr = nullptr);

        /** @brief Kernel used */
        VirtualKernel & m_kernel;

        ModuleList m_loadedModules;
    };
}

#endif // MODULEMANAGER_H
