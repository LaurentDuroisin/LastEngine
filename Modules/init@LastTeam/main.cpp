#include <LastEngine/Visibility.h>
#include <LastEngine/InfoModule.h>
#include <iostream>

namespace LE
{
    class IKernel;
}

EXPORT void init(LE::IKernel & k)
{
    LE::InfoModule_test(k, "Modules/enabled/init@LastTeam");
}

// + TODO test


EXPORT LE::InfoModule info;

LE::InfoModule info = {
    LE::Info::file(LE::version(0,0,0,1),
                   "2014/10/11",
                   "https://github.com/LastProject/LastEngine/tree/master/Modules/init%40LastTeam",
                   LE::Info::authors({
                        LE::Info::author("Neckara", "Neckara.LastDungeon@gmail.com")
                        })
                   ),
    LE::Info::modules({
        LE::Info::module("name", LE::version(0,0,0,1), "api", LE::version(0,0,0,1)),
        LE::Info::module("name", LE::version(0,0,0,1), "api", LE::version(0,0,0,1))
        })
    };
