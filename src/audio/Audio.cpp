#include "Audio.hpp"

namespace Synapse
{


void Audio::Play(const char *audioFilePath)
{
#ifdef __ADD__AUDIO__

    using namespace irrklang;
    ISoundEngine *SoundEngine = createIrrKlangDevice();
    SoundEngine->play2D(audioFilePath, true);

#endif
}


}

