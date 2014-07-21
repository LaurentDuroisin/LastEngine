#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H


#include "../../VirtualModuleManager.h"

namespace NLP
{

    class ModuleManager : public VirtualModuleManager
    {
    public:
        ModuleManager();

        /** @brief Load others modules */
        void run(void);
    };
}

#endif // MODULEMANAGER_H
