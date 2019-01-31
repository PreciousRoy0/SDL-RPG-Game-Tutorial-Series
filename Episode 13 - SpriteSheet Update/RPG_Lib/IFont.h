#pragma once

#include <string>
#include <map>
#include "Rectangle2D.h"

class IFont
{
protected:
	int m_Size = 0;
	std::map<char, RectangleF> m_Charecters;

public:

	virtual void DrawString(std::string string, Vector2 location) = 0;

	virtual ~IFont() = 0 {};
};
