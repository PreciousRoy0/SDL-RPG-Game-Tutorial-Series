#pragma once

struct Rectangle2d
{
public:
	int X = 0;
	int Y = 0;
	int Width = 0;
	int Height = 0;

	Rectangle2d() {}
	Rectangle2d(int x, int y, int w, int h) { X = x; Y = y, Width = w, Height = h; }
};