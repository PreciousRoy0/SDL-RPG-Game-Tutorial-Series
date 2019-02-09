#include "Color.h"

int ColorFloatToColorByte(float Color)
{
	return (int)(Color * 255);
}

float ColorByteToColorFloat(int Color)
{
	return (1.0f / 255.0f) * (float)Color;
}

Color ColorHexToRGB(std::string hexValue)
{
	Color rgb;
	rgb.R = strtoul(hexValue.substr(1, 2).c_str(), NULL, 16);
	rgb.G = strtoul(hexValue.substr(3, 2).c_str(), NULL, 16);
	rgb.B = strtoul(hexValue.substr(5, 2).c_str(), NULL, 16);

	return rgb;
}