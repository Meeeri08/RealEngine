#include "ModuleFile.h"

ModuleFile::~ModuleFile()
{
}

bool ModuleFile::AddPath(const char* path)
{
	return false;
}

void ModuleFile::GetNameFromPath(const char* full_path, std::string* path, std::string* file, std::string* fileWithExtension, std::string* extension) const
{
	if (full_path != nullptr)
	{
		std::string nwFullPath = full_path;
		for (std::string::iterator charIterator = nwFullPath.begin(); charIterator != nwFullPath.end(); ++charIterator)
		{
			if (*charIterator == '\\')
				*charIterator = '/';
		}
		size_t posSlash = nwFullPath.find_last_of("\\/");
		size_t posDot = nwFullPath.find_last_of(".");

		if (path != nullptr)
		{
			if (posSlash < nwFullPath.length())
				*path = nwFullPath.substr(0, posSlash + 1);
			else
				path->clear();
		}
		if (fileWithExtension != nullptr) {
			if (posSlash < nwFullPath.length()) {
				*fileWithExtension = nwFullPath.substr(posSlash + 1);
			}
			else
				*fileWithExtension = nwFullPath;
		}

		if (file != nullptr)
		{
			nwFullPath = nwFullPath.substr(0, posDot);
			posSlash = nwFullPath.find_last_of("\\/");
			*file = nwFullPath.substr(posSlash + 1);

		}

		if (extension != nullptr)
		{
			if (posDot < nwFullPath.length())
				*extension = nwFullPath.substr(posDot);
			else
				extension->clear();
		}
	}
}


