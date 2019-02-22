#include "SDL_SpriteSheet.h"

#include "SDL_ScreenHandeler.h"
#include <SDL.h>

#include "AssetManager.h"

bool SDL_SpriteSheet::Load(XML* priteFontFile)
{
	if (!priteFontFile)
		return false;

	m_XMLDocument = priteFontFile;
	std::string imageFile;

	xml_node<>* rootnode = m_XMLDocument->GetDocument()->first_node("TextureAtlas");

	for (xml_attribute<>* at = rootnode->first_attribute(); at; at = at->next_attribute())
	{
		std::string name = at->name();

		if (name == "imagePath")
			imageFile = at->value();
	}

	if (SDL_Image::Load(imageFile))
		return true;

	for (xml_node<>* n = rootnode->first_node("SubTexture"); n; n = n->next_sibling())
	{
		std::string name;
		RectangleF rect;

		for (xml_attribute<>* at = n->first_attribute(); at; at = at->next_attribute())
		{
			std::string n = at->name();
			std::string v = at->value();

			if (n == "name")
				name = v;
			if (n == "x")
				rect.X = (float)atof(v.c_str());
			if (n == "y")
				rect.Y = (float)atof(v.c_str());
			if (n == "width")
				rect.Width = (float)atof(v.c_str());
			if (n == "height")
				rect.Height = (float)atof(v.c_str());
		}

		m_Sprites[name] = rect;
	}

	return false;
}

bool SDL_SpriteSheet::Load(const std::string& XMLFile)
{
	bool res = TheAssetManager::Pointer()->LoadAsset<XML>(XMLFile);
	if (res)
		return true;

	XML* asset = TheAssetManager::Pointer()->GetAsset<XML>(XMLFile);
	res = Load(asset);

	return res;
}

void SDL_SpriteSheet::Draw(const std::string& sprite, const Vector2& location)
{
		RectangleF spr = m_Sprites[sprite];
		SDL_Rect source
		{
			(int)spr.X,
			(int)spr.Y,
			(int)spr.Width,
			(int)spr.Height
		};

		SDL_Rect destination
		{
			(int)location.X,
			(int)location.Y,
			source.w,
			source.h
		};

		SDL_RenderCopy(TheSDLScreenHandeler::Pointer()->GetRenderer(),
			m_Texture,
			&source,
			&destination);
}
