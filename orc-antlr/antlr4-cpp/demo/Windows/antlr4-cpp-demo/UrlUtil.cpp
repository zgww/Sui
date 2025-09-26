#include "UrlUtil.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <format>
#include "FsUtil.h"

std::string encodeURI(std::string in)
{
	std::stringstream ssUri;
	for (char c : in)
	{
		//0-9A-Za-z-_.!~*'()
		if ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9')
			|| c == '!'
			|| (c >= '\'' && c <= '*')
			|| c == '-'
			|| c == '.'
			|| c == '_'
			|| c == '/'
			|| c == '~')
		{
			ssUri << c;
		}
		else
		{
			ssUri << "%";
			if ((c & 0xf0) == 0)
				ssUri << 0;
			ssUri << std::setiosflags(std::ios::uppercase) << std::hex << (c & 0xff);
		}
	}
	return ssUri.str();
}
/**
 * uri�����ַ���.
 *
 * \param in ������utf-8����ģ�
 * \return uri�������ַ�����
 */
std::string encodeURIComponent(std::string in)
{
	std::stringstream ssUri;
	for (char c : in)
	{
		//0-9A-Za-z-_.!~*'()
		if ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9')
			|| c == '!'
			|| (c >= '\'' && c <= '*')
			|| c == '-'
			|| c == '.'
			|| c == '_'
			|| c == '~')
		{
			ssUri << c;
		}
		else
		{
			ssUri << "%";
			if ((c & 0xf0) == 0)
				ssUri << 0;
			ssUri << std::setiosflags(std::ios::uppercase) << std::hex << (c & 0xff);
		}
	}
	return ssUri.str();
}

/**
 * URI����.
 *
 * \param in    URI������ַ�����
 * \return  �������ַ�������utf-8����ġ�
 */
std::string decodeURIComponent(std::string in)
{
	int               readFlag = 0;
	int               code = 0;
	std::stringstream ssUri;
	for (char c : in)
	{
		if ((readFlag == 0) && (c == '%'))
		{
			readFlag = 1;
			continue;
		}
		else if (readFlag == 1)
		{
			if (isxdigit(c))
			{
				if (isdigit(c))
					code = c - '0';
				else if (c >= 'A' && c <= 'F')
					code = (0x0a + (c - 'A'));
				else
					return std::string();
				readFlag = 2;
				continue;
			}
			else
			{
				return std::string();
			}
		}
		else if (readFlag == 2)
		{
			if (isxdigit(c))
			{
				code <<= 4;
				if (isdigit(c))
					code |= (c - '0');
				else if (c >= 'A' && c <= 'F')
					code |= (0x0a + (c - 'A'));
				else
					return std::string();
				ssUri << (char)(code & 0xff);
				code = 0;
				readFlag = 0;
				continue;
			}
			else
			{
				return std::string();
			}
		}
		else
		{
			ssUri << c;
		}
	}
	return ssUri.str();
}


// file:///a:/xx תΪ  a:/xx   file:///a/b => /a/b
std::string fileUri_toAbsPath(std::string path) {
	path = decodeURIComponent(path);
	if (path.size() > 9 && path.starts_with("file:///") && path[9] == ':') {
		if (path.size() > 9 && path[9] == ':') { //windows
			return path.substr(8);
		}
		return path.substr(7); //linux
	}
	return path;
}

std::string UrlUtil::absPath_toFileUri(std::string abspath)
{
	//windows���̷� /c:
	if (abspath.size() >= 3 && abspath[0] == '/' && abspath[2] == ':') {
		Path p(abspath);
		auto tmpp = p.normal().eliminateDotDir().path();
		tmpp = encodeURI(tmpp);
		return std::format("file://{}", tmpp);
	}

	//windows���̷� c:
	if (abspath.size() >= 2 && abspath[1] == ':') {
		Path p(abspath);
		auto tmpp = p.normal().eliminateDotDir().path();
		tmpp = encodeURI(tmpp);
		return std::format("file:///{}", tmpp);
	}
	return std::format("file://{}", abspath);
}
