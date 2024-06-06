#ifndef ENEMY_H
#define ENEMY_H

// CUSTOM INCLUDE(s)
#include "Character.h"

class Enemy : public Character
{
protected:

public:

    // CLASS FUNCTION(s)

    /// @brief Custom Constructor for Class
    Enemy(std::string tag, std::string name, Transform2D transform, float health, float damage, float speed, float maxJump, Texture2D spriteSheet, Level* level);

    /// @brief Custom Constuctor for Class
    Enemy(std::string tag, std::string name, Vector2 position, float rotation, Vector2 size, float health, float damage, float speed, float maxJump, Texture2D spriteSheet, Level* level);


    /// @brief Default Destructor for Class
    virtual ~Enemy() {};

    
    // BASE FUNCTION(s)

    /// @brief Default Update function for Class 
    virtual void Update(float DeltaTime) override;

    /// @brief Default Draw function for Class
    virtual void Draw() override;

};

#endif