#include "modulesystem.h"
#include <algorithm>
#include <stack>

#include <dirent.h>
#include <sys/stat.h>

namespace
{
    void read_dir( std::vector <std::string> & vector, const std::string & prefix, LE::IKernel & k)
    {
        std::stack<std::string> stack;

        stack.push("");

        while( ! stack.empty() )
        {
            std::string dirname = stack.top();
            stack.pop();

            dirent * de;
            DIR * dir = opendir( (prefix + dirname).c_str() );
            if( ! dir )
                throw std::system_error(errno, std::system_category(), "Opening directory " + prefix + dirname);

            errno = 0;

            struct stat filestat;
            while( de = readdir(dir) )
            {
                if( de->d_name != std::string(".") && de->d_name != std::string("..") )
                {
                    std::string filename = de->d_name;
                    stat( (prefix + dirname + filename).c_str(), &filestat);
                    if( S_ISDIR( filestat.st_mode) )
                        stack.push( dirname + filename + "/" );
                    else
                    {
                        std::size_t ext_pos = filename.size() - k.moduleExtention().size();
                        if( k.moduleExtention() == filename.substr(ext_pos) )
                        {
                            filename.erase(ext_pos);
                            vector.push_back( dirname + filename );
                        }
                    }
                }
            }
            if( errno )
                throw std::system_error(errno, std::system_category(), "Reading directory " + prefix + dirname);

            closedir(dir);
        }

        std::sort(vector.begin(), vector.end() );
    }
}

namespace LE
{
    namespace Module
    {
        ModuleSystem::ModuleSystem(IKernel & k)
            : m_kernel(k)
        {
            read_dir(m_disabled, disabledPathPrefix() , k);
            read_dir(m_enabled, enabledPathPrefix() , k);
        }

        bool ModuleSystem::enable(const std::string & filename)
        {
            if( ! std::binary_search(m_disabled.begin(), m_disabled.end(), filename) )
            {
                if( ! std::binary_search(m_enabled.begin(), m_enabled.end(), filename) )
                    return false;

                auto it = m_actions.find(filename);
                if( it != m_actions.end() )
                    m_actions.erase(it);
            }
            else
                m_actions[filename] = true;

            return true;
        }

        bool ModuleSystem::disable(const std::string & filename)
        {
            if( ! std::binary_search(m_enabled.begin(), m_enabled.end(), filename) )
            {
                if( ! std::binary_search(m_disabled.begin(), m_disabled.end(), filename) )
                    return false;

                auto it = m_actions.find(filename);
                if( it != m_actions.end() )
                    m_actions.erase(it);
            }
            else
                m_actions[filename] = false;

            return true;
        }

        void ModuleSystem::executeChanges(void)
        {
            for(const auto & pair : m_actions )
            {
                std::string orig = (pair.second ? disabledPathPrefix() : enabledPathPrefix() ) + pair.first + m_kernel.moduleExtention();
                std::string dest = (pair.second ? enabledPathPrefix() : disabledPathPrefix() ) + pair.first + m_kernel.moduleExtention();

                if( rename(orig.c_str(), dest.c_str() ) )
                    throw std::system_error(errno, std::system_category(), "Moving " + orig + " to " + dest);
            }
        }

        const std::string & ModuleSystem::enabledPathPrefix(void) const
        {
            static std::string path = m_kernel.pathPrefix() + enabledRelativePathPrefix();

            return path;
        }

        const std::string & ModuleSystem::disabledPathPrefix(void) const
        {
            static std::string path = m_kernel.pathPrefix() + disabledRelativePathPrefix();

            return path;
        }

        const std::string & ModuleSystem::enabledRelativePathPrefix(void) const
        {
            static std::string path = "Modules/enabled/";
            return path;
        }
        const std::string & ModuleSystem::disabledRelativePathPrefix(void) const
        {
            static std::string path = "Modules/disabled/";
            return path;
        }
    }
}
