#ifndef CTEXTUREATLAS_HEADER
#define CTEXTUREATLAS_HEADER
#include "CTexture.h"
#include <array>


class CTextureAtlas : public CTexture
{
	int m_cellsperrow = 0;
public:
	void Init(std::string filePath, int cellsperrow);
	std::array<float, 12> GetFromIndex(int index);
};

#endif
