#ifndef ENEMY_H
#define ENEMY_H

// PARENT CLASS
#include "GameObject.h"

// COMPONENT(s)
#include "AnimationComponent.h"
#include "CharacterComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"

class EnemyObject : public GameObject
{
private:
public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    /// @param tag 
    /// @param name 
    /// @param transform 
    /// @param health 
    /// @param damage 
    /// @param speed 
    /// @param maxJump 
    /// @param spriteSheet 
    EnemyObject(std::string tag, std::string name, Transform2Utility transform, float health, float damage, float speed, float maxJump, Texture2D spriteSheet);

    /// @brief Default Destructor for Class
    virtual ~EnemyObject() { };

    
    // BASE FUNCTION(s)

    /// @brief Default Update function for Class 
    virtual void Update(float DeltaTime) override;

    /// @brief Default Draw function for Class
    virtual void Draw() override;

};

#endif