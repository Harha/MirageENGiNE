#ifndef STRUTIL_H
#define STRUTIL_H

// std includes
#include <string>

#ifdef _MSC_VER 
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif

namespace mirage
{

	// ---------------------------------------------------------------------------
	// istwospace
	// Comparator for finding extra whitespace in a string
	// ---------------------------------------------------------------------------
	extern bool istwospace(const char lhs, const char rhs);

	// ---------------------------------------------------------------------------
	// strcompcasei
	// Compares two std::strings, case insensitive
	// ---------------------------------------------------------------------------
	extern bool strcompcasei(const std::string & a, const std::string & b);

	// ---------------------------------------------------------------------------
	// cstr2int
	// Converts a C type string to integer
	// ---------------------------------------------------------------------------
	extern constexpr unsigned int cstr2int(const char * str, int h = 0)
	{
		return !str[h] ? 5381 : (cstr2int(str, h + 1) * 33) ^ str[h];
	}

	// ---------------------------------------------------------------------------
	// filetofilepath
	// Converts a filepath ending to a file into a path to the folder of the file
	// ---------------------------------------------------------------------------
	extern std::string filetofilepath(const std::string & file);

	// ---------------------------------------------------------------------------
	// filetoextension
	// Converts a filepath ending to a file into the file extension
	// ---------------------------------------------------------------------------
	extern std::string filetoextension(const std::string & file);

	// ---------------------------------------------------------------------------
	// ltrim
	// Trim from start (in place)
	// ---------------------------------------------------------------------------
	extern inline void ltrim(std::string &s);

	// ---------------------------------------------------------------------------
	// rtrim
	// Trim from end (in place)
	// ---------------------------------------------------------------------------
	extern inline void rtrim(std::string &s);

	// ---------------------------------------------------------------------------
	// trim
	// Trim from both ends (in place)
	// ---------------------------------------------------------------------------
	extern inline void trim(std::string &s);

}

#endif // STRUTIL_H