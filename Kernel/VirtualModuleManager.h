#ifndef VIRTUALMODULEMANAGER_H
#define VIRTUALMODULEMANAGER_H

#include "VirtualKernel.h"

#ifdef _WIN32
    #define EXPORT extern "C" __declspec(dllexport)
#else
    #define EXPORT extern "C" __attribute__((visibility("default")))
#endif

/** @brief Call by the Kernel, launch ModuleManager */
EXPORT void run(NLP::VirtualKernel &ptr);


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
