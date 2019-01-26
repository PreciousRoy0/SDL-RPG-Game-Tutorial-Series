#pragma once
#include "Singleton.h"

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
		m_Objects.insert(std::pair <std::string, std::function<Type*(void)>>(key, []()->Type*
		{
			T* temp = new T();
			return temp;
		}));
	}

	Type* Create(std::string key)
	{
		auto a = m_Objects.find(key);
		if (a == m_Objects.end()) //had i here
		{
			printf("Type was not registered: %s", key.c_str());
			throw "Type was not registered";
		}
		else
			return a->second();
	}

};