#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H


#include "../../VirtualModuleManager.h"

extern "C"
{
    __declspec(dllexport)
    void run(void *);
}

namespace NLP
{

    class ModuleManager : public VirtualModuleManager
    {
    public:
        ModuleManager();

        void run(void);
    };
}

#endif // MODULEMANAGER_H
