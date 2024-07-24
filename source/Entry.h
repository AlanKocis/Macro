#pragma once
#include <string>
#include <cassert>

class Entry
{
private:
	std::string name;
	float calories;
	float protein;
	float servings;
	bool guiBool = false;
public:
	Entry()
		: name{ "##unique_id" }, calories{ 0.0f }, protein{ 0.0f }, servings{ 0.0f } {}
	Entry(const std::string &str, const float &cal, const float &p, const float &num)
		: name{ str }, calories { cal }, protein{ p }, servings{ num }	{}
	float get_calories() const { return calories; }
	float get_protein() const { return protein; }
	float get_servings() const { return servings; }
	std::string& get_name() { return name; }
	inline void switchGuiBool() { guiBool = !guiBool; }
	void setGuiBool(bool b) { guiBool = b; }
	bool getGuiBool() { return guiBool; }
	

};