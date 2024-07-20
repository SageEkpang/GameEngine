#ifndef PLAYER_INPUT_COMPONENT_H
#define PLAYER_INPUT_COMPONENT_H

// NEEDED INCLUDE(s)
#include "Component.h"

enum InputType
{
    INPUT_KEY_IDLE, // 0
    INPUT_KEY_PRESS, // 1
    INPUT_KEY_DOWN, // 2
    INPUT_KEY_RELEASE // -1
};

struct KeyType
{
    KeyboardKey key;
    InputType type;
};

typedef void (*FunctionType)(void);

class InputComponent : public Component
{
private:

    // PRIVATE VARIABLE(s)
    std::vector<KeyType> m_Keys; // Takes in Key and Script tied to that key
    std::map<KeyboardKey, std::pair<FunctionType, std::type_index>> m_KeyMap;

    template<typename T, typename... Args>
    inline T ExecuteKey(KeyboardKey& value, Args&&... args);

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
    template<typename T>
    inline void SetKeyInput(InputType type, KeyboardKey value, T func);

};

#endif