#include "SDL_Image.h"

#include <SDL.h>
#include <SDL_image.h>

#include "SDL_ScreenHandeler.h"

bool SDL_Image::Load(const std::string& File)
{
	// load our image
	m_Texture = IMG_LoadTexture(TheSDLScreenHandeler::Pointer()->GetRenderer(), File.c_str());
	if (!m_Texture)
	{
		printf("SDL_image load failed: %s\n", SDL_GetError());
		return true;
	}

	// get the width and height of the texture
	SDL_QueryTexture(m_Texture, NULL, NULL, &m_TextureSize.Width, &m_TextureSize.Height);

	return false;
}

void SDL_Image::Draw(const Vector2F& Location)
{
	SDL_Rect destination
	{
		destination.x = (int)Location.X,
		destination.y = (int)Location.Y,
		destination.w = m_TextureSize.Width,
		destination.h = m_TextureSize.Height,
	};

	SDL_RenderCopy(TheSDLScreenHandeler::Pointer()->GetRenderer(),
		m_Texture,
		NULL,
		&destination);
}

void SDL_Image::Draw(const RectangleF& Source, const RectangleF& Destination)
{
	SDL_Rect source
	{
		(int)Source.X,
		(int)Source.Y,
		(int)Source.Width,
		(int)Source.Height
	};

	SDL_Rect destenation
	{
		(int)Destination.X,
		(int)Destination.Y,
		(int)Destination.Width,
		(int)Destination.Height
	};

	SDL_RenderCopy(TheSDLScreenHandeler::Pointer()->GetRenderer(), m_Texture, &source, &destenation);
}

SDL_Image::~SDL_Image()
{
	if (m_Texture)
		SDL_DestroyTexture(m_Texture);
}
