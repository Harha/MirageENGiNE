#ifndef TXTFILE_H
#define TXTFILE_H

// std includes
#include <string>
#include <vector>

namespace mirage
{

	class TxtFile
	{
	public:
		TxtFile(const std::string & filePath);
		const std::string getFilePath() const;
		std::vector<std::string> getLines() const;
	private:
		std::string m_filePath;
		std::vector<std::string> m_lines;
	};

}

#endif // TXTFILE_H