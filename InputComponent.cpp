#include "InputComponent.h"

InputComponent::InputComponent() 
{
    
}

InputComponent::~InputComponent() 
{
    if (!m_KeyMap.empty())
    {
        m_KeyMap.clear();
    }
}

void InputComponent::Update(float deltaTime) 
{
    for (size_t i = 0; i < m_Keys.size(); ++i)
    {
        switch(m_Keys[i].type)
        {
            case InputType::KEY_IDLE: if (IsKeyUp(m_Keys[i].key)) { ExecuteKey<void>(m_Keys[i].key); } break;
            case InputType::KEY_PRESS: if (IsKeyPressed(m_Keys[i].key)) { ExecuteKey<void>(m_Keys[i].key); } break;
            case InputType::KEY_DOWN: if (IsKeyDown(m_Keys[i].key)) { ExecuteKey<void>(m_Keys[i].key); } break;
            case InputType::KEY_RELEASE: if (IsKeyReleased(m_Keys[i].key)) { ExecuteKey<void>(m_Keys[i].key); } break;
        }
    }
}

void InputComponent::Draw() 
{
}

template<typename T>
inline void InputComponent::SetKeyInput(InputType type, KeyboardKey value, T func) 
{
    auto Ins = std::type_index(typeid(func));
    m_Keys.push_back(KeyType{value, type});
    m_KeyMap.insert(std::make_pair(value, std::make_pair((FunctionType)func, Ins)));
}

template<typename T, typename... Args>
inline T InputComponent::ExecuteKey(KeyboardKey& value, Args&&... args) 
{
    auto MapIndex = m_KeyMap.find(value);
    auto MapValue = MapIndex->second;
    auto TypeCastFunc = (T(*)(Args...))(MapValue.first);

    assert(MapValue.second == std::type_index(typeid(TypeCastFunc)));
    return TypeCastFunc(std::forward<Args>(args)...);
}
