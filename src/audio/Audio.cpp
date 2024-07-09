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


void Audio::Pause(const char *audioFilePath = "")
{
    //Will add code for pausing the current audio
}

void Audio::Stop(const char *audioFilePath = "")
{
    //Will add code for stoping the current audio
}




}

