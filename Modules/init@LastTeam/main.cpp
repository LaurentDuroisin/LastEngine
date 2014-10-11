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


EXPORT LE::InfoModule info = {
    {0x40506070, "2014", "http://", { {"Neckara", "e-mail"} } }, { {"name", 0, {"api", 0} } } };
