#ifndef IPREFERENCE_H
#define IPREFERENCE_H

#include "../ModuleManager/InfoModule.h"
#include "../ModuleManager/IModuleManager.h"

namespace NLP
{
    inline const InfoModule & infoPermanantData(void)
    {
        const static InfoModule infoModule("Neckara",
                                           "https://github.com/LastProject/LastEngine/tree/master/Modules/PermanantData",
                                           "PermanantData",
                                           "libPermanantData",
                                           0,
                                           1406375982,
                                           "",
                                           nullptr,
                                           "loadPermanantData");
        return infoModule;
    }

    class IPermanantData {
    public :
        virtual ~IPermanantData(void){}
    };
}

#endif // IPREFERENCE_H
