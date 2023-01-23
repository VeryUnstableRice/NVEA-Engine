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

void CEntityTransformComponent::Move(const EngineMath::SVector3f& vector)
{
    m_transform.Translation += vector;
}

const STransform& CEntityTransformComponent::GetLocalTransform() const
{
    return m_transform;
}

STransform CEntityTransformComponent::GetWorldTransform() const
{
    //return GetTransformMatrix();
    if(GetOwner()->GetEntityParent())
        return GetTransformMatrix();
    return m_transform;
}

EngineMath::SMatrix4f CEntityTransformComponent::GetTransformMatrix(const EngineMath::SVector3f& ViewOrigin) const
{
    EngineMath::SMatrix4f CurrentMatrix = m_transform.TransformMatrix(ViewOrigin);
    
    if(const CEntity* transform_parent = GetOwner()->GetEntityParent())
        CurrentMatrix = transform_parent->GetTransformComponent()->GetTransformMatrix(ViewOrigin) * CurrentMatrix;
    
    return CurrentMatrix;
}

EngineMath::SVector3f CEntityTransformComponent::GetRightVector() const
{
    return glm::normalize(GetLocalTransform().GetRotationMatrix(0b1)[0]);
}

EngineMath::SVector3f CEntityTransformComponent::GetUpVector() const
{
    return glm::normalize(GetLocalTransform().GetRotationMatrix(0b10)[1]);
}

EngineMath::SVector3f CEntityTransformComponent::GetForwardVector() const
{
    return -glm::normalize(GetLocalTransform().GetRotationMatrix(0b100)[2]);
}