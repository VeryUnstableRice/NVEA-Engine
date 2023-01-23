#ifndef CGUICanvas_Header
#define CGUICanvas_Header
#include "CGUIAbstractElement.h"

class CGUICanvas : public CGUIAbstractElement
{
    void RenderEverything();
public:
    void AddToScreen();
    void RemoveFromScreen();
};

#endif