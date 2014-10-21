#ifndef IMODULESYSTEM_H
#define IMODULESYSTEM_H

#include <string>
#include <vector>


#ifndef NO_TEST
    #include<iostream>
#endif

namespace LE
{
    namespace Module
    {
        class IModuleSystem
        {
        public :
            IModuleSystem(void) = default;
            virtual ~IModuleSystem(void) = default;
            IModuleSystem(const IModuleSystem &) = delete;
            IModuleSystem & operator=(const IModuleSystem &) = delete;

            virtual bool enable(const std::string & filename) = 0;
            virtual bool disable(const std::string & filename) = 0;

            virtual const std::vector<std::string> & enabledModules(void) const = 0;
            virtual const std::vector<std::string> & disabledModules(void) const = 0;

            virtual const std::string & enabledPathPrefix(void) const = 0;
            virtual const std::string & disabledPathPrefix(void) const = 0;

            virtual const std::string & enabledRelativePathPrefix(void) const = 0;
            virtual const std::string & disabledRelativePathPrefix(void) const = 0;

            virtual void executeChanges(void) = 0;
        };


        inline void IModuleSystem_test(IModuleSystem & s)
        {
            #ifndef NO_TEST
                std::cout << "Begin of module list" << std::endl
                          << "* enabled modules : " << std::endl;
                for( const auto & mod : s.enabledModules() )
                    std::cout << '\t' << mod << std::endl;
                std::cout << "* disabled modules : " << std::endl;
                for( const auto & mod : s.disabledModules() )
                    std::cout << '\t' << mod << std::endl;
                std::cout << "End of module list" << std::endl;
            #endif
        }
    }
}

#endif // IMODULESYSTEM_H
