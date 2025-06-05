#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "ComponentEntity.h"
#include <iostream>
#include <unordered_map>
#include <functional>
#include "raylib.h"

enum class InputType : std::int8_t
{
	// KEYBOARD
	INPUT_TYPE_KEY_PRESSED,
	INPUT_TYPE_KEY_REPEAT_PRESSED,
	INPUT_TYPE_KEY_RELEASED,
	INPUT_TYPE_KEY_HELD,
	INPUT_TYPE_KEY_UP,

	// MOUSE
	INPUT_TYPE_MOUSE_PRESSED,
	INPUT_TYPE_MOUSE_RELEASED,
	INPUT_TYPE_MOUSE_HELD,
	INPUT_TYPE_MOUSE_UP,

	INPUT_TYPE_NONE
};

struct InputAction
{
	std::int8_t key;
	InputType type;
	std::function<void()> actionLambda;
};

// Need an event que for this 

class InputComponent : public ComponentEntity
{
private: // PRIVATE VARIABLE(s)

	std::vector<InputAction> m_ActionMapping;

public: // PUBLIC FUNCTION(s)

	// CLASS FUNCTION(s)
	InputComponent();
	~InputComponent() override;

	// BASE FUNCTION(s)
	void Update(const float deltaTime) override;

	// HELPER FUNCTION(s) 
	void AddInputMapping(std::int8_t key, InputType type, std::function<void()> input_action_lambda);

};

#endif