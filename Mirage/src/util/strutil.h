#ifndef STRUTIL_H
#define STRUTIL_H

// std includes
#include <string>
#include <cstring>
#include <algorithm>

#ifdef _MSC_VER 
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif

namespace mirage
{

	// ---------------------------------------------------------------------------
	// istwospace
	// Comparator for finding extra whitespace in a string.
	// ---------------------------------------------------------------------------
	inline bool istwospace(const char lhs, const char rhs) {
		return isspace(lhs) && isspace(rhs);
	}

	// ---------------------------------------------------------------------------
	// strcompcasei
	// Compares two std::strings, case insensitive.
	// ---------------------------------------------------------------------------
	inline bool strcompcasei(const std::string & a, const std::string & b)
	{
		return strncasecmp(a.c_str(), b.c_str(), std::min(a.length(), b.length())) == 0;
	}

	// ---------------------------------------------------------------------------
	// cstr2int
	// Converts a C type string to integer.
	// ---------------------------------------------------------------------------
	constexpr unsigned int cstr2int(const char* str, int h = 0)
	{
		return !str[h] ? 5381 : (cstr2int(str, h + 1) * 33) ^ str[h];
	}

}

#endif // STRUTIL_H