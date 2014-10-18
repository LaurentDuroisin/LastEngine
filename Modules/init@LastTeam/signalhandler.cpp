#include "signalhandler.h"

#include <iostream>

namespace
{
    void handler(int sig)
    {
        std::cerr << sig << std::endl;

        #ifdef __GNU_LIBRARY__
        size_t size = 32;
        void *array[size];

        size = backtrace(array, size);
        char ** symbols = backtrace_symbols(array, size);


        for(std::size_t i = 0; i != size; ++i)
            std::cerr << symbols[i] << std::endl;
        #endif
        exit(1);
    }
}

namespace LE
{
    SignalHandler::SignalHandler()
    {
        signal(SIGSEGV, handler);
        signal(SIGABRT, handler);
        signal(SIGFPE, handler);
        signal(SIGILL , handler);
    }
}
