#ifndef MODULESYSTEM_H
#define MODULESYSTEM_H

#include<LastEngine/Module/IModuleSystem.h>
#include<LastEngine/IKernel.h>

#include <map>

namespace LE
{
    namespace Module
    {
        class ModuleSystem : public IModuleSystem
        {
        public :
            ModuleSystem(IKernel &);

            virtual bool enable(const std::string & filename);
            virtual bool disable(const std::string & filename);


            virtual const std::vector<std::string> & enabledModules(void) const{ return m_enabled; }
            virtual const std::vector<std::string> & disabledModules(void) const{ return m_disabled; }

            virtual void executeChanges(void);
        private :
            IKernel & m_kernel;

            std::vector<std::string> m_enabled; // must be sorted
            std::vector<std::string> m_disabled;

            std::map<std::string, bool> m_actions;
        };
    }
}

#endif // MODULESYSTEM_H
