#include "FileManager.h"

FileManager::FileManager()
{
	fileStream.open(LOG_FILE_PATH, std::fstream::app);
	if (!fileStream.is_open())
	{
		printf("critical error in FileManager.cpp :: failed to open std::fstream\n");
	}
}

FileManager::~FileManager()
{
	fileStream.close();
}


FileManager &FileManager::instance()
{
	static FileManager *instance = new FileManager();
	return *instance;
}


void FileManager::init_buffers(std::vector<Day> &days)
{
	int index = 0;
	std::string line;
	while (std::getline(this->fileStream, line))
	{
		std::stringstream ss(line);
		std::string date;
		ss >> date;
		days.emplace_back(Day(date));

		std::string name;
		PARSE_MODES mode = NAME;
		while (ss >> line)
		{
			float cal, protein, servings;


			switch (mode)
			{ 
			case NAME:
				name = line;
				mode = CAL;
				break; 
			case CAL:
				cal = std::stof(line);
				mode = PROTEIN;
				break;
			case PROTEIN:
				protein = std::stof(line);
//				create and push/emplace objects
				mode = SERVINGS;
				break;
			case SERVINGS:
				servings = std::stof(line);
				days[index].push_entry(Entry(name, cal, protein, servings));
				mode = NAME;
				break;
			}

		}
		index++;
	}
}