#ifndef PLAYER_INPUT_COMPONENT_H
#define PLAYER_INPUT_COMPONENT_H

// NEEDED INCLUDE(s)
#include "Component.h"

enum Input{
    PLAYER_ONE,
    PLAYER_TWO
};

class InputComponent : public Component
{
private:

    // PRIVATE VARIABLE(s)
    std::map<Input, KeyboardKey*> m_KeyMap;
    std::map<KeyboardKey, int> m_KeyBoardScriptMap; // Takes in Key and Script tied to that key
    KeyboardKey m_Keys[5];

    // PRIVATE FUNCTION(s)
    void InsertElements(KeyboardKey* values, int size);

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    InputComponent();

    /// @brief Default Destructor for Class
    ~InputComponent();


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class
    void Update(float deltaTime) override;

    /// @brief Default Draw function for Class
    void Draw() override;



    // GETTER FUNCTION(s)



    // SETTER FUNCTION(s)
    inline void SetPlayerInput(Input playerType);

};

#endif