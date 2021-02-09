#pragma once

#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <time.h>
#include "Attribs.h"
#include "Values.h"
#include "Links.h"
#include "Examples.h"
#include "Node.h"


#define RN ((double) rand() / (double)(RAND_MAX))

class ANN : public CObject
{

DECLARE_SERIAL(ANN)

public:
	ANN(void);
	ANN(const std::vector<int>& nodes, double learning, double momentum);
	~ANN(void);


	//member variables
private:
	//basic network variables
	std::string networkName;	//the name of the network
	Attribs attributes;			//an Attribs object to hold all attributes
	Values values;				//a Values object to hold all values
	Examples examples;			//an Example object to hold all examples
	std::vector<Node> theNet;	//a vector of Nodes that is the neural network
	std::vector<int> nodesPerLayer;	//a vector that holds the number of nodes per layer
									//nodesPerLayer[0] is the input layer
	int numberOfLayers;			//a quick reference to the number of layers
	double learningRate;		//the learning rate of the network
	double momentum;			//the momentum of the network
	std::vector<std::vector<Link>> theLinks;	//a matrix of the links
	std::vector<int> layerStart;				//a quick reference into theNet for the first node in a layer
	std::vector<int> layerEnd;					//a quick reference into theNet for the last node in a layer
	std::string outputFile;						//the name of the output file

	//evaluationOutput is used to store each output value from each example 
	//this has the potential of being very very large ***is it necessary****?
	//this is only used for testing a network, not used in training
	std::vector<double> evaluationOutput; 
	std::vector<double> evaluationError;
	std::vector<double> evaluationOutputError;
	std::vector<int> exampleSetOutput;
	Examples outputExamples;

	//k-fold variables
	std::vector<std::vector<double>> kFoldError;
	std::vector<std::vector<double>> kFoldOutput;
	std::vector<std::vector<double>> kFoldOutputError;
	std::vector<std::vector<int>> kFoldWithin01;
	std::vector<std::vector<int>> kFoldWithin05;
	std::vector<std::vector<int>> kFoldWithin10;
	std::vector<std::vector<int>> kFoldWithin25;
	std::vector<std::vector<int>> kFoldMoreThan25;
	std::vector<double> modelError;
	std::vector<double> modelOutput;
	std::vector<double> modelOutputError;
	std::vector<int> hiddenStartNodes;
	std::vector<int> hiddenEndNodes;
	int startingLayer;
	int endingLayer;
	int folds;
	int epochs;
	int runs;
	double stoppingCriteria;
	std::vector<Examples> partitionedFolds;
	int startingPosition;
	int modelNumber;
	//new fields
	std::vector<std::vector<int>> epochCount;
	//************************************************
	//************** 2 27 2011 ***********************
	//************************************************
	int userSeed;
	int currentSeed;
	int numTests;
	int testsRun;
	int testType;

	//public methods
public:
	//neural network methods
	void createNetwork();
	void createIANNNetwork();
	void backPropagation();
	void evaluateExamples(Examples& testing);
	void runExamples(Examples& exampleSet);
	void runExamples() 
	{ 
		if (outputExamples.getCount() > 0) 
			runExamples(outputExamples);
	}
	void trainNetwork();
	void trainIANNNetwork();

	//k-fold cross-validation methods
	void kFoldCrossValidation();
	//new methods
	void runAllKFold();
	

	//serializable methods
	void Serialize(CArchive& ar);
	bool loadExampleFile(std::string& filename);
	bool appendExampleFile(std::string& filename);
	bool resetExamples() { examples.clear(); return true; }
	bool haveExamples() { return examples.hasExamples(); }
	bool loadAttributeFile(std::string& filename);
	bool loadValueFile(std::string& filename);
	int getExampleCount();
	void shuffleExamples();
	bool saveExamples(std::string& filename);
	bool saveModel(std::string& filename);
	void saveOutput();
	bool loadOutputExamples(std::string& filename);

	//interface methods for MFC front end
	//ATTRIBUTE METHODS
	//accessor methods
	double getAttributeMin(std::string& name);
	double getAttributeMax(std::string& name);
	double getAttributeFri(std::string& name);
	std::string getAttributeName(int index);
	double getAttributeMin(int index);	
	double getAttributeMax(int index);
	double getAttributeFri(int index);
	int getNumberOfAttributes();

