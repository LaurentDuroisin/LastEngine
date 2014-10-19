#include "modulesystem.h"
#include <algorithm>
#include <stack>

#include <dirent.h>

namespace
{
    void read_dir( std::vector <std::string> & vector, std::string && path, LE::IKernel & k)
    {
        std::string prefix = k.pathPrefix() + path;
        std::stack<std::string> stack;

        stack.push("");

        while( ! stack.empty() )
        {
            std::string dirname = stack.top();
            stack.pop();

            std::cout << dirname << std::endl;

            dirent * de;
            DIR * dir = opendir( (prefix + dirname).c_str() );
            if( ! dir )
                throw std::system_error(errno, std::system_category(), "Opening directory " + prefix + dirname);

            errno = 0;

            while( de = readdir(dir) )
            {
                if( de->d_name != std::string(".") && de->d_name != std::string("..") )
                {
                    std::string filename = de->d_name;
                    std::size_t ext_pos = filename.size() - k.moduleExtention().size();
                    if( k.moduleExtention() == filename.substr(ext_pos) )
                    {
                        filename.erase(ext_pos);
                        vector.push_back( dirname + filename );
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
            read_dir(m_disabled, "Modules/disabled", k);
            read_dir(m_enabled, "Modules/enabled", k);
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
                std::string orig = m_kernel.pathPrefix() + (pair.second ? "Modules/disabled/" : "Modules/enabled/") + pair.first + m_kernel.moduleExtention();
                std::string dest = m_kernel.pathPrefix() + (pair.second ? "Modules/enabled/" : "Modules/disabled/") + pair.first + m_kernel.moduleExtention();

                if( rename(orig.c_str(), dest.c_str() ) )
                    throw std::system_error(errno, std::system_category(), "Moving " + orig + " to " + dest);
            }
        }
    }
}
