#pragma once

//#include <irrKlang/irrKlang.h>
#include "../../vendor/irrKlang/include/irrKlang.h"

namespace Synapse
{


using namespace irrklang;

class Audio
{
public:
    Audio() : m_soundEngine(createIrrKlangDevice()), m_audioBuffer(0){}
    ~Audio() = default;

    virtual void Play(const char *audioFilePath);
private:
    ISoundEngine *m_soundEngine = nullptr;
    unsigned long *m_audioBuffer = nullptr;
};


}

