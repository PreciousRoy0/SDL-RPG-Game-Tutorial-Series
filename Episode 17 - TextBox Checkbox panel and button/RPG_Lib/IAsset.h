#pragma once

#include <string>

class IAsset
{
public:

	virtual bool Load(const std::string& fileName) = 0;

	virtual ~IAsset() = 0 {};
};
