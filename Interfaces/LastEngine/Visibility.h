#ifndef VISIBILITY_H
#define VISIBILITY_H

#ifdef _WIN32
    #define EXPORT extern "C" __declspec(dllexport)
#else
    #define EXPORT extern "C" __attribute__((visibility("default")))
#endif


#endif // VISIBILITY_H
