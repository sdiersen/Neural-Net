#include "StdAfx.h"
#include "Attribs.h"

IMPLEMENT_SERIAL(Attribs, CObject, 1)

Attribs::Attribs(void)
{
	attributes = std::vector<Attrib>();
	errorMsg = "Invalid Id";
}

Attribs::Attribs(const Attribs& a)
{
	attributes = a.attributes;
	errorMsg = a.errorMsg;
}

Attribs& Attribs::operator=(const Attribs& a)
{
	if (&a != this)
	{
		attributes = a.attributes;
		errorMsg = a.errorMsg;
	}
	return *this;
}

Attribs::~Attribs(void)
{
}


//mutator methods
bool Attribs::addAttribute(const std::string& name, double min, double max, double fri)
{
	std::vector<Attrib>::iterator it;
	for (it = attributes.begin(); it < attributes.end(); ++it)
	{
		if ((*it).getName() == name)
			return false;
	}
	
	int id = attributes.size();
	Attrib temp(id, name, min, max, fri);
	
	attributes.push_back(temp);
	
	return true;
}

bool Attribs::changeName(int id, const std::string& newName)
{
	//make sure it is a valid id
	int size = attributes.size() - 1;
	if (id < 0 || id > size)
		return false;
	
	//make sure the new name is not already the name of an attribute
	std::vector<Attrib>::iterator it;
	for (it = attributes.begin(); it < attributes.end(); ++it)
	{
		if ((*it).getId() != id && (*it).getName() == newName)
			return false;
	}

	attributes[id].setName(newName);
	return true;
}

bool Attribs::changeMin(int id, double min)
{
	//make sure id is a valid id
	int size = attributes.size() - 1;
	if (id < 0 || id > size)
		return false;

	attributes[id].setMin(min);
	return true;
}

bool Attribs::changeMax(int id, double max)
{
	//make sure id is a valid id
	int size = attributes.size() - 1;
	if (id < 0 || id > size)
		return false;

	attributes[id].setMax(max);
	return true;
}

bool Attribs::changeFri(int id, double fri)
{
	//make sure id is a valid id
	int size = attributes.size() - 1;
	if (id < 0 || id > size)
		return false;

	attributes[id].setFri(fri);
	return true;
}

bool Attribs::removeAttribute(int id)
{
	int size = attributes.size() - 1;
	if (id < 0 || id > size)
		return false;
	int position = 0;
	std::vector<Attrib>::iterator it;
	for (it = attributes.begin(); it < attributes.end(); ++it)
	{
		if ((*it).getId() == id)
			it = attributes.end();
		++position;
	}
	if (position > size)
		return false;
	attributes.erase(attributes.begin() + position);
	return true;
}

//accessor methds
std::string& Attribs::getName(int id)
{
	//make sure id is a valid id
	int size = attributes.size() - 1;
	if (id < 0 || id > size)
		return errorMsg;

	return attributes[id].getName();
}

double Attribs::getMin(int id)
{
	return attributes[id].getMin();
}

double Attribs::getMax(int id)
{
	return attributes[id].getMax();
}

double Attribs::getFri(int id)
{
	return attributes[id].getFri();
}

std::string Attribs::getNameByIndex(int index)
{
	int size = attributes.size();
	if (index < 0 || index >= size)
		return "Attribute Not Found";
	return attributes[index].getName();
}

double Attribs::getMinByIndex(int index)
{
	int size = attributes.size();
	if (index < 0 || index >= size)
		return 0.0;
	return attributes[index].getMin();
}

double Attribs::getMaxByIndex(int index)
{
	int size = attributes.size();
	if (index < 0 || index >= size)
		return 0.0;
	return attributes[index].getMax();
}

double Attribs::getFriByIndex(int index)
{
	int size = attributes.size();
	if (index < 0 || index >= size)
		return 0.0;
	return attributes[index].getFri();
}

int Attribs::getId(std::string& name)
{
	std::vector<Attrib>::iterator it;
	for (it = attributes.begin(); it < attributes.end(); ++it)
	{
		if ((*it).getName() == name)
			return (*it).getId();
	}
	return -1;
}

//serializable methods
void Attribs::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << attributes.size();

		std::vector<Attrib>::iterator it;
		for (it = attributes.begin(); it < attributes.end(); ++it)
		{
			std::string aName = (*it).getName();
			CString name(aName.c_str());
			ar << (*it).getId() << name << (*it).getMin() << (*it).getMax() << (*it).getFri();
		}
	}
	else
	{
		int size;
		int id;
		CString name;
		double min;
		double max;
		double fri;

		ar >> size;

		for (int x = 0; x < size; ++x)
		{
			ar >> id >> name >> min >> max >> fri;
			CT2CA s(name);
			std::string aName(s);
			Attrib temp(id, aName, min, max, fri);
			attributes.push_back(temp);
		}
	}
}
