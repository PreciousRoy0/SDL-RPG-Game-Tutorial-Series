#include <string>
#include "XML.h"

bool XML::Load(const std::string& FileLocation)
{
	mFileLocation = FileLocation;
	xmlFile = new rapidxml::file<>(FileLocation.c_str());
	if (!xmlFile)
		return true;

	mDocument = new xml_document<>;
	mDocument->parse<0>(xmlFile->data());

	return false;
}