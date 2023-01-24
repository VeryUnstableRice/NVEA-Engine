#ifndef CMeshRenderEntity_Header
#define CMeshRenderEntity_Header

#include <memory>

#include "Engine/Object/Entity/CEntity.h"
#include <glad/glad.h>

enum class ERenderType : std::uint8_t 
{
    TRIANGLES
};

class CMeshRenderEntity : public CEntity
{
    CWeakObjectPtr<class CShader        > m_shader = nullptr;
    CWeakObjectPtr<class CTexture       > m_texture = nullptr;
    CWeakObjectPtr<class CAbstractMesh  > m_mesh = nullptr;
    EngineMath::SVector4f m_color = {1.f, 1.f, 1.f, 1.f};
    std::int16_t m_priority = 0;
    bool m_wireframe = false;
    ERenderType m_type;
public:
    CMeshRenderEntity();
    
    void SetRenderPriority(std::uint16_t Priority)  { m_priority    = Priority;     }
    void SetColor(const EngineMath::SVector4f& Color)           { m_color       = Color;        }
    void SetShader(CShader* Shader)                 { m_shader      = Shader;       }
    void SetTexture(CTexture* Texture)              { m_texture     = Texture;      }
    void SetMesh(CAbstractMesh* Mesh)               { m_mesh        = Mesh;         }
    void SetWireframe(bool wireframe)               { m_wireframe   = wireframe;    }
    void SetRenderType(ERenderType renderType)      { m_type        = renderType;   }
    
    const EngineMath::SVector4f& GetColor()         const { return m_color;           }
    CTexture* GetTexture()              const { return m_texture.get();   }
    CShader* GetShader()                const { return m_shader.get();    }
    CAbstractMesh* GetMesh()            const { return m_mesh.get();      }
    int GetRenderPriority()             const { return m_priority;        }
    bool GetWireframe()                 const { return m_wireframe;       }
    ERenderType GetRenderType()         const { return m_type;            }


    void OnConstruct() override;
    void OnDestroy() override;
};

#endif