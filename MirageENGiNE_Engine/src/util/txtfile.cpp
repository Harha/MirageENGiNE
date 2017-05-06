#include "txtfile.h"

// std includes
#include <fstream>

// mirage includes
#include "macros.h"
#include "strutil.h"

namespace mirage
{

	TxtFile::TxtFile(const std::string & filePath) :
		m_filePath(filePath),
		m_lines()
	{
		// Read the file into memory
		std::ifstream file(m_filePath);

		if (file.is_open() == false)
		{
			MLOG_ERROR("TxtFile::TxtFile, error loading file (%s) into memory.", m_filePath.c_str());
			return;
		}

		std::string line;
		while (std::getline(file, line))
		{
			m_lines.push_back(line);
		}

		MLOG_DEBUG("TxtFile::TxtFile, loaded file (%s) into memory. Lines: %zu", m_filePath.c_str(), m_lines.size());
	}

	const std::string TxtFile::getFilePath() const
	{
		return m_filePath;
	}

	std::vector<std::string> TxtFile::getLines() const
	{
		return m_lines;
	}

}