#pragma once
#include <string>

class Color
{
public:
	int R = 0;
	int G = 0;
	int B = 0;
	int A = 0;

	Color(int r = 0, int g = 0, int b = 0, int a = 255) : R(r), G(g), B(b), A(a) {}

	friend bool operator == (const Color& a, const Color& b) //const
	{
		if (a.A != b.A || a.B != b.B || a.G != b.G || a.R != a.R)
			return false;
		else
			return true;
	}
};

int ColorFloatToColorByte(float Color);
float ColorByteToColorFloat(int Color);
Color ColorHexToRGB(std::string hexValue);

#define Colour Color;