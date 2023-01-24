#ifndef CBoundInput_Header
#define CBoundInput_Header
#include <string>
#include <vector>

#include "CInputManager.h"
#include "Engine/Object/CObject.h"

class CBoundInput : public CObject
{
public:
    struct SButton
    {
        bool MouseButton;
        SDL_Scancode ButtonID;
        EMouseButton MouseID;

        SButton(SDL_Scancode code)
        {
            MouseButton = false;
            ButtonID = code;
        }
        SButton(EMouseButton button)
        {
            MouseButton = true;
            MouseID = button;
        }
    };
private:
    std::string m_boundInputName = "";
    std::vector<SButton> m_buttons;
    CWeakObjectPtr<CInputManager> m_inputManager;

public:
    CBoundInput();
    CBoundInput* Init(CInputManager& input_manager, const std::string& name);
    bool CheckButtons(EButtonEvent event);
    CBoundInput* AddButton(const SButton& button);
    const std::string& GetName() const { return m_boundInputName; }
};

#endif