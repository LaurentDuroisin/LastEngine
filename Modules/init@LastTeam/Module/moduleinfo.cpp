#include "moduleinfo.h"

namespace LE
{
    namespace Module
    {
        ModuleInfo::ModuleInfo(IKernel & k)
            : m_kernel(k)
        {

        }

        Info::File ModuleInfo::loadInfo_intern(const std::string & filename)
        {
            IKernel::LibraryHandle handle = m_kernel.loadLibrary(filename );
            if( ! handle )
                throw std::system_error(EACCES, std::system_category(), filename + m_kernel.moduleExtention() + ", " + m_kernel.libraryError() );

            IKernel::LibrarySymbol symb = m_kernel.searchSymbol(handle, "info");
            if( ! symb )
                throw std::system_error(ENOEXEC, std::system_category(), filename + m_kernel.moduleExtention() + ", " + m_kernel.libraryError() );

            Info::File info = *(Info::File *) symb;

            m_kernel.closeLibrary(handle);

            return info;
        }

        Info::File & ModuleInfo::loadInfo(const std::string & filename)
        {
            auto it = m_infos.find(filename);

            if( it == m_infos.end() )
            {
                m_infos.insert( std::pair<std::string, Info::File>(filename,
                                                                   loadInfo_intern(filename) )  );
            }

            return it->second;
        }

        void ModuleInfo::loadInfo(const std::vector<std::string> & filenames, const std::string & prefix)
        {
            for(const auto & filename : filenames)
                m_infos.insert( std::pair<std::string, Info::File>(filename,
                                                                   loadInfo_intern(prefix + filename) )  );
        }
    }
}
