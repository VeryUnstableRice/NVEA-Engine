#include "CCameraEntity.h"
#include <glm/gtc/matrix_transform.hpp>
#include "CFrustumCollider.h"
#include <iostream>
#include <glm/glm.hpp>
#include <iostream>

SMatrix4f CCameraEntity::GetView(bool coordZero) const
{
	CEntityTransformComponent* component = GetTransformComponent();
	
	const STransform Transform = component->GetWorldTransform();

	glm::mat4 output = glm::inverse(QuatToMatrix(Transform.Rotation));
	//SEulerRotator rotator = ToEuler(Transform.Rotation);
	//output *= glm::rotate(glm::mat4(1), glm::radians((float)rotator.Pitch),		{ 0, 1, 0 }); //pitch
	//output *= glm::rotate(glm::mat4(1), glm::radians((float)rotator.Yaw),		{ 1, 0, 0 }); //yaw
	//output *= glm::rotate(glm::mat4(1), glm::radians((float)rotator.Roll),		{ 0, 0, 1 }); //roll
	if(!coordZero)
		output *= glm::translate(glm::mat4(1), -Transform.Translation);

	return output;
}

SVector3f CCameraEntity::GetMiddle() const
{
	glm::mat4 invproj = glm::inverse(m_projection);
	std::vector<glm::vec4> margins = 
	{
		{ 1, 1, 1, 1},
		{ 1,-1, 1, 1},
		{-1,-1, 1, 1},
		{-1, 1, 1, 1},
		{ 1, 1,-1, 1},
		{ 1,-1,-1, 1},
		{-1,-1,-1, 1},
		{-1, 1,-1, 1}
	};

	float minx = INFINITY, miny = INFINITY, minz = INFINITY, maxx= -INFINITY, maxy = -INFINITY, maxz = -INFINITY;
	for(auto& v : margins)
	{
		v = invproj * v;
		v.x /= v.w;
		v.y /= v.w;
		v.z /= v.w;
		minx = std::min(minx, v.x);
		miny = std::min(miny, v.y);
		minz = std::min(minz, v.z);

		maxx = std::max(maxx, v.x);
		maxy = std::max(maxy, v.y);
		maxz = std::max(maxz, v.z);
	}

	SVector4f output(minx+maxx, miny+maxy, minz+maxz, 1.0);
	output = output * 0.5f * GetView(false);
	return output;
}

CCameraEntity::~CCameraEntity()
{
}

void CCameraEntity::OnConstruct()
{
	CEntity::OnConstruct();
	m_collider.updatePlanes();
}

void CCameraEntity::OnDestroy()
{
	CEntity::OnDestroy();
}


CCameraEntity::CCameraEntity() : m_collider(this)
{
}

void CCameraEntity::MakePerspective(float fovy, float aspect, float near, float far)
{
	m_isOrtho = 0;
	m_projection = glm::perspective(glm::radians(fovy), aspect, near, far);
}

void CCameraEntity::MakeOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_isOrtho = 1;
	m_projection = glm::ortho(left, right, bottom, top, zNear, zFar);
}
