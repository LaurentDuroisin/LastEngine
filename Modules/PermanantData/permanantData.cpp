#include "permanantData.h"

#include <iostream>
#include <cassert>

extern "C"
{
    __declspec(dllexport) const char ** symbolList(void)
    {
        static const char * symbols[] = {"loadPermanantData", nullptr };
        return symbols;
    }
}

extern "C"
{
    __declspec(dllexport)

    NLP::InfoModule * loadPermanantData(NLP::InfoModule * asked, NLP::IModuleManager & moduleManager)
    {
        static NLP::InfoModule info = NLP::infoPermanantData();
        //info.changeCompatibility();
        //info.changeInterface();

        if( asked )
        {
            if( ! info.isCompatible( *(NLP::InfoModule *)asked ) )
                return nullptr;
        }

        std::cerr << "loaded" << std::endl;

        return & info;
    }
}
