#include "CTextureAtlas.h"



void CTextureAtlas::Init(std::string filePath, int cellsperrow)
{
	CTexture::Init(filePath);
	m_cellsperrow = cellsperrow;

/*
	{ {size, size, size}, { 0, 0 }},
	{ {0, size, size},{1, 0} },
	{ {0, 0, size},{1, 1} },

	{ {0, 0, size},{1, 1} },
	{ {size, 0, size},{0, 1} },
	{ {size, size, size},{0, 0} },*/
}

std::array<float, 12> CTextureAtlas::GetFromIndex(int index)
{
	float cellSize = m_cellsperrow/(float)GetWidth();

	int x = index % m_cellsperrow;
	int y = index / m_cellsperrow;
	
	float x0 = cellSize * x;
	float y0 = cellSize * y;

	float x1 = x0 + cellSize;
	float y1 = y0 + cellSize;
	
	std::array<float, 12> output
	{
		x0, y0,
		x1,y0,
		x1, y1,

		x1, y1,
		x0, y1,
		x0, y0
	};
	
	return output;
}