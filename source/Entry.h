#pragma once
#include <string>

class Entry
{
private:
	std::string name;
	float calories;
	float protein;
public:
	Entry()
		: name{""}, calories{0.0f}, protein{0.0f} {}
	Entry(const std::string &str, const float &cal, const float &p)
		: name{str}, calories{cal}, protein{ p }	{}
	float get_calories() { return calories; }
	float get_protein() { return protein; }
	std::string get_name() { return name; }
};