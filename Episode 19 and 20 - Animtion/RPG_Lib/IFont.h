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

	virtual SizeF MeasureString(const std::string text) = 0;
	virtual void DrawString(const std::string& string, Vector2F location) = 0;
	virtual void DrawString(const std::string& string, RectangleF location) = 0;

	virtual ~IFont() = 0 {};
};
