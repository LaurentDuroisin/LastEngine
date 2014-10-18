#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

#include <cstdlib>
#include <csignal>
#include <unistd.h>
#include <execinfo.h>

namespace LE
{
    class SignalHandler
    {
    public:
        SignalHandler();
    };
}

#endif // SIGNALHANDLER_H
