#ifndef CDRAWABLETEXT_HEADER
#define CDRAWABLETEXT_HEADER
#include <glm/vec2.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H //"freetype/freetype.h"
#include <memory>
#include <string>
#include <map>

#include "Engine/RenderingObjects/CShader.h"
#include "Engine/RenderingObjects/CTexture.h"
#include "Engine/Object/CObject.h"

/*struct SChar
{
	std::shared_ptr<CTexture> tex = nullptr;
	std::shared_ptr <CMesh> mesh = nullptr;
	glm::vec2 size;
	glm::vec2 bearing;
	int advance;
};

class CDrawableText : public CObject
{
	glm::vec2 m_color;
	float m_scale, m_rowpadding;
	FT_Library m_ft;
	FT_Face m_face;
	
	std::string m_string;
	static std::shared_ptr<CShader> m_shader;
	std::map<unsigned char, SChar> m_chars;
public:
	CDrawableText();
	void setScale(float scale);
	void setFont(std::string path, int i);
	void setRowPadding(float value);
	void setString(const std::string& text);
	void BulkDraw(class CBulkRenderer* renderer);
};
*/
#endif
