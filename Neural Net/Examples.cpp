#include "StdAfx.h"
#include "Examples.h"

IMPLEMENT_SERIAL(Examples, CObject, 1);

Examples::Examples(void)
{
	position = 0;
	examples = std::vector<Example>();
	attributes = Attribs();
	values = Values();
	haveExamples = false;
}

Examples::Examples(const Attribs& attributes, const Values& values)
{
	position = 0;
	examples = std::vector<Example>();
	this->attributes = attributes;
	this->values = values;
	haveExamples = false;
}

Examples::Examples(const Examples& e)
{
	position = e.position;
	examples = e.examples;
	attributes = e.attributes;
	values = e.values;
	haveExamples = e.haveExamples;
}

Examples& Examples::operator=(const Examples& e)
{
	if (&e != this)
	{
		position = e.position;
		examples = e.examples;
		attributes = e.attributes;
		values = e.values;
		haveExamples = e.haveExamples;
	}
	return *this;
}

Examples::~Examples(void) {}

//private methods
double Examples::normalize(double min, double max, double value)
{
	double norm = 0.0;
	double numerator = value - min;
	double denominator = max - min;
	if (denominator == 0.00)
		return norm;
	norm = numerator / denominator;
	return norm;
}

//public methods
//mutator methods
bool Examples::addExample(const std::vector<double>& atts, const std::vector<double>& vals)
{
	int id = examples.size();
	int attCount = attributes.getCount();
	int valCount = values.getCount();
	int attsSize = atts.size();
	int valsSize = vals.size();

	// make sure the example has the same number of attributes and values as
	//the network does
	if (attCount != attsSize || valCount != valsSize)
		return false;

	//normalize the example attributes and values
	std::vector<double> normAtts = std::vector<double>();
	std::vector<double> normVals = std::vector<double>();
	int count = 0;
	double min;
	double max;
	double value;
	double norm;

	std::vector<double>::const_iterator it;
	//get the normalized attribute values
	for (it = atts.begin(); it < atts.end(); ++it)
	{
		min = attributes.getMin(count);
		max = attributes.getMax(count);
		value = *it;
		norm = normalize(min, max, value);

		normAtts.push_back(norm);
		++count;
	}
	//get the normalized value values
	count = 0;
	for (it = vals.begin(); it < vals.end(); ++it)
	{
		min = values.getMin(count);
		max = values.getMax(count);
		value = *it;
		norm = normalize(min, max, value);

		normVals.push_back(norm);
		++count;
	}

	//make the example proper
	Example temp(id, atts, vals);
	temp.setNormalized(normAtts, normVals);

	//add this example to examples
	examples.push_back(temp);
	
	haveExamples = true;

	return true;
}

bool Examples::addExample(const Example& example)
{
	examples.push_back(example);
	haveExamples = true;
	return true;
}

void Examples::appendExamples(Examples& examps)
{
	int id = examples.size();
	std::vector<Example> e;
	e = examps.getExampleVector(e);
	std::vector<Example>::iterator it;
	for(it = e.begin(); it < e.end(); ++it)
	{
		/*(*it).setId(id);
		++id;*/
		examples.push_back((*it));
	}
}

std::vector<Example>& Examples::getExampleVector(std::vector<Example>& e)
{
	e = examples;
	return e;
}

void Examples::setAttributes(const Attribs& attributes)
{
	this->attributes = attributes;
}

void Examples::setValues(const Values& values)
{
	this->values = values;
}

std::vector<double>& Examples::getAttributes(int id, std::vector<double>& atts)
{
	int size = examples.size();
	if (id >= 0 && id < size)
	{
		atts = examples[id].getAttributes(atts);
	}
	return atts;
}

std::vector<double>& Examples::getValues(int id, std::vector<double>& vals)
{
	int size = examples.size();
	if (id >= 0 && id < size)
	{
		vals = examples[id].getValues(vals);
	}
	return vals;
}

std::vector<double>& Examples::getNormalizedAttributes(int id, std::vector<double>& atts)
{
	int size = examples.size();
	if (id >= 0 && id < size)
	{
		atts = examples[id].getNormalizedAttributes(atts);
	}
	return atts;
}

std::vector<double>& Examples::getNormalizedValues(int id, std::vector<double>& vals)
{
	int size = examples.size();
	if (id >= 0 && id < size)
	{
		vals = examples[id].getNormalizedValues(vals);
	}
	return vals;
}

Example& Examples::getNextExample(Example& example)
{
	example = examples[position];
	
	int size = examples.size();
	position = (position + 1) % size;

	return example;
}

void Examples::randomizeExamples()
{
	std::random_shuffle(examples.begin(), examples.end());
}

void Examples::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		int size = examples.size();
		int atts = attributes.getCount();
		int vals = values.getCount();
		int id = 0;

		ar << haveExamples << size << atts << vals;

		std::vector<Example>::iterator it;
		for (it = examples.begin(); it < examples.end(); ++it)
		{
			ar << (*it).getId();

			//for each example save all attribute value then value values
			//then normalized attribute values and finally normalized value values
			for (id; id < atts; ++id)
			{
				ar << (*it).getAttribute(id);
			}
			id = 0;
			for (id; id < vals; ++id)
			{
				ar << (*it).getValue(id);
			}
			id = 0; 
			for (id; id < atts; ++id)
			{
				ar << (*it).getNormalizedAttribute(id);
			}
			id = 0;
			for (id; id < vals; ++id)
			{
				ar << (*it).getNormalizedValue(id);
			}
			id = 0;
		}

	}
	else
	{
		int size;
		int attCount;
		int valCount;
		int id;
		std::vector<double> atts = std::vector<double>();
		std::vector<double> vals = std::vector<double>();
		std::vector<double> normAtts = std::vector<double>();
		std::vector<double> normVals = std::vector<double>();
		double att;
		double val;
		double normAtt;
		double normVal;

		ar >> haveExamples >> size >> attCount >> valCount;

		examples.clear();
		for (int s = 0; s < size; ++s)
		{
			ar >> id;
			
			atts.clear();
			vals.clear();
			normAtts.clear();
			normVals.clear();

			for (int a = 0; a < attCount; ++a)
			{
				ar >> att;
				atts.push_back(att);
			}
			for (int v = 0; v < valCount; ++v)
			{
				ar >> val;
				vals.push_back(val);
			}
			for (int a = 0; a < attCount; ++a)
			{
				ar >> normAtt;
				normAtts.push_back(normAtt);
			}
			for (int v = 0; v < valCount; ++v)
			{
				ar >> normVal;
				normVals.push_back(normVal);
			}
			
			Example temp(id, atts, vals);
			temp.setNormalized(normAtts, normVals);
			examples.push_back(temp);
		}
	}
}