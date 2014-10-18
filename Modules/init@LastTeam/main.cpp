#include <LastEngine/Visibility.h>
#include <LastEngine/InfoModule.h>
#include <LastEngine/IException.h>
#include <fstream>

#include "signalhandler.h"

namespace LE
{
    class IKernel;
}

void foo(void)
{
    throw LE::Exception<LE::IException::OTHER, 0>("test", THROW_ARGS);
}



EXPORT void init(LE::IKernel & k)
{
    // output redirections
    std::cerr << k.pathPrefix() + "log/fatalerror.log" << std::endl;
    std::ofstream fatalerrorfile(k.pathPrefix() + "log/fatalerror.log");
    std::cerr.rdbuf(fatalerrorfile.rdbuf());

    std::ofstream errorfile(k.pathPrefix() + "log/error.log");
    std::clog.rdbuf(errorfile.rdbuf());

    std::ofstream logfile(k.pathPrefix() + "log/output.log");
    std::cout.rdbuf(logfile.rdbuf());

    // signal handler
    LE::SignalHandler shandler;

    try {
        foo();
    } catch( LE::IException & ie )
    {
        std::cerr << ie << std::endl;
        throw;
    }
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
