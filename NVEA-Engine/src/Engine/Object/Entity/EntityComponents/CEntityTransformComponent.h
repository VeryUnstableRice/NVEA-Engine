#ifndef CTransformComponent_Header
#define CTransformComponent_Header
#include <assert.h> 
#include <string>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "CEntityComponent.h"

typedef glm::vec3 SVector3f;
typedef glm::vec4 SVector4f;
typedef glm::mat4 SMatrix4f;
typedef glm::mat4 SMatrix3f;

struct SEulerRotation
{
    double Yaw;
    double Pitch;
    double Roll;
    SEulerRotation(double Yaw = 0, double Pitch = 0, double Roll = 0) : Yaw(Yaw), Pitch(Pitch), Roll(Roll) {}
};

struct STransform
{
    SVector3f       Translation;
    SEulerRotation  Rotation;
    SVector3f       Scale;

    SMatrix4f TransformMatrix(const SVector3f& ViewOrigin = SVector3f(0)) const
    {
        const SMatrix4f transform = glm::translate(glm::mat4(1), Translation-ViewOrigin);
        return transform * GetRotationMatrix() * glm::scale(glm::mat4(1), Scale);
    }

    SMatrix3f GetRotationMatrix() const
    {
        SMatrix3f rotation = SMatrix3f(1);
        rotation *= glm::rotate(SMatrix3f(1), glm::radians((float)Rotation.Pitch)  , { 1, 0, 0 }); //pitch
        rotation *= glm::rotate(SMatrix3f(1), glm::radians((float)Rotation.Yaw)    , { 0, 1, 0 }); //yaw
        rotation *= glm::rotate(SMatrix3f(1), glm::radians((float)Rotation.Roll)   , { 0, 0, 1 }); //roll

        return rotation;
    }

    STransform(const SVector3f& translation = SVector3f(0), const SEulerRotation& rotation=SEulerRotation(0), const SVector3f& scale=SVector3f(1)) : Translation(translation), Rotation(rotation), Scale(scale)
    {
        
    }
    
    STransform(const glm::mat4& matrix)
    {
        *this = matrix;
    }

    std::string to_string()
    {
        std::string output = "";
        output += "[" + std::to_string(Translation.x) + " " + std::to_string(Translation.y) + " " + std::to_string(Translation.z) + "] ";
        output += "[" + std::to_string(Rotation.Yaw) + " " + std::to_string(Rotation.Pitch) + " " + std::to_string(Rotation.Roll) + "] ";
        output += "[" + std::to_string(Scale.x) + " " + std::to_string(Scale.y) + " " + std::to_string(Scale.z) + "]";
        return output;
    }

    STransform& operator=(const glm::mat4& matrix)
    {
        Scale.x = glm::length(matrix[0]);
        Scale.y = glm::length(matrix[1]);
        Scale.z = glm::length(matrix[2]);

        glm::mat3 RotationMatrix(matrix);
        SVector3f tempRot = glm::eulerAngles(glm::normalize(glm::quat_cast(RotationMatrix)));
        Rotation.Yaw    = glm::degrees(tempRot.y);
        Rotation.Pitch  = glm::degrees(tempRot.x);
        Rotation.Pitch  = glm::degrees(tempRot.z);
        
        Translation.x = matrix[3][0];
        Translation.y = matrix[3][1];
        Translation.z = matrix[3][2];

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