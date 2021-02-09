#pragma once

#include <vector>
#include "Value.h"

class Values : public CObject
{

DECLARE_SERIAL(Values)

public:
	Values(void);
	Values(const Values& v);
	Values& operator=(const Values& v);
	~Values(void);

	//private variables
private:
	std::vector<Value> values;
	std::string errorMsg;

	//public methods
public:
	//mutator methods
	bool addValue(const std::string& name, double min, double max);
	bool changeName(int id, const std::string& name);
	bool changeMin(int id, double min);
	bool changeMax(int id, double max);
	bool removeValue(int id);
	void clear() { values.clear(); }

	//accessor methods
	std::string& getName(int id);
	double getMin(int id);
	double getMax(int id);
	std::string getNameByIndex(int index);
	double getMinByIndex(int index);
	double getMaxByIndex(int index);
	int getCount() { return values.size(); }
	int getId(std::string& name);

	//serializable methods
	void Serialize(CArchive& ar);
};

