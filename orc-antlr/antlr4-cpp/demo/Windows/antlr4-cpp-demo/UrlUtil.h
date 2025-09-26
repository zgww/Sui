#pragma once
#include <string>
class UrlUtil
{public:
	static std::string absPath_toFileUri(std::string abspath);
};

std::string encodeURI(std::string in);
std::string encodeURIComponent(std::string in);

std::string decodeURIComponent(std::string in);

std::string fileUri_toAbsPath(std::string path);
