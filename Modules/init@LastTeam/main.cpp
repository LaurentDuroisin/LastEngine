#include <LastEngine/Visibility.h>
#include <LastEngine/InfoModule.h>
#include <LastEngine/IException.h>
#include <fstream>

#include "signalhandler.h"
#include "Module/modulesystem.h"

namespace LE
{
    class IKernel;
}


EXPORT void init(LE::IKernel & k)
{
    // output redirections
    std::streambuf * bufs[] = { std::cerr.rdbuf(), std::clog.rdbuf(), std::cout.rdbuf() };

    std::ofstream fatalerrorfile(k.pathPrefix() + "log/fatalerror.log");
    std::cerr.rdbuf(fatalerrorfile.rdbuf());

    std::ofstream errorfile(k.pathPrefix() + "log/error.log");
    std::clog.rdbuf(errorfile.rdbuf());

    std::ofstream logfile(k.pathPrefix() + "log/output.log");
    std::cout.rdbuf(logfile.rdbuf());

    // signal handler
    LE::SignalHandler shandler;

    try {
        LE::Module::ModuleSystem ms(k);
        ms.disable("toto");
        LE::Module::IModuleSystem_test(ms);
        ms.executeChanges();
    } catch( LE::IException & ie )
    {
        std::cerr << ie << std::endl;
    } catch( std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }

    std::cerr.rdbuf(bufs[0]);
    std::clog.rdbuf(bufs[1]);
    std::cout.rdbuf(bufs[2]);
}


EXPORT LE::Info::File info;

using namespace LE::Info;

File info(
    Version(0,0,1,0),
    Date(2014,10,12),
    "https://github.com/LastProject/LastEngine/tree/master/Modules/init%40LastTeam",
    Authors{
        Author("Neckara", "Neckara.LastDungeon@gmail.com")
    },
    Modules{
        Module("name", Version(0,0,0,1), API("api", Version(0,0,0,1) ) ),
        Module("name", Version(0,0,0,1), API("api", Version(0,0,0,1) ) )
    }
);
