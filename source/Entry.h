#pragma once
#include <string>

class Entry
{
private:
	std::string name;
	float calories;
	float protein;
	float servings;
public:
	Entry()
		: name{ "" }, calories{ 0.0f }, protein{ 0.0f }, servings{ 0.0f } {}
	Entry(const std::string &str, const float &cal, const float &p, const float& num)
		: name{ str }, calories{ cal }, protein{ p }, servings{ num } {}
	float get_calories() { return calories; }
	float get_protein() { return protein; }
	float get_servings() { return servings; }
	std::string get_name() { return name; }
};