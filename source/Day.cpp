#include "Day.h"

Day::Day(const std::string &date)
{
	this->date = date;
	this->num_entries = 0;
}

void Day::push_entry(const Entry &entry)
{
	this->entries.emplace_back(entry);
	this->num_entries++;
}
