#include "InputComponent.h"

InputComponent::InputComponent() 
{
    m_KeyMap[Input::PLAYER_ONE] = new KeyboardKey[5] {KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_SPACE};
    m_KeyMap[Input::PLAYER_TWO] = new KeyboardKey[5] {KEY_W, KEY_A, KEY_S, KEY_D, KEY_Z};
}

// TODO: Make key binding function (input flag, key flag, script object)

InputComponent::~InputComponent() 
{
    if (!m_KeyMap.empty())
    {
        m_KeyMap.clear();
    }
}

void InputComponent::Update(float deltaTime) 
{
    if (IsKeyDown(m_Keys[0])) m_Transform->MoveUp(PLAYER_SPEED * deltaTime);
    if (IsKeyDown(m_Keys[1])) m_Transform->MoveLeft(PLAYER_SPEED * deltaTime);
    if (IsKeyDown(m_Keys[2])) m_Transform->MoveDown(PLAYER_SPEED * deltaTime);
    if (IsKeyDown(m_Keys[3])) m_Transform->MoveRight(PLAYER_SPEED * deltaTime);
    // TODO: Need to do jump (if the jump button was pressed, it would manipulate the speed of which)
    // you go up at so it would have something to do with the physics component that wil be written
    // so for now leave the keys as they are and sort out the phyics and jump later
}

void InputComponent::Draw() 
{
}

inline void InputComponent::SetPlayerInput(Input playerType) 
{
    switch(playerType)
    {
        case Input::PLAYER_ONE: InsertElements(m_KeyMap[Input::PLAYER_ONE], 5); break;
        case Input::PLAYER_TWO: InsertElements(m_KeyMap[Input::PLAYER_TWO], 5); break;
        default: InsertElements(m_KeyMap[Input::PLAYER_ONE], 5); break;
    }
}

void InputComponent::InsertElements(KeyboardKey* values, int size) 
{
    for (int i = 0; i < size; ++i)
    {
        m_Keys[i] = values[i];
    }
}
