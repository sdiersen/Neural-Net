#pragma once
/*
	This is the container for all attributes for the Neural Network
	Attribs is a vector that contains all attributes
*/
#include <vector>
#include "Attrib.h"

class Attribs : public CObject
{
	
DECLARE_SERIAL(Attribs)

public:
	Attribs(void);
	Attribs(const Attribs& a);
	Attribs& operator=(const Attribs& a);
	~Attribs(void);

	//private variables
private:
	std::vector<Attrib> attributes;
	std::string errorMsg;

	//public methods
public:
	//mutator methods
	bool addAttribute(const std::string& name, double min, double max, double fri = 1.0);
	bool changeName(int id, const std::string& newName);
	bool changeMin(int id, double min);
	bool changeMax(int id, double max);
	bool changeFri(int id, double fri);
	bool removeAttribute(int id);
	void clear() { attributes.clear(); }

	//accessor methods
	std::string& getName(int id);
	double getMin(int id);
	double getMax(int id);
	double getFri(int id);
	std::string getNameByIndex(int index);
	double getMinByIndex(int index);
	double getMaxByIndex(int index);
	double getFriByIndex(int index);
	int getCount() { return attributes.size(); }
	int getId(std::string& name);

	//serializable methods
	void Serialize(CArchive& ar);
};

