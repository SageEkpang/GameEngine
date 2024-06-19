#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

// COMPONENT(s)
#include "AnimationComponent.h"
#include "CharacterComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"

class PlayerObject : public GameObject
{
private:
public:

    // CLASS FUNCTION(s)
    PlayerObject(std::string tag, std::string name, Transform2Utility transform, float health, float damage, float speed, float maxJump, Texture2D spriteSheet);


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class
    void Update(float DeltaTime) override;

    /// @brief Default Draw function for Class
    void Draw() override;

};

#endif