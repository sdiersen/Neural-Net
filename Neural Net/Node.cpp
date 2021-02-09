#include "stdafx.h"
#include "Node.h"

IMPLEMENT_SERIAL(Node, CObject, 1)

Node::Node(void)
{
	id = -1;
	layer = -1;
	output = 0.0;
	error = 0.0;
	outputError = 0.0;
	sumIntoNode = 0.0;
}

Node::Node(int id, int layer)
{
	this->id = id;
	this->layer = layer;
	output = 0.0;
	error = 0.0;
	outputError = 0.0;
	sumIntoNode = 0.0;
}

Node::Node(const Node& n)
{
	id = n.id;
	layer = n.layer;
	output = n.output;
	error = n.error;
	outputError = n.outputError;
	sumIntoNode = n.sumIntoNode;
}

Node& Node::operator=(const Node& n)
{
	if (&n != this)
	{
		id = n.id;
		layer = n.layer;
		output = n.output;
		error = n.error;
		outputError = n.outputError;
		sumIntoNode = n.sumIntoNode;
	}
	return *this;
}

Node::~Node(void) {}

//serializable methods
void Node::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << id << layer << output << error << outputError << sumIntoNode;
	}
	else
	{
		ar >> id >> layer >> output >> error >> outputError >> sumIntoNode;
	}
}