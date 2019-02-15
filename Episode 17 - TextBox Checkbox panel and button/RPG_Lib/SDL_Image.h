#pragma once

#include <string>
#include "Vector2.h"
#include "Rectangle2D.h"
#include "Size.h"
#include "IAsset.h"
struct SDL_Texture;

class SDL_Image : public IAsset
{
protected:
	SDL_Texture* m_Texture = nullptr;
	Size m_TextureSize;
	Vector2 m_CellsXY;

public:
	virtual bool Load(const std::string& fileName) override;
	virtual void Draw(const Vector2F& Location);
	virtual void Draw(const RectangleF& Source, const RectangleF& Destination);
	virtual ~SDL_Image();
};
