#pragma once
#include <string>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace rapidxml;

class XML
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
	bool Load(const std::string&);

	virtual ~XML()
	{
		delete mDocument;
		delete xmlFile;
	};
};
