#ifndef CAABB_HEADER
#define CAABB_HEADER
#include <glm/glm.hpp>

#include "IAbstractCollisionShape.h"
#include "Engine/Object/CObject.h"
#include "Engine/Object/Entity/CEntity.h"

#define DEBUG_DRAW_COLLIDER

enum
{
	AABB_NotIntersected = 0,
	AABB_FullyIntersected = 1,
	AABB_PartiallyIntesected = 2,
};

enum
{
	AABB_Normal_Up,		 //(0,1,0)
	AABB_Normal_Down,	 //(0,-1,0)

	AABB_Normal_Left,	 //(-1,0,0)
	AABB_Normal_Right,	 //(1,0,0)

	AABB_Normal_Front,   //(0,0,1)
	AABB_Normal_Back,    //(0,0,-1)
};

class CAABB : public IAbstractCollisionShape
{
	SVector3f m_pivot;
	SVector3f m_size;

public:
	CAABB(const SVector3f& min, const SVector3f& max);

	SVector3f getMinVector(bool local = false) const;
	SVector3f getMaxVector(bool local = false) const;
	SVector3f getCenterVector(bool local = false) const;
	SVector3f getSizeVector() const;

	FCollisionShape GetCollisionShape() const override;
	bool RayCast(const SVector3f& position, const SVector3f& offset, SVector3f& normal, float& delta) override;

	bool ResolveDynamicSweep(CAABB& box, SVector3f& velocity, SVector3f& normal, bool forceNormalUp = false);

	bool RaySweep(CAABB& box, const SVector3f& offset, SVector3f& normal, float& delta);

	bool collidesWithPoint(SVector3f point);
};

inline SVector3f CAABB::getMinVector(bool local) const { return local ? m_pivot - m_size : GetTransformComponent()->GetWorldTransform().Translation + m_pivot - m_size; }
inline SVector3f CAABB::getMaxVector(bool local) const { return local ? m_pivot + m_size : GetTransformComponent()->GetWorldTransform().Translation + m_pivot + m_size; }
inline SVector3f CAABB::getCenterVector(bool local) const { return local ? m_pivot : GetTransformComponent()->GetWorldTransform().Translation + m_pivot; }
inline SVector3f CAABB::getSizeVector() const { return m_size; }

#endif