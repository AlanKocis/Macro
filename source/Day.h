#pragma once
#include <vector>
#include "Entry.h"
#include <string>


class Day
{
public:
	std::string date;
	std::vector<Entry> entries;
	size_t num_entries;

	Day(const std::string& date);
	void push_entry(const Entry& entry);
};