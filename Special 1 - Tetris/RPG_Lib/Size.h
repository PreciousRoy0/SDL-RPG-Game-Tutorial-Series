#pragma once

struct Size
{
public:
	int Width = 0;
	int Height = 0;

	Size() {}
	Size(int width, int height) { Width = width; Height = height; }
};
