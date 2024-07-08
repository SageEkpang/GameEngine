#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

// NEEDED INCLUDE(s)
#include "Component.h"

class RenderComponent;

enum PlayerAnimState{
    IDLE,
    WALKING,
    JUMPING,
    START_DEATH,
    MIDDLE_DEATH,
    END_DEATH
};

enum AnimState {};

class AnimationComponent : public Component
{
private:

    // ANIMATION VARIABLE(s)
    float m_RunningTime;
    float m_UpdateTime = 1.0 / 13.0;
    float m_Frame;
    float m_MaxFrame;

    bool m_FlipX;
    int m_Flip = 1;

    float m_Animate;
    float m_MoveDown;

    // ANIMATION STATE VARIABLE(s)
    std::vector<AnimState> m_AnimationStates;
    AnimState m_AnimState;

    // RENDER COMPONENT VARIABLE(s)
    RenderComponent* m_RenderComponent;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    AnimationComponent(RenderComponent* renderComponent);

    /// @brief Default Destructor for Class
    ~AnimationComponent();


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class 
    void Update(float deltaTime) override;

    /// @brief Default Draw function for Class
    void Draw();


    // GETTER FUNCTION(s)


    // SETTER FUNCTION(s)
    void AddState(AnimState state) { m_AnimationStates.push_back(state); }


};





#endif