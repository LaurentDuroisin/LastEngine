#ifndef VIRTUALKERNEL_H
#define VIRTUALKERNEL_H

#include <string>

namespace NLP
{
    class VirtualKernel
    {
    public :
        VirtualKernel(void){}
        VirtualKernel(const VirtualKernel &) = delete;
        VirtualKernel & operator=(const VirtualKernel &);
        virtual ~VirtualKernel(void){}
        virtual void run(void) = 0;
        virtual void changeModuleManager(std::string filename = "libModuleManager") = 0;
        virtual void changeModulePreferences(std::string filename = "default") = 0;
        virtual void restart(void) = 0;
    protected :

        virtual void launchModuleManager(void) = 0;
    };
}

#endif // VIRTUALKERNEL_H
