#include "Day.h"

Day::Day(const std::string &date)
{
	this->date = date;
	this->num_entries = 0;
	this->total_calories = 0;
	this->total_protein = 0;
}

void Day::push_entry(const Entry &entry)
{
	this->total_calories += entry.get_calories() * entry.get_servings();
	this->total_protein += entry.get_protein() * entry.get_servings();
	this->entries.emplace_back(entry);
}
