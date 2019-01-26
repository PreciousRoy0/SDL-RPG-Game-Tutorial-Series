#pragma once
#include <string>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "IAsset.h"

using namespace rapidxml;

class XML: public IAsset
{
protected:
	file<char>* xmlFile;
	xml_document<>* mDocument;
	std::string mFileLocation;

public:
	std::string& GetFileLocation() { return mFileLocation; }

	xml_document<>* GetDocument() const
	{
		return mDocument;
	}
	virtual bool Load(const std::string&) override;

	virtual ~XML()
	{
		delete mDocument;
		delete xmlFile;
	};
};
