#include "inifile.h"

namespace mirage
{

	const std::regex INI_SECTION("\\[(.*?)\\]");
	const std::regex INI_KEYVALUE("(\\w+)=([^\\+]+(?!\\+{3}))");

	IniFile::IniFile(const std::string & path) :
		m_path(path)
	{
		// Read the file into memory
		std::ifstream file(path);
		std::string line;
		while (std::getline(file, line))
		{
			m_lines.push_back(line);
		}

		// If there is content, continue
		if (m_lines.empty() == false)
		{
			// Hold information about current section
			std::string section;

			// Parse the key-value pairs on each line, in each section
			for (auto & l : m_lines)
			{
				// Trim all extra whitespace
				l.erase(std::unique(l.begin(), l.end(), istwospace), l.end());

				// Leave comments out
				std::string::size_type comment = l.find(";", 0);
				if (comment != std::string::npos)
				{
					l = l.substr(0, comment);
				}

				// Is this line a start for a new section of a keyvalue pair?
				std::smatch match_section;
				if (std::regex_match(l, match_section, INI_SECTION) == true)
				{
					section = match_section.str();
				}
				else
				{
					// Is this a keyvalue pair?
					std::smatch match_keyvalue;
					if (std::regex_match(l, match_keyvalue, INI_KEYVALUE) == true)
					{
						// Get key and value as strings and save them to memory
						std::string key = match_keyvalue.str(1);
						std::string val = match_keyvalue.str(2);

						// Either add this pair to an existing map or create the map if it doesn't exist, [] handles creation
						std::map<std::string, std::string> & section_keyval = m_entries[section];
						section_keyval.insert({ key, val });
					}
				}
			}
		}

		MLOG("IniFile: Loaded " << path << " into memory.  Lines: " << m_lines.size() << ", sections: " << m_entries.size());
	}

	const std::string & IniFile::getString(const std::string & section, const std::string & key, const std::string & defval)
	{
		try
		{
			std::map<std::string, std::string> & section_keyval = m_entries.at(section);
			return section_keyval.at(key);
		}
		catch (const std::exception & e)
		{
			MERR("IniFile: Failed to fetch a string from given section's key. Section: " << section << ", key: " << key << ", exception: " << e.what());
			return defval;
		}
	}

	bool IniFile::getBool(const std::string & section, const std::string & key, const bool defval)
	{
		try
		{
			std::map<std::string, std::string> & section_keyval = m_entries.at(section);
			return strcompcasei(section_keyval.at(key), "true") == true;
		}
		catch (const std::exception & e)
		{
			MERR("IniFile: Failed to fetch a bool from given section's key. Section: " << section << ", key: " << key << ", exception: " << e.what());
			return defval;
		}
	}

	int IniFile::getInt(const std::string & section, const std::string & key, const int defval)
	{
		try
		{
			std::map<std::string, std::string> & section_keyval = m_entries.at(section);
			return std::stoi(section_keyval.at(key));
		}
		catch (const std::exception & e)
		{
			MERR("IniFile: Failed to fetch an int from given section's key. Section: " << section << ", key: " << key << ", exception: " << e.what());
			return defval;
		}
	}

	float IniFile::getFloat(const std::string & section, const std::string & key, const float defval)
	{
		try
		{
			std::map<std::string, std::string> & section_keyval = m_entries.at(section);
			return std::stof(section_keyval.at(key));
		}
		catch (const std::exception & e)
		{
			MERR("IniFile: Failed to fetch a float from given section's key. Section: " << section << ", key: " << key << ", exception: " << e.what());
			return defval;
		}
	}

	double IniFile::getDouble(const std::string & section, const std::string & key, const double defval)
	{
		try
		{
			std::map<std::string, std::string> & section_keyval = m_entries.at(section);
			return std::stod(section_keyval.at(key));
		}
		catch (const std::exception & e)
		{
			MERR("IniFile: Failed to fetch a double from given section's key. Section: " << section << ", key: " << key << ", exception: " << e.what());
			return defval;
		}
	}

	const std::string & IniFile::getPath() const
	{
		return m_path;
	}

	std::vector<std::string> IniFile::getLines() const
	{
		return m_lines;
	}

	std::map<std::string, std::map<std::string, std::string>> IniFile::getEntries() const
	{
		return m_entries;
	}

}