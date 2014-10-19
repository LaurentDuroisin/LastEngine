#ifndef IMODULEINFO_H
#define IMODULEINFO_H

#include <string>
#include <vector>

#ifndef NO_TEST
    #include "InfoFile.h"
#endif

namespace LE
{

    namespace Module
    {
        namespace Info
        {
            class File;
        }

        class IModuleInfo
        {
        public :
            IModuleInfo(void) = default;
            IModuleInfo(const IModuleInfo &) = delete;
            IModuleInfo & operator=(const IModuleInfo &) = delete;

            virtual Info::File & loadInfo(const std::string & filename) = 0;
            virtual void loadInfo(const std::vector<std::string> & filename, const std::string & prefix) = 0;
        };


        inline void ModuleInfo_test(IModuleInfo & mi, const std::vector<std::string> &);

        /*==========
         *==== Code
         *==========
         */

        void ModuleInfo_test(IModuleInfo & mi, const std::vector<std::string> & v)
        {
            #ifndef NO_TEST
                for(const auto & filename : v)
                {
                    std::cout << "=====" << filename << " info=====" << std::endl;
                    Info::InfoFile_test( mi.loadInfo( filename ) );
                    std::cout << "===== end of " << filename << " info=====" << std::endl;
                }
            #endif
        }
    }
}

#endif // IMODULEINFO_H
