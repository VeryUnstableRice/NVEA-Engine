#include "CGUICanvas.h"

#include "CGUIEngineModule.h"

void CGUICanvas::RenderEverything()
{
    
}

void CGUICanvas::AddToScreen()
{
    CGUIEngineModule::Instance->AddCanvas(this);
}

void CGUICanvas::RemoveFromScreen()
{
    CGUIEngineModule::Instance->RemoveCanvas(this);
}
