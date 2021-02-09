#pragma once
class Link
{
public:
	Link(void)
	{
		nodeFrom = -1;
		nodeTo = -1;
		id = -1;
		weight = 0;
		deltaWeight = 0;
		value = 0;
		fri = 1;
	}
	Link(int from, int to, int id, double fri = 1.0)
	{
		nodeFrom = from;
		nodeTo = to;
		this->id = id;
		weight = 0.0;
		deltaWeight = 0.0;
		value = 0.0;
		this->fri = fri;
	}
	Link(const Link& l)
	{
		nodeFrom = l.nodeFrom;
		nodeTo = l.nodeTo;
		id = l.id;
		weight = l.weight;
		deltaWeight = l.deltaWeight;
		value = l.value;
		fri = l.fri;
	}
	Link& operator=(const Link& l)
	{
		if (&l != this)
		{
			nodeFrom = l.nodeFrom;
			nodeTo = l.nodeTo;
			id = l.id;
			weight = l.weight;
			deltaWeight = l.deltaWeight;
			value = l.value;
			fri = l.fri;
		}
		return *this;
	}
	~Link(void){}

	//member variables
private:
	int nodeFrom;
	int nodeTo;
	int id;
	double weight;
	double value;
	double deltaWeight;
	double fri;

	//public methods
public:
	//inline public methods
	//mutator methods
	void setNodeFrom(int from) { nodeFrom = from; }
	void setNodeTo(int to) { nodeTo = to; }
	void setId(int id) { this->id = id; }
	void setWeight(double w) { weight = w; }
	void setDeltaWeight(double d) { deltaWeight = d; }
	void setValue(double v) { value = v; }
	void setFri(double f) { fri = f; }

	//accessor methods
	int getNodeFrom() { return nodeFrom; }
	int getNodeTo() { return nodeTo; }
	int getId() { return id; }
	double getWeight() { return weight; }
	double getDeltaWeight() { return deltaWeight; }
	double getValue() { return value; }
	double getFri() { return fri; }

};

