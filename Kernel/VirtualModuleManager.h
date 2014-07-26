#ifndef VIRTUALMODULEMANAGER_H
#define VIRTUALMODULEMANAGER_H

#include "VirtualKernel.h"

typedef NLP::VirtualKernel VirtualKernel;

extern "C"
{
    /** @brief Call by the Kernel, launch ModuleManager */
    __declspec(dllexport) void run(NLP::VirtualKernel &ptr);
}

namespace NLP
{
    typedef void (*MainFct)(VirtualKernel &);

    /** @brief Load and unload others modules */
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
