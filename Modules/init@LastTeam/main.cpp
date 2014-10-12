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

File info{ // todo constructor + copy
    Version(0,0,0,1), // todo struct.
    "2014/10/11",
    "https://github.com/LastProject/LastEngine/tree/master/Modules/init%40LastTeam",
    Authors{
        Author{"Neckara", "Neckara.LastDungeon@gmail.com"} // todo constructor + copy
    },
    Modules{
        Module{"name", Version(0,0,0,1), API{"api", Version(0,0,0,1)} }, // todo constructor + copy * 2
        Module{"name", Version(0,0,0,1), API{"api", Version(0,0,0,1)} }
    }
};
