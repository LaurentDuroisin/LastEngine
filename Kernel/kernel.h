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

        LibraryHandle loadLibrary(const std::string & filename) const;

        std::string libraryError(void) const;

        LibrarySymbol searchSymbol(LibraryHandle handle, const std::string & symbolName) const;

        void closeLibrary(LibraryHandle handle) const;

        const std::string & libraryExtension(void) const { return m_libraryExtension; }

        void printOk(void) const;
    protected :

        void launchModuleManager(void);

    private :
        bool m_restart;
        /** @brief ModuleManager dynamics library without its extension. */
        std::string m_moduleManagerFile;
        /** @brief Preferences module dynamics library without its extension. */
        std::string m_preferencesFile;

        /** @brief Dynamic library's extension used. */
        const static std::string m_libraryExtension;
    };
}

#endif // KERNEL_H