	//mutator methods
	bool addAttribute(std::string& name, double min, double max, double fri);	
	bool editAttribute(std::string& previousName, std::string& editName, double min, double max, double fri);	
	bool removeAttribute(std::string& name);
	
	//VALUE METHODS
	//accessor methods
	double getValueMin(std::string& name);
	double getValueMax(std::string& name);
	std::string getValueName(int index);
	double getValueMin(int index);	
	double getValueMax(int index);
	int getNumberOfValues();

	//mutator methods
	bool addValue(std::string& name, double min, double max);
	bool editValue(std::string& previousName, std::string& editName, double min, double max);
	bool removeValue(std::string& name);

	//K-FOLD CROSS-VALIDATION METHODS
	//accessor methods
	int getFolds();
	int getEpochs(); 
	int getConsecutiveRuns();
	double getStoppingCriteria();
	int getStartingPosition();
	std::vector<int>& getNumberOfStartingHiddenNodes(std::vector<int>& starting);
	std::vector<int>& getNumberOfEndingHiddenNodes(std::vector<int>& ending);
	int getFoldStartingLayer();
	int getFoldEndingLayer();
	int getFoldStartingNodeAtLayer(int layer);
	int getFoldEndingNodeAtLayer(int layer);

	//mutator methods
	void setFolds(int folds);
	void setEpochs(int epochs);
	void setConsecutiveRuns(int runs);
	void setStoppingCriteria(double stopping);
	bool setStartingPosition(int starting);
	void setNumberOfStartingHiddenNodes(std::vector<int>& starting);
	void setNumberOfEndingHiddenNodes(std::vector<int>& ending);
	void setKFoldParameters(int folds, int epochs, double criteria, int runs, int startingLayer, int endingLayer,
							std::vector<int>& startingNodes, std::vector<int>& endingNodes);	
	void setKFoldStartingNodeAtLayer(int layer, int nodes);
	void setKFoldEndingNodeAtLayer(int layer, int nodes);

	//NETWORK METHODS
	//accessor methods
	std::string getNetworkName();
	int getNumberOfLayers();
	double getLearningRate();
	double getMomentum();
	int getNodesAtLayer(int layer);
	int getInputNodes();
	int getOutputNodes();
	int getHidden1();
	int getHidden2();
	int getHidden3();
	int getHidden4();
	std::string getOutputFile() { return outputFile; }
	
	//mutator methods
	void setNetworkName(std::string& name);
	void setNumberOfLayers(int layers);
	void setLearningRate(double learning);
	void setMomentum(double momentum);
	void setNodesPerLayer(std::vector<int>& nodes);
	void setOutputFile(std::string& f) { outputFile = f; }
	
	//private methods
private:
	//evaluate example(s) methods
	void runExample(Example& example); //runs a single example through the network
	void evaluateOutputError(Example& example); //evaluates the output eror of an example that has just been run
	void adjustLinkWeights();
	//new methods
	void setLayerStart();
	void setLayerEnd();
	void adjustIANNLinkWeights();

	//k-fold cross-validation methods
	void createFolds();
	void testAndEvaluateFold(Examples& testing);
	void evaluateModel();

	//private methods
private:
	//network creation methods
	void buildNetwork();
	void buildBiasLinks();
	void buildLinks();
	void buildIANNLinks();
	void initLinkWeights();
	void initBiasLinkWeights();
	void addLinksToNodes();

	//helper methods
	int concatinateId(int from, int to);
	int getFirstIdOfLayer(int layer);
	int getLastIdOfLayer(int layer);
	void setNodeLinkValues(int id, double value);
	std::vector<double>& getNetworkOutput(std::vector<double>& out);
	std::vector<double>& getNetworkOutputError(std::vector<double>& out);

	//activation functions
	double logistic(double x) { return ( 1. / (1. + exp(-x))); }
	double Dlogistic(double x) { return ( exp(-x) / (( 1. + exp(-x)) * ( 1. + exp(-x)))); }
	

	//added 2 27 2011
public:
	void setUserSeed(int seed);
	void setConsecutiveTests(int tests);
	void runConsecutiveTests();
	void runConsecutiveIANNTests();
private:
	void setNewSeed();
};

