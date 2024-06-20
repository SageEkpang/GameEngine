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
    bool m_Playing;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    AudioComponent();

    /// @brief Default Destructor for Class
    ~AudioComponent();


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class 
    void Update(float deltaTime) override;

    /// @brief Default Draw function for Class
    void Draw() override;

};

#endif