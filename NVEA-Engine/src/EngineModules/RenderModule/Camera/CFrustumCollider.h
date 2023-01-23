#ifndef CFrustumCollider_Header
#define CFrustumCollider_Header
//#include "CAABB.h"
#include <array>
#include <glm/glm.hpp>

struct Plane
{
	float a, b, c, d;
};

class CFrustumCollider
{
	class CCameraEntity* m_parent;
	std::array<Plane, 6> m_planes;

public:
	CFrustumCollider(class CCameraEntity* parent);
	bool sphereIntersection(glm::vec3 center, float radius) const;

	void updatePlanes();

};

#endif