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
	float total_calories;
	float total_protein;

	Day(const std::string& date);
	float get_total_calories() const { return total_calories; }
	float get_total_protein() const { return total_protein; }
	void push_entry(const Entry& entry);
};