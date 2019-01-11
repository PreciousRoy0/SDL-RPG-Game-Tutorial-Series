#pragma once

template<class T>
class SizeT
{

public:
	T Width = 0;
	T Height = 0;

	SizeT() {}
	SizeT(T width, T height) : Width(width), Height(height) {}

	//typecast
	template<class T2>
	operator SizeT<T2>()
	{
		SizeT<T2> res;
		res.Width = (T2)Width;
		res.Height = (T2)Height;
		return res;
	}

	// ==
	template<class T2>
	bool operator == (const SizeT<T2> b)
	{
		return Width == b.Width &&  Height == b.Height;
	}

	// !=
	template<class T2>
	bool operator != (const SizeT<T2> b)
	{
		return Width != b.Width &&  Height != b.Height;
	}

	// +
	template<class T2>
	SizeT operator + (const SizeT<T2> b)
	{
		SizeT<T2> res = *this;
		res.Width += (T2)Width;
		res.Height += (T2)Height;
		return res;
	}

	template<class T2>
	void operator += (const SizeT<T2> b)
	{
		Width += (T)b.Width;
		Height += (T)b.Height;
	}

	// -
	template<class T2>
	SizeT operator - (const SizeT<T2> b)
	{
		SizeT<T2> res = *this;
		res.Width -= (T2)Width;
		res.Height -= (T2)Height;
		return res;
	}

	template<class T2>
	void operator -= (const SizeT<T2> b)
	{
		Width -= (T)b.Width;
		Height -= (T)b.Height;
	}

	// *
	// *=
	
	bool IsZero() const
	{
		return Width == 0 && Height == 0;
	}
};

typedef SizeT<int> Size;
typedef SizeT<float> SizeF;