#include "CEntityTransformComponent.h"

#include <iostream>

#include "Engine/Object/Entity/CEntity.h"

CEntityTransformComponent::CEntityTransformComponent(): m_transform(), CEntityComponent()
{
    
}

void CEntityTransformComponent::SetLocalTransform(const STransform& transform)
{
    m_transform = transform;
}

void CEntityTransformComponent::Move(const SVector3f& vector)
{
    m_transform.Translation += vector;
}

const STransform& CEntityTransformComponent::GetLocalTransform() const
{
    return m_transform;
}

STransform CEntityTransformComponent::GetWorldTransform() const
{
    if(GetOwner()->GetEntityParent())
        return GetTransformMatrix();
    return m_transform;
}

SMatrix4f CEntityTransformComponent::GetTransformMatrix(const SVector3f& ViewOrigin) const
{
    SMatrix4f CurrentMatrix = m_transform.TransformMatrix(ViewOrigin);
    
    if(const CEntity* transform_parent = GetOwner()->GetEntityParent())
        CurrentMatrix = transform_parent->GetTransformComponent()->GetTransformMatrix(ViewOrigin) * CurrentMatrix;
    
    return CurrentMatrix;
}

SVector3f CEntityTransformComponent::GetForwardVector() const
{
    return -normalize(GetLocalTransform().GetRotationMatrix()[2]);
}

SVector3f CEntityTransformComponent::GetRightVector() const
{
    return normalize(GetLocalTransform().GetRotationMatrix()[0]);
}

SVector3f CEntityTransformComponent::GetUpVector() const
{
    return glm::normalize(GetLocalTransform().GetRotationMatrix()[1]);
}
