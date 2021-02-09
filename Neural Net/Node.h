#pragma once

#include <vector>
#include "Links.h"

class Node : public CObject
{

DECLARE_SERIAL(Node)

public:
	Node(void);
	Node(int id, int layer);
	Node(const Node& n);
	Node& operator=(const Node& n);
	~Node(void);

	//private member variables
private:
	int id;
	int layer;
	double output;
	double error;
	double sumIntoNode;
	double outputError;

	//public methods
public:
	//mutator methods
	void setId(int id) { this->id = id; }
	void setLayer(int layer) { this->layer = layer; }
	void setOutput(double output) { this->output = output; }
	void setError(double error) { this->error = error; }
	void setOutputError(double outputError) { this->outputError = outputError; }
	void setSumIntoNode(double sum) { sumIntoNode = sum; }

	//accessor methods
	int getId() { return id; }
	int getLayer() { return layer; }
	double getOutput() { return output; }
	double getError() { return error; }
	double getOutputError() { return outputError; }
	double getSumIntoNode() { return sumIntoNode; }

	//serializable methods
	void Serialize(CArchive& ar);
};