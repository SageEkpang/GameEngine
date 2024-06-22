#ifndef AUDIO_COMPONENT_H
#define AUDIO_COMPONENT_H

// Parent Include
#include "Component.h"

class AudioComponent : public Component
{
private:

    Sound m_Sound;
    const char* m_SoundFileName;
    float m_Volume;
    bool m_Looping;
    int m_PlayTime;
    bool m_Playing;
    bool m_HasSoundPlayed;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    AudioComponent(const char* sound);

    /// @brief Default Destructor for Class
    ~AudioComponent();


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class 
    void Update(float deltaTime) override;

    /// @brief Default Draw function for Class
    void Draw() override;


    // GETTER FUNCTION(s)
    const char* GetSoundFileName() const { return m_SoundFileName; }
    float GetVolume() const { return m_Volume; }
    bool GeLooping() const { return m_Looping; }
    int GetPlayTime() const { return m_Looping; }
    bool GetPlaying() const { return m_Playing; }


    // SETTER FUNCTION(s)
    void SetVolume(float volume) { SetSoundVolume(m_Sound, volume); }
    void SetLooping(bool looping) { this->m_Looping = looping; }
    void SetPlayTime(float playTime) { this->m_PlayTime = playTime; }
    void SetPlaying(bool playing) { this->m_Playing = playing; }
};

#endif