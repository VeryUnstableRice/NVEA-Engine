#ifndef CCameraEntity_HEADER
#define CCameraEntity_HEADER
#include "CFrustumCollider.h"
#include "Engine/Object/Entity/CEntity.h"
#include "Engine/Object/Entity/EntityComponents/CEntityTransformComponent.h"

enum class ECameraPerspective
{
	PERSPECTIVE,
	ORTHO
};

struct CCameraInfo
{
	ECameraPerspective Type;
private:
	bool Dirty = true;
	float Near = 0.1f;
	float Far  = 100.f;
	float Fov = 90;
	float Left;
	float Right;
	float Top;
	float Bottom;

public:
	bool GetDirty() const
	{
		return Dirty;
	}

	void SetDirty(bool dirty)
	{
		Dirty = dirty;
	}
	
	float GetNear() const
	{
		return Near;
	}

	void SetNear(float near)
	{
		Near = near;
		Dirty = true;
	}

	float GetFar() const
	{
		return Far;
	}

	void SetFar(float far)
	{
		Far = far;
		Dirty = true;
	}

	float GetFov() const
	{
		return Fov;
	}

	void SetFov(float fov)
	{
		Fov = fov;
		Dirty = true;
	}

	float GetLeft() const
	{
		return Left;
	}

	void SetLeft(float left)
	{
		Left = left;
		Dirty = true;
	}

	float GetRight() const
	{
		return Right;
	}

	void SetRight(float right)
	{
		Right = right;
		Dirty = true;
	}

	float GetTop() const
	{
		return Top;
	}

	void SetTop(float top)
	{
		Top = top;
		Dirty = true;
	}

	float GetBottom() const
	{
		return Bottom;
	}

	void SetBottom(float bottom)
	{
		Bottom = bottom;
		Dirty = true;
	}
};

class CCameraEntity : public CEntity
{
	EngineMath::SMatrix4f m_projection;
	CFrustumCollider m_collider;
	CObjectPtr<class CCameraBuffer> m_cameraBuffer;

	CCameraInfo m_info;
	float m_near;
	float m_far;
	
	void MakePerspective(float fovy, float aspect, float near, float far);
	void MakeOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
	void UpdateMatrix();
public:
	CCameraEntity();
	~CCameraEntity() override;
	
	EngineMath::SMatrix4f GetView(bool coordZero) const;
	EngineMath::SVector3f GetMiddle() const;

	void OnConstruct() override;
	void OnDestroy() override;

	void SetPerspective(ECameraPerspective perspective);

	virtual void Tick(double DeltaTime) override;
	
	CCameraInfo& GetCameraInfo() { return m_info; };

	const EngineMath::SMatrix4f&	GetProjection() const	{ return m_projection;	}
	const CFrustumCollider&			GetCollider()			{ return m_collider;	}
	CCameraBuffer*					GetCameraBuffer()		{ return m_cameraBuffer; }
};

inline void CCameraEntity::SetPerspective(ECameraPerspective perspective)
{
	m_info.SetDirty(true);
	//m_info.Type = perspective;
	UpdateMatrix();
}

#endif