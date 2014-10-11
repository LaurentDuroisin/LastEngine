#include <LastEngine/Visibility.h>
#include <LastEngine/InfoModule.h>
#include <iostream>

namespace LE
{
    class IKernel;
}

EXPORT void init(LE::IKernel & k)
{
    LE::Info::InfoModule_test(k, "Modules/enabled/init@LastTeam");
}

// + TODO test


EXPORT LE::Info::File info;

using namespace LE::Info;

File info{
    version(0,0,0,1),
    "2014/10/11",
    "https://github.com/LastProject/LastEngine/tree/master/Modules/init%40LastTeam",
    Authors{
        Author{"Neckara", "Neckara.LastDungeon@gmail.com"}
    },
    Modules{
        Module{"name", version(0,0,0,1), API{"api", version(0,0,0,1)} },
        Module{"name", version(0,0,0,1), API{"api", version(0,0,0,1)} }
    }
};
