#ifndef IKERNEL_H
#define IKERNEL_H

#include <string>
#include <system_error>

namespace LE
{
    /** @brief Provide symbol loading services to the module manager. */
    class IKernel
    {
    public :
        typedef void (*InitFunction)(IKernel & k);

        /** @brief Dynamic library handle.
         *  @see loadLibrary
         */
        typedef void * LibraryHandle;

        /** @brief Dynamic library's symbol
         *  @see loadLibrary()
         *  @see searchSymbol()
         */
        typedef void * LibrarySymbol;

        IKernel(void){} // required.
        IKernel(const IKernel &) = delete;
        IKernel & operator=(const IKernel &) = delete;

        /** @brief Ask for replace the current init.lpm file and restart, it will be executed when the current init.lpm will stop. */
        virtual void restart(bool restart, const std::string & new_init_file) = 0;
        virtual void restart(bool restart = true, const std::string && new_init_file = "") = 0;

        /** @brief Open a dynamic library.
         *  @param filename : dynamic library's filename without it's extension.
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
    };
}

#endif // IKERNEL_H
