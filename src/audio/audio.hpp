#pragma once

namespace Synapse
{

class Audio
{
public:
    Audio() : m_audioBuffer(0){}
    ~Audio() = default;

    virtual void Play();
private:
    unsigned long long m_audioBuffer;
};


}

