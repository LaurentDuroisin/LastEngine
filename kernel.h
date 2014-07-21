#ifndef KERNEL_H
#define KERNEL_H

#include "VirtualKernel.h"

namespace NLP
{
    class Kernel : public VirtualKernel
    {
    public:
        Kernel();

        void run(void);
        void changeModuleManager(std::string filename = "libModuleManager");
        void changeModulePreferences(std::string filename = "default");
        void restart(void);
    protected :

        void launchModuleManager(void);

    private :
        bool m_restart;
        std::string m_moduleManagerFile;
        std::string m_modulePreferencesFile;
    };
}

#endif // KERNEL_H
