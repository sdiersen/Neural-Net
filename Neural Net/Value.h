#pragma once

#include <string>

class Value
{
public:
	Value() {}
	Value(int id, const std::string& name, double min, double max)
	{
		this->id = id;
		this->name = name;
		this->min = min;
		this->max = max;
	}
	Value(const Value& v)
	{
		id = v.id;
		name = v.name;
		min = v.min;
		max = v.max;
	}
	Value& operator=(const Value& v)
	{
		if (&v != this)
		{
			id = v.id;
			name = v.name;
			min = v.min;
			max = v.max;
		}
		return *this;
	}
	~Value() {}

	//member variables
private:
	std::string name;
	double min;
	double max;
	int id;

	//public methods
public:
	//inline public methods
	//mutator methods
	void setName(const std::string& name) { this->name = name; }
	void setMin(double min) { this->min = min; }
	void setMax(double max) { this->max = max; }
	void setId(int id) { this->id = id; }

	//accessor methods
	std::string& getName() { return name; }
	double getMin() { return min; }
	double getMax() { return max; }
	int getId() { return id; }
};