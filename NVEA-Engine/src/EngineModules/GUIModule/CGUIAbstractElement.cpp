#include "CGUIAbstractElement.h"

#include "Engine/Math/Math.h"

void CGUIAbstractElement::OnConstruct()
{
    CObject::OnConstruct();
    m_min           = EngineMath::SVector2f(0.f, 0.f);
    m_max           = EngineMath::SVector2f(0.f, 0.f);
    m_anchorMin     = EngineMath::SVector2f(0.f, 0.f);
    m_anchorMax     = EngineMath::SVector2f(1.f, 1.f);
}

void CGUIAbstractElement::OnDestroy()
{
    CObject::OnDestroy();
}

void CGUIAbstractElement::AttachTo(CGUIAbstractElement* element)
{
    if(!element) return;
    if(element->m_parent)
        DettachFromParent();
    m_children.push_back(element);
    element->m_parent = this;
}

void CGUIAbstractElement::DettachFromParent()
{
    if(!m_parent) return;
    std::erase(m_parent->m_children, this);
    m_parent = nullptr;
}
