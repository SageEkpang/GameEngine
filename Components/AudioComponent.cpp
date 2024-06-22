#include "AudioComponent.h"

AudioComponent::AudioComponent(const char* sound) 
{
    m_SoundFileName = sound;
    m_Sound = LoadSound(sound);

    m_Volume = 0.0f;
    SetSoundVolume(m_Sound, m_Volume);

    m_Looping = false;
    m_PlayTime = 1.0f;
    m_Playing = false;
    m_HasSoundPlayed = false;
}

AudioComponent::~AudioComponent() 
{
    UnloadSound(m_Sound);
}

void AudioComponent::Update(float deltaTime) 
{
    if (m_Looping == false)
    {
        // Play Sound (Once)
        if (!IsSoundPlaying(m_Sound) && m_HasSoundPlayed == false)
        {
            PlaySoundMulti(m_Sound);
            m_HasSoundPlayed = true;
        }
    }
    else if (m_Looping == true)
    {
        // Play Sound (Looping)
        if (!IsSoundPlaying(m_Sound))
        {
            PlaySoundMulti(m_Sound);
        }
    }
}

void AudioComponent::Draw() 
{
}
