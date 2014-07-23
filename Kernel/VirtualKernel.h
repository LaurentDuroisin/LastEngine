#ifndef VIRTUALKERNEL_H
#define VIRTUALKERNEL_H

#include <string>

namespace NLP
{
    /** @brief His only aim is to launch ModuleManager.
     */
    class VirtualKernel
    {
    public :
        VirtualKernel(void){}
        VirtualKernel(const VirtualKernel &) = delete;
        VirtualKernel & operator=(const VirtualKernel &);
        virtual ~VirtualKernel(void){}

        /** @brief Launch ModuleManager as long as it say it want to be restarted */
        virtual void run(void) = 0;

        /** @brief Change the ModuleManager to launch.
         *  @param filename : ModuleManager dynamics library without its extension.
         */
        virtual void changeModuleManager(std::string filename = "libModuleManager") = 0;

        /** @brief Change the Preferences module to launch.
         *  @param filename : Preferences module dynamics library without its extension.
         */
        virtual void changePreferences(std::string filename = "default") = 0;

        /** @brief Restart ModuleManager when it's finish. */
        virtual void restart(void) = 0;
    protected :
        /** @brief Launch ModuleManager */
        virtual void launchModuleManager(void) = 0;
    };
}

#endif // VIRTUALKERNEL_H
