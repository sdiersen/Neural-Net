#pragma once

#include <vector>
#include "Attribs.h"
#include "Values.h"
#include "Example.h"
#include <algorithm>

class Examples : public CObject
{

DECLARE_SERIAL(Examples)

public:
	Examples(void);
	Examples(const Attribs& attributes, const Values& values);
	Examples(const Examples& e);
	Examples& operator=(const Examples& e);
	~Examples(void);

	//private variables
private:
	std::vector<Example> examples;
	Attribs attributes;
	Values values;
	int position; //this is the position of the next example to get
	bool haveExamples;

	//public methods
public:
	//mutator methods
	bool addExample(const std::vector<double>& atts, const std::vector<double>& vals);
	bool addExample(const Example& example);
	void setAttributes(const Attribs& attributes);
	void setValues(const Values& values);
	void resetPosition() { position = 0; }
	void setPosition(int p) { position = (p % examples.size()); }
	void appendExamples(Examples& examps);
	void clear() { examples.clear(); }
	void randomizeExamples();
	//void randomizeExamples(int seed);
	
	//accessor methods
	std::vector<double>& getAttributes(int id, std::vector<double>& atts);
	std::vector<double>& getNormalizedAttributes(int id, std::vector<double>& atts);
	std::vector<double>& getValues(int id, std::vector<double>& vals);
	std::vector<double>& getNormalizedValues(int id, std::vector<double>& vals);
	Example& getNextExample(Example& example);
	int getCount() { return examples.size(); }
	std::vector<Example>& getExampleVector(std::vector<Example>& e);
	bool hasExamples() { return haveExamples; }

	//serializable methods
	void Serialize(CArchive& ar);

	//private methods
private:
	double normalize(double min, double max, double value);
};

