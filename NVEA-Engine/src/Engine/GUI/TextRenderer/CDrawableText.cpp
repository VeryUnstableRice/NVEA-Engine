#include "CDrawableText.h"
#include "glad/glad.h"
#include <iostream>


/*std::shared_ptr<CShader> CDrawableText::m_shader=nullptr;

CDrawableText::CDrawableText()
{
	m_face = NULL;
	m_scale = 1;
	m_rowpadding = 5;
}

void CDrawableText::setScale(float scale)
{
	m_scale = scale;
}

void CDrawableText::setFont(std::string path, int i)
{
	if (!m_shader)
		m_shader = CFileManager::GetShader("./res/DefaultShader/TextShader");
	if (FT_Init_FreeType(&m_ft))
	{
		std::cerr << "[FREETYPE] Could not init FreeType Library!\n";
		return;
	}
	if (FT_New_Face(m_ft, path.c_str(), 0, &m_face))
	{
		std::cerr << "[FREETYPE]No font named: " + path << '\n';
		return;
	}
	FT_Set_Pixel_Sizes(m_face, i, i);

	//std::shared_ptr<CShader> shader = CFileManager::getShader("./res/DefaultShader/TextShader");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (unsigned char i = 0; i < 128; i++)
	{

		if (FT_Load_Char(m_face, i, FT_LOAD_RENDER))
		{
			std::cerr << "[FREETYPE]Failed to load Glyph\n";
			continue;
		}

		SChar chara;

		chara.size = glm::vec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows);
		chara.bearing = glm::vec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top);
		chara.advance = m_face->glyph->advance.x;

		chara.tex = std::make_shared<CTexture>();
		chara.tex->InitData(m_face->glyph->bitmap.buffer, GL_RED, m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows, GL_UNSIGNED_BYTE);
		
		if (m_chars.count(i) == 0)
			m_chars.insert(std::make_pair(i, chara));
		else
			m_chars[i] = chara;
	}
}


//bulk renderer has showed me a big flaw in this code, so I'm thankful for that
void CDrawableText::BulkDraw(class CBulkRenderer* renderer)
{
	glm::vec3 pos = GetPosition();
	float firsty = 0;
	bool needupdate = true;
	for (int i = 0; (size_t)i < m_string.length(); i++)
	{
		if (m_chars.count(m_string[i]) == 0)
			continue;

		glm::vec3 position = GetPosition();
		SChar& chr = m_chars.at(m_string[i]);

		float h = chr.size.y * m_scale;

		if (m_string[i] == '\n')
		{
			glm::vec3 position = GetPosition();
			position.x = pos.x;
			position.y += h + m_rowpadding * m_scale;
			SetPosition(position);
			needupdate = true;
			continue;
		}

		if (!i)
		{
			firsty = h;
			position.y += h;
			SetPosition(position);
		}

		if (needupdate)
			firsty = position.y;

		float ypos = firsty - chr.bearing.y * m_scale;

		float xpos = position.x + chr.bearing.x * m_scale;
		float w = chr.size.x * m_scale;

		if (chr.mesh == nullptr)
		{
			chr.mesh = std::make_shared<CMesh>();

			chr.mesh->Init2DRect(0, 0, w, h);
			chr.mesh->SetShader(m_shader);
			chr.mesh->SetTexture(chr.tex);
		}
		chr.mesh->SetPosition({xpos, ypos, pos.z});
		chr.mesh->BulkDraw(renderer);

		SetPosition(GetPosition() + glm::vec3{ (chr.advance >> 6)* m_scale, 0, 0 });
	}
	SetPosition(pos);
}

void CDrawableText::setRowPadding(float value)
{
	m_rowpadding = value;
}

void CDrawableText::setString(const std::string& text)
{
	m_string = text;
}

/*void CDrawableText::Draw(const SDrawInfo& info)
{ 
	glm::vec3 pos = GetPosition();
	float firsty = 0;
	bool needupdate = true;
	for (int i = 0; (size_t)i < m_string.length(); i++)
	{
		if (m_chars.count(m_string[i]) == 0)
			continue;

		glm::vec3 position = GetPosition();
		SChar chr = m_chars.at(m_string[i]);

		float h = chr.size.y * m_scale;

		if (m_string[i] == '\n')
		{
			glm::vec3 position = GetPosition();
			position.x = pos.x;
			position.y += h + m_rowpadding * m_scale;
			SetPosition(position);
			needupdate = true;
			continue;
		}

		if (i == 0)
		{
			firsty = h;
			position.y += h;
			SetPosition(position);
		}

		if (needupdate)
			firsty = position.y;

		float ypos = firsty - chr.bearing.y * m_scale;

		float xpos = position.x + chr.bearing.x * m_scale;
		float w = chr.size.x * m_scale;

		if (chr.mesh == nullptr)
		{
			chr.mesh = std::make_shared<CMesh>();

			chr.mesh->Init2DRect(xpos, ypos, xpos+w, ypos+h);
			chr.mesh->SetShader(m_shader);
			chr.mesh->SetTexture(chr.tex);
		}
		
		chr.mesh->Draw(info);

		SetPosition(GetPosition() + glm::vec3{ (chr.advance >> 6)* m_scale, 0, 0 });
	}
	SetPosition(pos);
}*/

