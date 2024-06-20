#ifndef AUDIO_COMPONENT_H
#define AUDIO_COMPONENT_H

// Parent Include
#include "Component.h"

class AudioComponent : public Component
{
private:

    float m_Volume;
    bool m_Looping;
    int m_PlayTime;

public:

    // CLASS FUNCTION(s)

    AudioComponent();

    ~AudioComponent();


    // BASE FUNCTION(s)

    void Update(float deltaTime) override;

    void Draw() override;


};

#endif