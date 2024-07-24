#pragma once
#include <fstream>
#include <ostream>
#include <string>
#include <sstream>
#include <vector>
#include "Day.h"

#define LOG_FILE_PATH "../../../save.dat"

enum PARSE_MODES
{
	NAME,
	CAL,
	PROTEIN,
	SERVINGS
};

//singleton class
//create a local FileManager = FileManager::instance() to access
class FileManager
{
private:
	std::ifstream fileStream;
	FileManager();
	~FileManager();
public:
	static FileManager &instance();
	void init_buffers(std::vector<Day> &days);
	void writeNewDate(std::string& dateStr);
	void writeFirstDate(std::string &dateStr);
	void write_entry(Entry &entry);
};