/*
 text::text() :
	entity()
{
	Im2D(true);
	m_face = NULL;

}

void text::setFont(std::string path, int i)
{

	if (FT_Init_FreeType(&m_ft))
		ShowLog("[FREETYPE] Could not init FreeType Library");
	if (FT_New_Face(m_ft, path.c_str(), 0, &m_face))
		ShowLog("[FREETYPE]No font named: " + path);
	FT_Set_Pixel_Sizes(m_face, 0, i);

	CEObject::Init();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (unsigned char i = 0; i < 128; i++)
	{

		if (FT_Load_Char(m_face, i, FT_LOAD_RENDER))
		{
			ShowLog("[FREETYPE]Failed to load Glyph");
			continue;
		}

		character chara =
		{
			nullptr,
			vector2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
			vector2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
			m_face->glyph->advance.x
		};

		chara.tex = std::make_shared<texture>();
		chara.tex->Init(nullptr, m_face->glyph->bitmap.buffer, GL_RED, m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows);

		if (m_chars.count(i) == 0)
			m_chars.insert(std::make_pair(i, chara));
		else
			m_chars[i] = chara;
	}
}

void text::setString(std::string text)
{
	m_string = text;
}


void text::Draw(drawinfo* info)
{
	entity::Draw(info);
	mesh msh;
	vector3 pos = getPosition();
	float firsty = 0;
	bool needupdate = true;
	for (int i = 0; i < m_string.length(); i++)
	{
		if (m_string[i] == '\n')
		{
			vector3 pp = getPosition();
			pp.x = pos.x;
			pp.y += firsty + 20;
			setPosition(pp);
			needupdate = true;
			continue;
		}
		vector3 position = getPosition();
		if(m_chars.count(i) == 0)
			continue;

		character chr = m_chars.at(m_string[i]);
		float scale = 1.f;
		float xpos = position.x + chr.bearing.x * scale;
		float ypos = position.y - (chr.size.y - chr.bearing.y) * scale;

		float w = chr.size.x * scale;
		float h = chr.size.y * scale;

		if (needupdate)
		{
			firsty = ypos + h;
			needupdate = false;
		}
		else
			ypos = firsty - h;

		msh.Clean();
		std::vector<vertex> m =
		{
			{{xpos, ypos, position.z},{0, 0}},
			{{xpos, ypos+h, position.z},{0,1}},
			{{xpos+w, ypos+h, position.z},{1, 1}},

			{{xpos + w, ypos + h, position.z},{1, 1}},
			{{xpos+w, ypos, position.z},{1, 0}},
			{{xpos, ypos, position.z},{0, 0}},
		};

		msh.Init(m);

		msh.setShader(getShader());
		msh.SetTexture(chr.tex.get());
		msh.Draw(info);
		move({ (chr.advance >> 6) * scale, 0, 0 });
	}
	setPosition(pos);
}

bool text::isText()
{
	return true;
}

std::string text::getShaderPath()
{
	return "./res/defaultshader/textshader";
}
*/
