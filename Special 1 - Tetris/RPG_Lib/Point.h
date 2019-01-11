#pragma once

template <class T>
class PointT
{

public:
	T X = 0;
	T Y = 0;

	PointT() {}
	PointT(T x, T y) { X = x; Y = y; }

	template<class TT>
	PointT(const PointT<TT>& b)
	{
		X = (T)b.X;
		Y = (T)b.Y;
	}

	PointT& operator + (const PointT& b)
	{
		X += b.X;
		Y += b.Y;

		return *this;
	}

	bool operator == (const PointT& b) const
	{
		return X == b.X && Y == b.Y;
	}
};

typedef PointT<int> Point;
typedef PointT<float> PointF;