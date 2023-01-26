#include "CFrustumCollider.h"
#include "CCameraEntity.h"

void CFrustumCollider::updatePlanes()
{
	glm::mat4 matrix = m_parent->GetProjection() * m_parent->GetView(false);
	
	//CAMERA HAS PERSPECTIVE 
	if(m_parent->GetCameraInfo().Type == ECameraPerspective::PERSPECTIVE)
	{
		//LEFT
		m_planes[0].a = matrix[0][3] + matrix[0][0];
		m_planes[0].b = matrix[1][3] + matrix[1][0];
		m_planes[0].c = matrix[2][3] + matrix[2][0];
		m_planes[0].d = matrix[3][3] + matrix[3][0];
		//RIGHT					 [3]
		m_planes[1].a = matrix[0][3] - matrix[0][0];
		m_planes[1].b = matrix[1][3] - matrix[1][0];
		m_planes[1].c = matrix[2][3] - matrix[2][0];
		m_planes[1].d = matrix[3][3] - matrix[3][0];
		//TOP					 [3]
		m_planes[2].a = matrix[0][3] - matrix[0][1];
		m_planes[2].b = matrix[1][3] - matrix[1][1];
		m_planes[2].c = matrix[2][3] - matrix[2][1];
		m_planes[2].d = matrix[3][3] - matrix[3][1];
		//BOTTOM				 [3]
		m_planes[3].a = matrix[0][3] + matrix[0][1];
		m_planes[3].b = matrix[1][3] + matrix[1][1];
		m_planes[3].c = matrix[2][3] + matrix[2][1];
		m_planes[3].d = matrix[3][3] + matrix[3][1];
		//NEAR					 [3]
		m_planes[4].a = matrix[0][3] + matrix[0][2];
		m_planes[4].b = matrix[1][3] + matrix[1][2];
		m_planes[4].c = matrix[2][3] + matrix[2][2];
		m_planes[4].d = matrix[3][3] + matrix[3][2];
		//FAR					 [3]
		m_planes[5].a = matrix[0][3] - matrix[0][2];
		m_planes[5].b = matrix[1][3] - matrix[1][2];
		m_planes[5].c = matrix[2][3] - matrix[2][2];
		m_planes[5].d = matrix[3][3] - matrix[3][2];
		return;
	}
	//CAMERA HAS ORTHO VIEW

}

CFrustumCollider::CFrustumCollider(CCameraEntity* parent) : m_parent(parent)
{
	//updatePlanes();
}

bool CFrustumCollider::sphereIntersection(glm::vec3 center, float radius) const
{
	if(m_parent->GetCameraInfo().Type == ECameraPerspective::PERSPECTIVE) return true;
	//updatePlanes();
	for (int i = 0; i < 6; ++i)
	{
		glm::vec3 temp = glm::vec3(m_planes[i].a, m_planes[i].b, m_planes[i].c);
		if (glm::dot(center, temp) + m_planes[i].d + radius < 0)
			return false;
	}
	return true;
}
