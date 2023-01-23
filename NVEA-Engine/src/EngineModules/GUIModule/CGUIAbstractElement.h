#ifndef CGUIAbstractElement_Header
#define CGUIAbstractElement_Header
#include <vector>

#include "Engine/Object/CObject.h"
#include "Engine/Object/Entity/EntityComponents/CEntityTransformComponent.h"

class CGUIAbstractElement : public CObject
{
    EngineMath::SVector2f m_min;
    EngineMath::SVector2f m_max;

    EngineMath::SVector2f m_anchorMin;
    EngineMath::SVector2f m_anchorMax;

    std::vector<CObjectPtr<CGUIAbstractElement>> m_children;
    CObjectPtr<CGUIAbstractElement> m_parent;
public:
    void OnConstruct() override;
    void OnDestroy() override;

    void AttachTo(CGUIAbstractElement* element);
    void DettachFromParent();

};

#endif