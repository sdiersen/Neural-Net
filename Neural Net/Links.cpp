#include "StdAfx.h"
#include "Links.h"

IMPLEMENT_SERIAL(Links, CObject, 1)

Links::Links(void)
{
	list = std::vector<Link>();
	position = 0;
}

Links::Links(const Links& l)
{
	list = l.list;
	position = l.position;
}

Links& Links::operator=(const Links& l)
{
	if (&l != this)
	{
		list.clear();
		int blah = 0;
		int balh = 0;
		list.assign(l.list.begin(), l.list.end());
		position = l.position;
	}
	return *this;
}

Links::~Links(void){}

//public methods
//mutator methods

void Links::addLink(int from, int to, int id)
{
	list.push_back(Link(from, to, id));
}

void Links::setWeight(int id, double weight)
{
	std::vector<Link>::iterator it;
	for (it = list.begin(); it < list.end(); ++it)
	{
		if ((*it).getId() == id)
		{
			(*it).setWeight(weight);
			return;
		}
	}
}

void Links::setDeltaWeight(int id, double delta)
{
	std::vector<Link>::iterator it;
	for (it = list.begin(); it < list.end(); ++it)
	{
		if ((*it).getId() == id)
		{
			(*it).setDeltaWeight(delta);
			return;
		}
	}
}

void Links::setValue(int id, double value)
{
	std::vector<Link>::iterator it;
	for (it = list.begin(); it < list.end(); ++it)
	{
		if ((*it).getId() == id)
		{
			(*it).setValue(value);
			return;
		}
	}
}

void Links::clear()
{
	list.clear();
	position = 0;
}

void Links::resetPosition()
{
	position = 0;
}

//accessor methods
Link& Links::getLink(int id, Link& link)
{
	std::vector<Link>::iterator it;
	for (it = list.begin(); it < list.end(); ++it)
	{
		if ((*it).getId() == id)
		{
			link = (*it);
			it = list.end();
		}
	}
	return link;
}

double Links::getWeight(int id)
{
	std::vector<Link>::iterator it;
	for (it = list.begin(); it < list.end(); ++it)
	{
		if ((*it).getId() == id)
		{
			return (*it).getWeight();
		}
	}
	return 0.0;
}

double Links::getDeltaWeight(int id)
{
	std::vector<Link>::iterator it;
	for (it = list.begin(); it < list.end(); ++it)
	{
		if ((*it).getId() == id)
		{
			return (*it).getDeltaWeight();
		}
	}
	return 0.0;
}

double Links::getValue(int id)
{
	std::vector<Link>::iterator it;
	for (it = list.begin(); it < list.end(); ++it)
	{
		if ((*it).getId() == id)
		{
			return (*it).getValue();
		}
	}
	return 0.0;
}

int Links::getFrom(int id)
{
	std::vector<Link>::iterator it;
	for (it = list.begin(); it < list.end(); ++it)
	{
		if ((*it).getId() == id)
		{
			return (*it).getNodeFrom();
		}
	}
	return -1;
}

int Links::getTo(int id)
{
	std::vector<Link>::iterator it;
	for (it = list.begin(); it < list.end(); ++it)
	{
		if ((*it).getId() == id)
		{
			return (*it).getNodeTo();
		}
	}
	return -1;
}

Links& Links::getLinksIn(int to, Links& in)
{
	in.clear();

	std::vector<Link>::iterator it;
	for (it = list.begin(); it < list.end(); ++it)
	{
		if ((*it).getNodeTo() == to)
			in.addLink((*it).getNodeFrom(), to, (*it).getId());
	}
	return in;
}

Links& Links::getLinksOut(int from, Links& out)
{
	out.clear();
	
	std::vector<Link>::iterator it;
	for (it = list.begin(); it < list.end(); ++it)
	{
		if ((*it).getNodeFrom() == from)
			out.addLink(from, (*it).getNodeTo(), (*it).getId());
	}
	return out;
}

int Links::getNextId()
{
	int id = list[position].getId();
	int size = list.size();
	position = (position + 1) % size;
	return id;
}

Link& Links::getNextLink(Link& l)
{
	l = list[position];
	int size = list.size();
	position = (position + 1) % size;
	return l;
}

int Links::getCount()
{
	return list.size();
}

double Links::getSumOfLinks()
{
	double sum = 0.0;
	double weight;
	double value;
	std::vector<Link>::iterator it;
	for (it = list.begin(); it < list.end(); ++it)
	{
		weight = (*it).getWeight();
		value = (*it).getValue();
		sum += weight * value;
	}
	return sum;
}

int Links::getId(int from, int to)
{
	std::vector<Link>::iterator it;
	for (it = list.begin(); it < list.end(); ++it)
	{
		if ((*it).getNodeFrom() == from && (*it).getNodeTo() == to)
			return (*it).getId();
	}
	return -1;
}

Link& Links::getLinkIn(int from, Link& link)
{
	std::vector<Link>::iterator it;
	for (it = list.begin(); it < list.end(); ++it)
	{
		if ((*it).getNodeFrom() == from)
		{
			link = (*it);
			return link;
		}
	}
	return link;
}

Link& Links::getLinkOut(int to, Link& link)
{
	std::vector<Link>::iterator it;
	for (it = list.begin(); it < list.end(); ++it)
	{
		if ((*it).getNodeTo() == to)
		{
			link = (*it);
			return link;
		}
	}
	return link;
}

//serializable methods
void Links::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << list.size();

		std::vector<Link>::iterator it;
		for (it = list.begin(); it < list.end(); ++it)
		{
			ar << (*it).getId() << (*it).getNodeFrom() << (*it).getNodeTo() << (*it).getWeight() << (*it).getDeltaWeight() << (*it).getValue();
		}
	}
	else
	{
		int size;
		int id;
		int from;
		int to;
		double weight;
		double delta;
		double value;

		list.clear();

		ar >> size;

		for (int x = 0; x < size; ++x)
		{
			ar >> id >> from >> to >> weight >> delta >> value;
			
			Link temp(from, to, id);
			temp.setWeight(weight);
			temp.setDeltaWeight(delta);
			temp.setValue(value);
			
			list.push_back(temp);
		}
	}
}