#ifndef MODULEINFO_H
#define MODULEINFO_H

#include <LastEngine/Module/IModuleInfo.h>
#include <LastEngine/Module/InfoFile.h>

namespace LE
{
    namespace Module
    {
        class ModuleInfo : public IModuleInfo
        {
        public:
            ModuleInfo(IKernel & k);
            virtual Info::File & loadInfo(const std::string & filename);
            virtual void loadInfo(const std::vector<std::string> & filenames, const std::string & prefix);
        private :
            Info::File loadInfo_intern(const std::string & filename);


            IKernel & m_kernel;
            std::map<std::string, Info::File> m_infos;
        };
    }
}


#endif // MODULEINFO_H
