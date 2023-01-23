#include "CBoundInput.h"


CBoundInput::CBoundInput()
{
}


CBoundInput* CBoundInput::Init(CInputManager& input_manager, const std::string& name)
{
    m_inputManager = &input_manager;
    m_boundInputName = name;
    return this;
}

bool CBoundInput::CheckButtons(EButtonEvent event)
{
    for(const SButton& button : m_buttons)
    {
        if(button.MouseButton && m_inputManager->MouseButtonStatus(button.MouseID, event) || !button.MouseButton && m_inputManager->KeyStatus(button.ButtonID, event))
            return true;
    }
    return false;
}

CBoundInput* CBoundInput::AddButton(const SButton& button)
{
    m_buttons.push_back(button);
    return this;
}
