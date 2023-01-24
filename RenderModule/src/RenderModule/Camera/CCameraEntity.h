#ifndef CCameraEntity_HEADER
#define CCameraEntity_HEADER
#include "CFrustumCollider.h"
#include "Engine/Object/Entity/CEntity.h"
#include "Engine/Object/Entity/EntityComponents/CEntityTransformComponent.h"

class CCameraEntity : public CEntity
{
	EngineMath::SMatrix4f m_projection;
	CFrustumCollider m_collider;
	uint8_t m_isOrtho : 1;
public:
	CCameraEntity();
	void MakePerspective(float fovy, float aspect, float near, float far);
	void MakeOrtho(float left, float right, float bottom, float top, float zNear, float zFar);

	EngineMath::SMatrix4f GetView(bool coordZero) const;
	EngineMath::SVector3f GetMiddle() const;
	virtual ~CCameraEntity() override;

	void OnConstruct() override;
	void OnDestroy() override;

	const EngineMath::SMatrix4f&			getProjection() const	{ return m_projection;	}
	const CFrustumCollider&		getCollider()			{ return m_collider;	}
	bool						isOrtho()		const	{ return m_isOrtho;		}
};

#endif