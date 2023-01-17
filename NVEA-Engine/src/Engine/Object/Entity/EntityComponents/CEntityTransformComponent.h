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
typedef glm::vec4 SVector4f;
typedef glm::mat4 SMatrix4f;
typedef glm::mat4 SMatrix3f;

struct SEulerRotator
{
    double Yaw;
    double Pitch;
    double Roll;
    SEulerRotator(double Yaw = 0, double Pitch = 0, double Roll = 0) : Yaw(Yaw), Pitch(Pitch), Roll(Roll) {}
};

using SQuaternionRotator = glm::quat;

inline SEulerRotator ToEuler(const SQuaternionRotator& Quat)
{
    SEulerRotator rotator;
    SQuaternionRotator q = glm::normalize(Quat);
    // roll (x-axis rotation)
    double sinr_cosp = 2.0 * (q.w * q.x + q.y * q.z);
    double cosr_cosp = 1.0 - 2.0 * (q.x * q.x + q.y * q.y);
    rotator.Yaw = std::atan2(sinr_cosp, cosr_cosp) * 180.0/M_PI;

    // pitch (y-axis rotation)
    double sinp = std::sqrt(1.0 + 2.0 * (q.w * q.y - q.x * q.z));
    double cosp = std::sqrt(1.0 - 2.0 * (q.w * q.y - q.x * q.z));
    rotator.Pitch =( 2.0 * std::atan2(sinp, cosp) - M_PI / 2.0)* 180.0/M_PI;

    // yaw (z-axis rotation)
    double siny_cosp = 2.0 * (q.w * q.z + q.x * q.y);
    double cosy_cosp = 1.0 - 2.0 * (q.y * q.y + q.z * q.z);
    rotator.Roll = std::atan2(siny_cosp, cosy_cosp)* 180.0/M_PI;

    return rotator;
}

inline SQuaternionRotator ToQuaternions(const SEulerRotator& euler)
{
    SQuaternionRotator quat;
    double yawRad      = euler.Yaw     * M_PI / 180.0;
    double pitchRad     = euler.Pitch    * M_PI / 180.0;
    double rollRad       = euler.Roll      * M_PI / 180.0;

    double yawCos = std::cos(yawRad*0.5);
    double yawSin = std::sin(yawRad*0.5);

    double pitchCos = std::cos(pitchRad*0.5);
    double pitchSin = std::sin(pitchRad*0.5);

    double rollCos = std::cos(rollRad*0.5);
    double rollSin = std::sin(rollRad*0.5);
    
    quat.w = yawCos * pitchCos * rollCos + yawSin * pitchSin * rollSin;
    quat.x = yawSin * pitchCos * rollCos - yawCos * pitchSin * rollSin;
    quat.y = yawCos * pitchSin * rollCos + yawSin * pitchCos * rollSin;
    quat.z = yawCos * pitchCos * rollSin - yawSin * pitchSin * rollCos;
    return quat;
}

inline SMatrix4f QuatToMatrix(const SQuaternionRotator& quat)
{
    SMatrix4f R(1);
    double w = quat.w;
    double x = quat.x;
    double y = quat.y;
    double z = quat.z;
    
    R[0][0] = 1 - 2*y*y - 2*z*z;
    R[0][1] = 2*x*y - 2*w*z;
    R[0][2] = 2*x*z + 2*w*y;

    R[1][0] = 2*x*y + 2*w*z;
    R[1][1] = 1 - 2*x*x - 2*z*z;
    R[1][2] = 2*y*z - 2*w*x;

    R[2][0] = 2*x*z - 2*w*y;
    R[2][1] = 2*y*z + 2*w*x;
    R[2][2] = 1 - 2*x*x - 2*y*y;

    return R;
}

struct STransform
{
    SVector3f           Translation;
    SQuaternionRotator  Rotation;
    SVector3f           Scale;

    SMatrix4f TransformMatrix(const SVector3f& ViewOrigin = SVector3f(0)) const
    {
        const SMatrix4f transform = glm::translate(glm::mat4(1), Translation-ViewOrigin);
        return transform * GetRotationMatrix() * glm::scale(glm::mat4(1), Scale);
    }

    SMatrix3f GetRotationMatrix() const
    {
        return glm::mat4_cast(Rotation);
    }

    STransform(const SVector3f& translation = SVector3f(0), const SQuaternionRotator& rotation=SQuaternionRotator(), const SVector3f& scale=SVector3f(1)) : Translation(translation), Rotation(rotation), Scale(scale)
    {
        
    }
    
    STransform(const glm::mat4& matrix)
    {
        *this = matrix;
    }

    STransform& operator=(const glm::mat4& matrix)
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