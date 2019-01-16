#pragma once

#include <string>
#include "Vector2.h"
#include "Size.h"
struct SDL_Texture;

class SDL_Image
{
protected:
	SDL_Texture* m_Texture = nullptr;
	Size m_TextureSize;
	Vector2 m_CellsXY;

public:
	virtual bool Load(const std::string& File);
	virtual void Draw(const Vector2& Location);
	virtual ~SDL_Image();
};
