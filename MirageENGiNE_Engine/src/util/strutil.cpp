#include "strutil.h"

// std includes
#include <cstring>
#include <cctype>
#include <algorithm>
#include <functional>

// VC++ Madness
#ifdef _MSC_VER
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif

namespace mirage
{

	bool istwospace(const char lhs, const char rhs) {
		return isspace(lhs) && isspace(rhs);
	}

	bool strcompcasei(const std::string & a, const std::string & b)
	{
		return strncasecmp(a.c_str(), b.c_str(), std::min(a.length(), b.length())) == 0;
	}

	std::string filetofilepath(const std::string & file)
	{
		return file.substr(0, file.find_last_of("/\\")) + "/";
	}

	std::string filetoextension(const std::string & file)
	{
		return file.substr(file.find_last_of(".") + 1);
	}

	void ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(),
			std::not1(std::ptr_fun<int, int>(std::isspace))));
	}

	void rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	}

	void trim(std::string &s) {
		ltrim(s);
		rtrim(s);
	}

}