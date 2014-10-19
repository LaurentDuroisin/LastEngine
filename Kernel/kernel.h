#ifndef KERNEL_H
#define KERNEL_H

#include <LastEngine/IKernel.h>

namespace LE
{
    class Kernel : public IKernel
    {
    public:

        void pathPrefixe(const std::string &);
        void pathPrefixe(const std::string &&);
        const std::string & pathPrefix(void) const;
        const std::string & moduleExtention(void) const;

        void run(void);
        void restart(bool restart, const std::string & new_init_file);
        void restart(bool restart, const std::string && new_init_file);

        LibraryHandle loadLibrary(const std::string & filename) const;

        std::string libraryError(void) const;

        LibrarySymbol searchSymbol(LibraryHandle handle, const std::string & symbolName) const;

        void closeLibrary(LibraryHandle handle) const;

    protected :

        void launchInitPhase(void);

    private :
        bool m_restart;

        const static std::string m_moduleExtension;

        const static std::string m_initFilename;

        std::string m_new_init_file;
        std::string m_path_prefixe = "./";
    };
}

#endif // KERNEL_H
