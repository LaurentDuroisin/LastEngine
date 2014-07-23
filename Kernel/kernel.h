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
        void changePreferences(std::string filename = "default");
        void restart(void);
    protected :

        void launchModuleManager(void);

    private :
        bool m_restart;
        /** @brief ModuleManager dynamics library without its extension. */
        std::string m_moduleManagerFile;
        /** @brief Preferences module dynamics library without its extension. */
        std::string m_preferencesFile;
    };
}

#endif // KERNEL_H
