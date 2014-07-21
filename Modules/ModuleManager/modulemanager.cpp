#include "modulemanager.h"

#include <iostream>

namespace NLP
{
    ModuleManager::ModuleManager()
    {
    }

    void ModuleManager::run(void)
    {
        std::cerr << "it work !" << std::endl;
    }
}

void run(void * kernel)
{
    NLP::VirtualKernel * vkernel = (NLP::VirtualKernel *) kernel;
    NLP::ModuleManager module;
    module.run();
    vkernel->restart();
}
