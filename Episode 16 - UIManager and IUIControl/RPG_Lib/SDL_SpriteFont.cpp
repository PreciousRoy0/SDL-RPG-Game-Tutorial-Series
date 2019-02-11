#include "SDL_SpriteFont.h"
#include "SDL_ScreenHandeler.h"
#include <SDL.h>

#include "AssetManager.h"

bool SDL_SpriteFont::Load(XML* priteFontFile)
{
	if (!priteFontFile)
		return false;

	m_XMLDocument = priteFontFile;

	xml_node<>* rootnode = m_XMLDocument->GetDocument()->first_node("BitmapFont");

	for (xml_attribute<>* at = rootnode->first_attribute(); at; at = at->next_attribute())
	{
		std::string name = at->name();

		if (name == "SpriteSheet")
			m_ImageFile = at->value();
		else if (name == "FontSize")
			m_Size = atoi(at->value());
	}

	if (SDL_Image::Load(m_ImageFile))
		return true;

	for (xml_node<>* n = rootnode->first_node("Letter"); n; n = n->next_sibling())
	{
		char letter = ' ';
		RectangleF rect;

		for (xml_attribute<>* at = n->first_attribute(); at; at = at->next_attribute())
		{
			std::string name = at->name();
			std::string value = at->value();

			if (name == "Char")
				letter = value[0];
			if (name == "X")
				rect.X = (float)atof(value.c_str());
			if (name == "Y")
				rect.Y = (float)atof(value.c_str());
			if (name == "Width")
				rect.Width = (float)atof(value.c_str());
			if (name == "Height")
				rect.Height = (float)atof(value.c_str());
		}

		m_Charecters[letter] = rect;
	}

	return false;
}

bool SDL_SpriteFont::Load(const std::string& XMLFile)
{
	bool res = TheAssetManager::Pointer()->LoadAsset<XML>(XMLFile);
	if (res)
		return true;

	XML* asset = TheAssetManager::Pointer()->GetAsset<XML>(XMLFile);
	res = Load(asset);

	return res;
}

SizeF SDL_SpriteFont::MeasureString(const std::string string)
{
	SizeF res;
	res.Height = m_Charecters[string[0]].Height;

	for (unsigned int i = 0; i < string.size(); i++)
	{
		RectangleF letter = m_Charecters[string[i]];
		res.Width += letter.Width;
	}

	return res;
}

void SDL_SpriteFont::DrawString(const std::string& string, Vector2F location)
{
	float x = 0;

	for (int i = 0; i < (int)string.size(); i++)
	{
		RectangleF source = m_Charecters[string[i]];
		RectangleF destination = source;
		destination.X = location.X + x;
		destination.Y = location.Y;

		SDL_Image::Draw(source, destination);
		x += source.Width;
	}
}


// this clamps the text to the specified rectangle, you might miss the botom and of Right part of your text
// it does not scale down.
void SDL_SpriteFont::DrawString(const std::string& string, RectangleF location)
{
	SizeF textSize = MeasureString(string);

	float x = 0;

	for (int i = 0; i < (int)string.size(); i++)
	{
		RectangleF source = m_Charecters[string[i]];
		RectangleF destination = source;
		destination.X = location.X + x;
		destination.Y = location.Y;

		if (destination.Height > location.Height)
		{
			source.Height = location.Height;
			destination.Height = location.Height;
		}

		if (destination.X <= location.X + location.Width)
		{
			SDL_Image::Draw(source, destination);
		}

		x += source.Width;
	}
}