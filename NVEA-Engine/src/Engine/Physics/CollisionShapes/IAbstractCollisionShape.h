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
    virtual bool RayCast(const SVector3f& position, const SVector3f& offset, SVector3f& normal, float& delta) = 0;
    virtual FCollisionShape GetCollisionShape() const = 0;
};

#endif