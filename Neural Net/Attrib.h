#pragma once

#include <string>

class Attrib
{
public:
	Attrib(void) {}
	Attrib(int id, const std::string& name, double min, double max, double fri = 1.0)
	{
		this->id = id;
		this->name = name;
		this->min = min;
		this->max = max;
		this->fri = fri;
	}
	Attrib(const Attrib& a)
	{
		name = a.name;
		min = a.min;
		max = a.max;
		fri = a.fri;
		id = a.id;
	}
	Attrib& operator=(const Attrib& a)
	{
		if (&a != this)
		{
			name = a.name;
			min = a.min;
			max = a.max;
			fri = a.fri;
			id = a.id;
		}
		return *this;
	}
	~Attrib(void){}

	//member variables
private:
	std::string name;
	double min;
	double max;
	double fri; //feature relavent importance value
	int id;

	//public methods
public:
	//inline public methods
	//mutator methods
	void setName(const std::string& name) { this->name = name; }
	void setMin(double min) { this->min = min; }
	void setMax(double max) { this->max = max; }
	void setFri(double fri) { this->fri = fri; }
	void setId(int id) { this->id = id; }

	//accessor methods
	std::string& getName() { return name; }
	double getMin() { return min; }
	double getMax() { return max; }
	double getFri() { return fri; }
	int getId() { return id; }

};