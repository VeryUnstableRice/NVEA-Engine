#include "CAABB.h"
#include "glm/gtx/string_cast.hpp"

#include <glm/gtx/component_wise.hpp>
#include <algorithm>
#include <iostream>


CAABB::CAABB(const SVector3f& min, const SVector3f& max)
{
	m_pivot = (min + max) * 0.5f;
	m_size = (max - min) * 0.5f;
}

/*
	SECOND BIGGEST SPAGHETTY MONSTER I'VE CREATED(first is the text), I MADE IT WORK, LIKE A GENETIC ALGORITHM, RANDOM CHANGES UNTIL IT WORKS.
	if someone else than me sees this, I hope you don't get mad, after all 2020 was not a great year
*/
bool CAABB::RayCast(const SVector3f& position, const SVector3f& offset, SVector3f& normal, float& delta)
{
	SVector3f NearUndiv, FarUndiv, aabbMin = getMinVector() , aabbMax =  getMaxVector() ;
	NearUndiv = aabbMax - position;
	FarUndiv = aabbMin - position;
	SVector3f invDir = 1.f / offset;
	SVector3f Near = NearUndiv * invDir;
	SVector3f Far = FarUndiv * invDir;
	normal = { 0,0,0 };
	
	if (Near.x > Far.x) std::swap(Near.x, Far.x);
	if (Near.y > Far.y) std::swap(Near.y, Far.y);
	if (Near.z > Far.z) std::swap(Near.z, Far.z);

	if(Near.x >= Far.y || Near.x >= Far.z) return false;
	if(Near.y >= Far.z || Near.y >= Far.x) return false;
	if(Near.z >= Far.y || Near.z >= Far.x) return false;

	delta = std::max({ Near.x, Near.y, Near.z });
	float hitFar = std::min({ Far.x, Far.y, Far.z });
	if (hitFar <= 0) return false;
	if (delta < 0) return false;

	const SVector3f hitPoint = position + offset * delta;

	int normals = 0;
	for(int i = 0; i < 3; ++i)
	{
		if(glm::abs(hitPoint[i] - aabbMin[i] ) == 0.0)
		{
			normal[i] = -1;
			++normals;
			continue;
		}
		if(glm::abs(hitPoint[i] - aabbMax[i]) == 0.0)
		{
			normal[i] = 1;
			++normals;
		}
	}

	if(normals > 1) normal = glm::vec3(0);
	return true;
}

bool CAABB::RaySweep(CAABB& box, const SVector3f& offset, SVector3f& normal, float& delta)
{
	struct sizer {
		CAABB *aabb, *t;
		glm::vec3 originalSize;
		sizer(CAABB* aabb, CAABB* t) : aabb(aabb), t(t) { originalSize = aabb->m_size; for(int i = 0; i < 3; ++i) aabb->m_size[i] += t->m_size[i]; };
		~sizer() { aabb->m_size = originalSize; };
	} s(&box, this);	

	if (box.RayCast(getCenterVector(), offset, normal, delta))
	{
		if (delta <= 1)
			return true;
	}
	return false;
}


bool CAABB::ResolveDynamicSweep(CAABB& box, SVector3f& velocity, SVector3f& normal, bool forceNormalUp)
{
	float delta;
	if (RaySweep(box, velocity, normal, delta))
	{
		if(forceNormalUp)
			normal.y = 1;
		velocity += normal * glm::abs(velocity) * (1.f - delta);
		return true;
	}
	return false;
}

bool CAABB::collidesWithPoint(SVector3f point)
{
	SVector3f min = getMinVector();
	SVector3f max = getMaxVector();
	bool x = min.x <= point.x && max.x >= point.x;
	bool y = min.y <= point.y && max.y >= point.y;
	bool z = min.z <= point.z && max.z >= point.z;

	return x && y && z;
}

FCollisionShape CAABB::GetCollisionShape() const
{
	return FCollisionShape::AABB;
}
