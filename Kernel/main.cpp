#include "kernel.h"
#include <cstdlib>
#include <string>

#include <iostream>

/** @mainpage Last Engine
 *
 */

int main(int, char ** argv)
{
    LE::Kernel k;

    std::string command = argv[0];
    auto it = command.find_last_of('/');
    if( it != std::string::npos )
    {
        command.erase(it + 1);
        k.pathPrefixe(std::move(command));
    }

    k.run();
    return EXIT_SUCCESS;
}

