#include "Audio.hpp"

namespace Synapse
{


void Audio::Play(const char *audioFilePath)
{
#define __ADD__AUDIO__
#ifdef __ADD__AUDIO__

    //using namespace irrklang;
    //m_soundEngine = createIrrKlangDevice();
    m_soundEngine->play2D(audioFilePath, true);

#endif
}


}

