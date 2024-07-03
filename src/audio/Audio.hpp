#pragma once

//#include <irrKlang/irrKlang.h>
#include "../../vendor/irrKlang/include/irrKlang.h"

namespace Synapse
{

class Audio
{
public:
    Audio() : m_audioBuffer(0){}
    ~Audio() = default;

    virtual void Play(const char *audioFilePath);
private:
    unsigned long long m_audioBuffer;
};


}

