#ifndef IMODULEINFO_H
#define IMODULEINFO_H

#include <string>

namespace LE
{
    namespace Info
    {
        class File;
    }

    namespace Module
    {
        class IModuleInfo
        {
            IModuleInfo(void) = default;
            IModuleInfo(const IModuleInfo &) = delete;
            IModuleInfo & operator=(const IModuleInfo &) = delete;

            virtual Info::File & loadInfo(const std::string & filename) = 0;
            virtual Info::File & loadInfo(std::string && filename) = 0;
        };
    }
}

#endif // IMODULEINFO_H
