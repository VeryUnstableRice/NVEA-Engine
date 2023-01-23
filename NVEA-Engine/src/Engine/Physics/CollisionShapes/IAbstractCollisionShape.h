#ifndef CAbstractCollisionShape_Header
#define CAbstractCollisionShape_Header

#include "Engine/Object/Entity/CEntity.h"

enum class FCollisionShape : std::uint8_t
{
    AABB
};

class IAbstractCollisionShape : public CEntity
{
public:
    virtual bool RayCast(const EngineMath::SVector3f& position, const EngineMath::SVector3f& offset, EngineMath::SVector3f& normal, float& delta) = 0;
    virtual FCollisionShape GetCollisionShape() const = 0;
};

#endif