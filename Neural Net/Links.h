#pragma once

#include <vector>
#include "Link.h"

class Links : public CObject
{
	
DECLARE_SERIAL(Links)

public:
	Links(void);
	Links(const Links& l);
	Links& operator=(const Links& l);
	~Links(void);

	//member variables
private:
	std::vector<Link> list;
	int position;

	//public methods
public:
	//mutator methods
	void addLink(int from, int to, int id);
	void setWeight(int id, double weight);
	void setDeltaWeight(int id, double delta);
	void setValue(int id, double value);
	void clear();
	void resetPosition();

	//accessor methods
	Link& getLink(int id, Link& link);
	double getWeight(int id);
	double getDeltaWeight(int id);
	double getValue(int id);
	int getFrom(int id);
	int getTo(int id);
	Links& getLinksIn(int to, Links& in);
	Links& getLinksOut(int from, Links& out);
	int getNextId();
	Link& getNextLink(Link& l);
	int getCount();
	double getSumOfLinks();
	int getId(int from, int to);
	Link& getLinkIn(int from, Link& link);
	Link& getLinkOut(int to, Link& link);

	//serializable methods
	void Serialize(CArchive& ar);
	
	//private methods
private:

};

