#ifndef PLAYER_H
#define PLAYER_H

#include "CharacterComponent.h"

// TODO: Can add like a projectile functionality here or something

class PlayerObject : public CharacterComponent
{
private:

public:

    // CLASS FUNCTION(s)


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class
    void Update(float DeltaTime) override;

    /// @brief Default Draw function for Class
    void Draw() override;

};

#endif