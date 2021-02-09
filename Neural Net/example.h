#pragma once

#include <string>
#include <vector>

class Example
{
public:
	Example(void) {}
	Example(int id, const std::vector<double>& atts, const std::vector<double>& vals)
	{
		this->id = id;
		attributes = atts;
		values = vals;
		normalized_attributes = std::vector<double>();
		normalized_values = std::vector<double>();
	}
	Example(const Example& e)
	{
		id = e.id;
		attributes = e.attributes;
		normalized_attributes = e.normalized_attributes;
		values = e.values;
		normalized_values = e.normalized_values;
	}
	Example& operator=(const Example& e)
	{
		if (&e != this)
		{
			id = e.id;
			attributes = e.attributes;
			normalized_attributes = e.normalized_attributes;
			values = e.values;
			normalized_values = e.normalized_values;
		}
		return *this;
	}
	~Example(void) {}

	//member variables
private:
	int id;
	std::vector<double> attributes;
	std::vector<double> normalized_attributes;
	std::vector<double> values;
	std::vector<double> normalized_values;

	//public methods
public:
	//mutator methods
	void setId(int id) { this->id = id; }
	void setAttributes(const std::vector<double>& atts) { attributes = atts; }
	void setNormalizedAttributes(const std::vector<double>& atts) { normalized_attributes = atts; }
	void setValues(const std::vector<double>& vals) { values = vals; }
	void setNormalizedValues(const std::vector<double>& vals) { normalized_values = vals; }
	void setNormalized(const std::vector<double>& atts, const std::vector<double>& vals)
	{
		normalized_attributes = atts;
		normalized_values = vals;
	}

	//accessor methods
	int getId() { return id; }
	std::vector<double>& getAttributes(std::vector<double>& atts)
	{
		atts = attributes;
		return atts;
	}
	std::vector<double>& getNormalizedAttributes(std::vector<double>& atts)
	{
		atts = normalized_attributes;
		return atts;
	}
	std::vector<double>& getValues(std::vector<double>& vals)
	{
		vals = values;
		return vals;
	}
	std::vector<double>& getNormalizedValues(std::vector<double>& vals)
	{
		vals = normalized_values;
		return vals;
	}

	double getAttribute(int id)
	{
		int size = attributes.size();
		if (id >= 0 && id < size)
			return attributes[id];
		return 0.0;
	}

	double getNormalizedAttribute(int id)
	{
		int size = attributes.size();
		if (id >= 0 && id < size)
			return normalized_attributes[id];
		return 0.0;
	}

	double getValue(int id)
	{
		int size = values.size();
		if (id >= 0 && id < size)
			return values[id];
		return 0.0;
	}

	double getNormalizedValue(int id)
	{
		int size = normalized_values.size();
		if (id >= 0 && id < size)
			return normalized_values[id];
		return 0.0;
	}
};