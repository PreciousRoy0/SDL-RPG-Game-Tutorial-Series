#pragma once
#include "Singleton.h"

#include <string>
#include<functional>
#include <map>

template<class Type>
class TypeFactory : public UnCopyable
{
	std::map<std::string, std::function<Type*(void)>> m_Objects;

	friend class Singleton<TypeFactory>;
	TypeFactory() {}

public:
	template<class T>
	void Register(std::string key)
	{
		m_Objects.insert(std::pair<std::string, std::function<Type*(void)>>(key,
		[]()->Type*
		{
			T* tmp = new T;
			return tmp;
		}));
	}

	Type* Create(std::string key)
	{
		auto a = m_Objects.find(key);
		if (a != m_Objects.end())
			return a->second();
		else
		{
			printf("TypeFactory:Create - Type was not registered: %s", key.c_str());
			throw "Type was not registered";
		}
	}
};