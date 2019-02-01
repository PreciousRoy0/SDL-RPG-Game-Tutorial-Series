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

void SDL_Image::Draw(const Vector2 & Location)
{
	SDL_Rect destination; 
	destination.x = Location.X;
	destination.y = Location.Y;
	destination.w = m_TextureSize.Width;
	destination.h = m_TextureSize.Height;

	SDL_RenderCopy(TheSDLScreenHandeler::Pointer()->GetRenderer(),
		m_Texture,
		NULL,
		&destination);
}

SDL_Image::~SDL_Image()
{
	if(m_Texture)
		SDL_DestroyTexture(m_Texture);
}
