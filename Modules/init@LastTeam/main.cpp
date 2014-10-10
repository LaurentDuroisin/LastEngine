#include <LastEngine/Visibility.h>
#include <iostream>

namespace LE
{
    class IKernel;
}

EXPORT void init(LE::IKernel & k)
{
    std::cerr << "ok" << std::endl;
    // init algorithm
}

// + TODO test
