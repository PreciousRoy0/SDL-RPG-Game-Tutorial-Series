#pragma once

#include "UnCopyable.h"

template <class T>
class Singleton
{
public:
	static T* Pointer()
	{
		static T t;
		return &t;
	}
};
