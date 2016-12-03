#ifndef INIFILE_H
#define INIFILE_H

// std includes
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <regex>

// mirage includes
#include "../macros.h"
#include "strutil.h"

namespace mirage
{

	extern const std::regex INI_SECTION;
	extern const std::regex INI_KEYVALUE;

	class IniFile
	{
	public:
		IniFile(const std::string & filePath);
		const std::string & getString(const std::string & section, const std::string & key, const std::string & defval = "");
		bool getBool(const std::string & section, const std::string & key, const bool defval = false);
		int getInt(const std::string & section, const std::string & key, const int defval = -1);
		float getFloat(const std::string & section, const std::string & key, const float defval = -1);
		double getDouble(const std::string & section, const std::string & key, const double defval = -1);
		const std::string & getFilePath() const;
		std::vector<std::string> getLines() const;
		std::map<std::string, std::map<std::string, std::string>> getEntries() const;
	private:
		std::string m_filePath;
		std::vector<std::string> m_lines;
		std::map<std::string, std::map<std::string, std::string>> m_entries;
	};

}

#endif // INIFILE_H