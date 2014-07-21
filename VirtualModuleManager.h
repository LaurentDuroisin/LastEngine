#ifndef VIRTUALMODULEMANAGER_H
#define VIRTUALMODULEMANAGER_H

#include "VirtualKernel.h"

extern "C"
{
    __declspec(dllexport) void run(void *);
}

namespace NLP
{
    typedef void (*MainFct)(VirtualKernel *);

    class VirtualModuleManager
    {
    public :
        VirtualModuleManager(void){}
        VirtualModuleManager(const VirtualModuleManager &) = delete;
        VirtualModuleManager & operator=(const VirtualModuleManager &) = delete;
        virtual ~VirtualModuleManager(void){}
    };
}

#endif // VIRTUALMODULEMANAGER_H
