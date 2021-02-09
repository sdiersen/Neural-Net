#include "StdAfx.h"
#include "Values.h"

IMPLEMENT_SERIAL(Values, CObject, 1)

Values::Values(void)
{ 
	values = std::vector<Value>();
	errorMsg = "Invalid Id";
}

Values::Values(const Values& v)
{
	values = v.values;
	errorMsg = v.errorMsg;
}

Values& Values::operator=(const Values& v)
{
	if (&v != this)
	{
		values = v.values;
		errorMsg = v.errorMsg;
	}
	return *this;
}

Values::~Values(void)
{
}

//mutator methods
bool Values::addValue(const std::string& name, double min, double max)
{
	std::vector<Value>::iterator it;
	for (it = values.begin(); it < values. end(); ++it)
	{
		if ((*it).getName() == name)
			return false;
	}

	int id = values.size();
	Value temp(id, name, min, max);

	values.push_back(temp);
	return true;
}

bool Values::changeName(int id, const std::string& name)
{
	int size = values.size() - 1;
	if (id < 0 || id > size)
		return false;

	std::vector<Value>::iterator it;
	for (it = values.begin(); it < values.end(); ++it)
	{
		if ((*it).getId() != id && (*it).getName() == name)
			return false;
	}

	values[id].setName(name);
	return true;
}

bool Values::changeMin(int id, double min)
{
	int size = values.size() - 1;
	if (id < 0 || id > size)
		return false;

	values[id].setMin(min);
	return true;
}

bool Values::changeMax(int id, double max)
{
	int size = values.size() - 1;
	if (id < 0 || id > size)
		return false;

	values[id].setMax(max);
	return true;
}

bool Values::removeValue(int id)
{
	int size = values.size() - 1;
	if (id < 0 || id > size)
		return false;

	int position = 0;
	std::vector<Value>::iterator it;
	for (it = values.begin(); it < values.end(); ++it)
	{
		if ((*it).getId() == id)
			it = values.end();
		++position;
	}
	if (position > size)
		return false;
	values.erase(values.begin() + position);
	return true;
}
//accessor methods
std::string& Values::getName(int id)
{
	int size = values.size() - 1;
	if (id < 0 || id > size)
		return errorMsg;

	return values[id].getName();
}

double Values::getMin(int id)
{
	return values[id].getMin();
}

double Values::getMax(int id)
{
	return values[id].getMax();
}

std::string Values::getNameByIndex(int index)
{
	int size = values.size();
	if (index < 0 || index >= size)
		return "Value Not Found";
	return values[index].getName();
}

double Values::getMinByIndex(int index)
{
	int size = values.size();
	if (index < 0 || index >= size)
		return 0.0;
	return values[index].getMin();
}

double Values::getMaxByIndex(int index)
{
	int size = values.size();
	if (index < 0 || index >= size)
		return 0.0;
	return values[index].getMax();
}

int Values::getId(std::string& name)
{
	std::vector<Value>::iterator it;
	for (it = values.begin(); it < values.end(); ++it)
	{
		if ((*it).getName() == name)
			return (*it).getId();
	}
	return -1;
}


//serializable methods
void Values::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << values.size();

		std::vector<Value>::iterator it;
		for (it = values.begin(); it < values.end(); ++it)
		{
			std::string aName = (*it).getName();
			CString name(aName.c_str());
			ar << (*it).getId() << name << (*it).getMin() << (*it).getMax();
		}
	}
	else
	{
		int size;
		int id;
		CString aName;
		double min;
		double max;

		ar >> size;

		for (int x = 0; x < size; ++x)
		{
			ar >> id >> aName >> min >> max;
			CT2CA s(aName);
			std::string name(s);
			Value temp(id, name, min, max);
			values.push_back(temp);
		}
	}
}
