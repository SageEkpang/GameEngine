#include "InputComponent.h"

InputComponent::InputComponent()
{
	m_ActionMapping.clear();
}

InputComponent::~InputComponent()
{
	m_ActionMapping.clear();
}

void InputComponent::Update(const float deltaTime)
{
	for (int i = 0; i < m_ActionMapping.size(); ++i)
	{
		// NOTE: Check if the lambda function is nullptr or not
		if (m_ActionMapping[i].actionLambda == nullptr) { continue; }

		// NOTE: Execute the action mapping component dependant on what is pressed
		switch (m_ActionMapping[i].type)
		{
			// KEYBOARD(s)
			case InputType::INPUT_TYPE_KEY_PRESSED: if (IsKeyPressed(m_ActionMapping[i].key)) { m_ActionMapping[i].actionLambda(); } break;
			case InputType::INPUT_TYPE_KEY_REPEAT_PRESSED: if (IsKeyPressedRepeat(m_ActionMapping[i].key)) { m_ActionMapping[i].actionLambda(); } break;
			case InputType::INPUT_TYPE_KEY_RELEASED: if (IsKeyReleased(m_ActionMapping[i].key)) { m_ActionMapping[i].actionLambda(); } break;
			case InputType::INPUT_TYPE_KEY_HELD: if (IsKeyDown(m_ActionMapping[i].key)) { m_ActionMapping[i].actionLambda(); } break;
			case InputType::INPUT_TYPE_KEY_UP: if (IsKeyUp(m_ActionMapping[i].key)) { m_ActionMapping[i].actionLambda(); } break;

			// MOUSE(s)
			case InputType::INPUT_TYPE_MOUSE_PRESSED: if (IsMouseButtonPressed(m_ActionMapping[i].key)) { m_ActionMapping[i].actionLambda(); } break;
			case InputType::INPUT_TYPE_MOUSE_RELEASED: if (IsMouseButtonReleased(m_ActionMapping[i].key)) { m_ActionMapping[i].actionLambda(); } break;
			case InputType::INPUT_TYPE_MOUSE_HELD: if (IsMouseButtonDown(m_ActionMapping[i].key)) { m_ActionMapping[i].actionLambda(); } break;
			case InputType::INPUT_TYPE_MOUSE_UP: if (IsMouseButtonUp(m_ActionMapping[i].key)) { m_ActionMapping[i].actionLambda(); } break;
		}
	}
}

void InputComponent::AddInputMapping(std::int8_t key, InputType type, void(*input_action_lambda)())
{
	InputAction t_tempAction;
	t_tempAction.key = key;
	t_tempAction.type = type;
	t_tempAction.actionLambda = input_action_lambda;
	m_ActionMapping.push_back(t_tempAction);
}
