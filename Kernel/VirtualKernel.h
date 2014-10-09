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
        /** @brief Dynamic library handle.
         *  @see loadLibrary
         */
        typedef void * LibraryHandle;

        /** @brief Dynamic library's symbol
         *  @see loadLibrary()
         *  @see searchSymbol()
         */
        typedef void * LibrarySymbol;

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

        /** @brief Open a dynamic library.
         *  @param filename : dynamic library's filename without it's extension (.so for Linux, .dll for Windows)
         *  @return dynamic library handle, false/nullptr if an error occurs.
         *  @see closeLibrary()
         */
        virtual LibraryHandle loadLibrary(const std::string & filename) const = 0;

        /** @brief Give the last error when loading
         *  @return last error
         */
        virtual std::string libraryError(void) const = 0;

        /** @brief Search a symbol in a dynamic library.
         *  @param handle : dynamic library handle
         *  @param symbolName : symbol name to research in the dynamic library
         *  @return symbole searched
         *  @see loadLibrary()
         */
        virtual LibrarySymbol searchSymbol(LibraryHandle handle, const std::string & symbolName) const = 0;

        /** @brief Close a dynamic library opened.
         *  @param handle : dynamic library opened to close.
         */
        virtual void closeLibrary(LibraryHandle) const = 0;

        /** @brief Return the dynamic library's extension used.
         *  @return dynamic library's extension used.
         */
        virtual const std::string & libraryExtension(void) const = 0;

    protected :
        /** @brief Launch ModuleManager */
        virtual void launchModuleManager(void) = 0;
    };
}

#endif // VIRTUALKERNEL_H
