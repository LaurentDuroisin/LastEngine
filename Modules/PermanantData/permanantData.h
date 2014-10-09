#ifndef PREFERENCES_H
#define PREFERENCES_H

#include "IPermanantData.h"

namespace NLP
{
    class PermanantData : public IPermanantData
    {
    public :
        PermanantData(IModuleManager & moduleManager);
    private :
        IModuleManager & m_moduleManager;

    };

    bool checkCompatibility(const InfoModule & info);
}

#endif // PREFERENCES_H
