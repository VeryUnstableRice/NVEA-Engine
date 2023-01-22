#ifndef CTransformComponent_Header
#define CTransformComponent_Header
#include <assert.h> 
#include <string>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <SDL2/SDL_stdinc.h>

#include "CEntityComponent.h"

typedef glm::vec3 SVector3f;
typedef glm::vec2 SVector2f;
typedef glm::vec4 SVector4f;
typedef glm::mat4 SMatrix4f;
typedef glm::mat3 SMatrix3f;

struct SEulerRotator
{
    float Yaw;
    float Pitch;
    float Roll;
    SEulerRotator(float Yaw = 0, float Pitch = 0, float Roll = 0) : Yaw(Yaw), Pitch(Pitch), Roll(Roll) {}
};

using SQuaternionRotator = glm::quat;

inline SEulerRotator ToEuler(const SQuaternionRotator& Quat)
{
    SEulerRotator rotator;
    SQuaternionRotator q = glm::normalize(Quat);
    // roll (x-axis rotation)
    float sinr_cosp = 2.f * (q.w * q.x + q.y * q.z);
    float cosr_cosp = 1.f - 2.f * (q.x * q.x + q.y * q.y);
    rotator.Yaw = std::atan2f(sinr_cosp, cosr_cosp) * 180.f/(float)M_PI;

    // pitch (y-axis rotation)
    float sinp = std::sqrtf(1.f + 2.f * (q.w * q.y - q.x * q.z));
    float cosp = std::sqrtf(1.f - 2.f * (q.w * q.y - q.x * q.z));
    rotator.Pitch = ( 2.f * std::atan2f(sinp, cosp) - (float)M_PI / 2.f)* 180.f/(float)M_PI;

    // yaw (z-axis rotation)
    float siny_cosp = 2.f * (q.w * q.z + q.x * q.y);
    float cosy_cosp = 1.f - 2.f * (q.y * q.y + q.z * q.z);
    rotator.Roll = std::atan2f(siny_cosp, cosy_cosp)* 180.f/(float)M_PI;

    return rotator;
}

inline SQuaternionRotator ToQuaternions(const SEulerRotator& euler)
{
    SQuaternionRotator quat;
    float yawRad    = euler.Yaw     * (float)M_PI / 180.f;
    float pitchRad  = euler.Pitch   * (float)M_PI / 180.f;
    float rollRad   = euler.Roll    * (float)M_PI / 180.f;

    float yawCos = std::cosf(yawRad*0.5f);
    float yawSin = std::sinf(yawRad*0.5f);

    float pitchCos = std::cosf(pitchRad*0.5f);
    float pitchSin = std::sinf(pitchRad*0.5f);

    float rollCos = std::cosf(rollRad*0.5f);
    float rollSin = std::sinf(rollRad*0.5f);
    
    quat.w = yawCos * pitchCos * rollCos + yawSin * pitchSin * rollSin;
    quat.x = yawSin * pitchCos * rollCos - yawCos * pitchSin * rollSin;
    quat.y = yawCos * pitchSin * rollCos + yawSin * pitchCos * rollSin;
    quat.z = yawCos * pitchCos * rollSin - yawSin * pitchSin * rollCos;
    return quat;
}

inline SMatrix4f QuatToMatrix(const SQuaternionRotator& quat, char flags = 0b111)
{
    SMatrix4f R(1);
    float w = quat.w;
    float x = quat.x;
    float y = quat.y;
    float z = quat.z;

    if(flags & 0b1)
    {
        R[0][0] = 1 - 2*y*y - 2*z*z;
        R[0][1] = 2*x*y - 2*w*z;
        R[0][2] = 2*x*z + 2*w*y;
    }

    if(flags & 0b10)
    {
        R[1][0] = 2*x*y + 2*w*z;
        R[1][1] = 1 - 2*x*x - 2*z*z;
        R[1][2] = 2*y*z - 2*w*x;
    }

    if(flags & 0b100)
    {
        R[2][0] = 2*x*z - 2*w*y;
        R[2][1] = 2*y*z + 2*w*x;
        R[2][2] = 1 - 2*x*x - 2*y*y;
    }

    return R;
}

struct STransform
{
    SVector3f           Translation;
    SQuaternionRotator  Rotation;
    SVector3f           Scale;

    SMatrix4f TransformMatrix(const SVector3f& ViewOrigin = SVector3f(0)) const
    {
        const SMatrix4f transform = glm::translate(SMatrix4f(1), Translation-ViewOrigin);
        return transform * GetRotationMatrix() * glm::scale(SMatrix4f(1), Scale);
    }

    SMatrix4f GetRotationMatrix(char flags = 0b111) const
    {
        return QuatToMatrix(Rotation, flags);
    }

    STransform(const SVector3f& translation = SVector3f(0), const SQuaternionRotator& rotation=SQuaternionRotator(), const SVector3f& scale=SVector3f(1)) :
        Translation(translation), Rotation(rotation), Scale(scale)
    { }
    
    STransform(const SMatrix4f& matrix)
    {
        *this = matrix;
    }

    STransform& operator=(const SMatrix4f& matrix)
    {
        Scale.x = glm::length(matrix[0]);
        Scale.y = glm::length(matrix[1]);
        Scale.z = glm::length(matrix[2]);
        
        Rotation = glm::quat_cast(glm::mat3(matrix));

        Translation = matrix[3];
        return *this;
    }
};

class CEntityTransformComponent : public CEntityComponent
{
    STransform m_transform;
public:
    CEntityTransformComponent();

    void SetLocalTransform(const STransform& transform);

    void Move(const SVector3f& vector);
    
    const STransform& GetLocalTransform() const;
    STransform GetWorldTransform() const;
    SMatrix4f GetTransformMatrix(const SVector3f& ViewOrigin = SVector3f(0)) const;
    
    SVector3f GetForwardVector()    const;
    SVector3f GetRightVector()      const;
    SVector3f GetUpVector()         const;
};

#endif