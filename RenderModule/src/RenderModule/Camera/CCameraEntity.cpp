#include "CCameraEntity.h"
#include <glm/gtc/matrix_transform.hpp>
#include "CFrustumCollider.h"
#include "CCameraBuffer.h"
#include <glm/glm.hpp>

EngineMath::SMatrix4f CCameraEntity::GetView(bool coordZero) const
{
	CEntityTransformComponent* component = GetTransformComponent();
	
	const STransform Transform = component->GetWorldTransform();

	glm::mat4 output = QuatToMatrix(Transform.Rotation);
	if(!coordZero)
		output *= glm::translate(EngineMath::SMatrix4f(1), -Transform.Translation);

	return output;
}

EngineMath::SVector3f CCameraEntity::GetMiddle() const
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

	EngineMath::SVector4f output(minx+maxx, miny+maxy, minz+maxz, 1.0);
	output = output * 0.5f * GetView(false);
	return output;
}

void CCameraEntity::OnConstruct()
{
	m_cameraBuffer = CreateComponent<CCameraBuffer>();
	CEntity::OnConstruct();
	m_collider.updatePlanes();
}

void CCameraEntity::OnDestroy()
{
	CEntity::OnDestroy();
}

void CCameraEntity::Tick(double DeltaTime)
{
	CEntity::Tick(DeltaTime);
	if(m_info.GetDirty())
	{
		UpdateMatrix();
		m_info.SetDirty(false);
	}
}

void CCameraEntity::MakePerspective(float fovy, float aspect, float near, float far)
{
	m_projection = glm::perspective(glm::radians(fovy), aspect, near, far);
}

void CCameraEntity::MakeOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_projection = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void CCameraEntity::UpdateMatrix()
{
	if(m_info.Type == ECameraPerspective::PERSPECTIVE)
		MakePerspective(m_info.GetFov(), 1.f,  m_info.GetNear(), m_info.GetFar());
	else
		MakeOrtho(m_info.GetLeft(), m_info.GetRight(), m_info.GetBottom(), m_info.GetTop(), m_info.GetNear(), m_info.GetFar());
}

CCameraEntity::CCameraEntity() : m_collider(this)
{
}

CCameraEntity::~CCameraEntity()
{
}
