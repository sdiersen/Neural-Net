#include "StdAfx.h"
#include "ANN.h"

IMPLEMENT_SERIAL(ANN, CObject, 1)

ANN::ANN(void)
{
	nodesPerLayer = std::vector<int>();
	learningRate = 0;
	momentum = 0;
	networkName = "";
	theNet = std::vector<Node>();
	numberOfLayers = 0;
	startingLayer = 0;
	endingLayer = 0;
	folds = 0;
	epochs = 0;
	runs = 0;
	stoppingCriteria = 0;
	partitionedFolds = std::vector<Examples>();
	startingPosition = 0;
	modelNumber = 0;
	epochCount = std::vector<std::vector<int>>();
	layerStart = std::vector<int>();
	layerEnd = std::vector<int>();
	theLinks = std::vector<std::vector<Link>>();

	//************************************************
	//************** 2 27 2011 ***********************
	//************************************************
	numTests = 1;
	testsRun = 0;
	testType = 0;
	//end 2 27 2011

}

ANN::ANN(const std::vector<int>& nodes, double learning, double momentum)
{
	nodesPerLayer = nodes;
	learningRate = learning;
	this->momentum = momentum;
	
	networkName = "";
	theNet = std::vector<Node>();
	numberOfLayers = 0;
	startingLayer = 0;
	endingLayer = 0;
	folds = 0;
	epochs = 0;
	runs = 0;
	stoppingCriteria = 0;
	partitionedFolds = std::vector<Examples>();
	startingPosition = 0;
	modelNumber = 0;
	epochCount = std::vector<std::vector<int>>();
	layerStart = std::vector<int>();
	layerEnd = std::vector<int>();
	theLinks = std::vector<std::vector<Link>>();

	createNetwork();
}

ANN::~ANN(void)
{
}

//public methods
//**************************************************************************
//********************** NEURAL NETWORK METHODS  ***************************
//**************************************************************************

void ANN::createNetwork()
{
	buildNetwork();
	buildBiasLinks();
	buildLinks();
}

void ANN::createIANNNetwork()
{
	buildNetwork();
	buildBiasLinks();
	buildIANNLinks();
}

void ANN::backPropagation()
{
	int count = examples.getCount();
	examples.resetPosition();
	Example example = Example();
	for (int x = 0; x < count; ++x)
	{
		example = examples.getNextExample(example);

		//run the example
		runExample(example);

		//evaluate the output
		evaluateOutputError(example);

		//adjust the link weights using back prop
		adjustLinkWeights();
	}
}

void ANN::evaluateExamples(Examples& testing)
{
	//create a vector to hold the output of the network
	//this is a vector to allow for multiple output nodes in a network
	/*std::vector<double> outValues = std::vector<double>();*/

	//clear the evaluationOutput vector
	evaluationOutput.clear();
	evaluationError.clear();
	evaluationOutputError.clear();

	int within01 = 0;
	int within05 = 0;
	int within10 = 0;
	int within25 = 0;
	int morethan25 = 0;

	//run each example through the network and save the output in outValues (for each example)
	//save outValues in evaluationOutput
	Example example = Example();
	int count = testing.getCount();
	testing.resetPosition();
	for (int x = 0; x < count; ++x)
	{
		//get the next example
		example = testing.getNextExample(example);

		//run the current example through the network
		runExample(example);

		//save the output from the running of example
		/*outValues.clear();
		outValues = getNetworkOutput(outValues);*/

		//get the output node
		int outId = layerEnd[numberOfLayers - 1];
		Node out = theNet[outId];

		//add the outValues to the evaluationOutput vector
		evaluationOutput.push_back(out.getOutput());
		evaluationError.push_back(out.getError());
		evaluationOutputError.push_back(out.getOutputError());
		double output = out.getOutput();
		output = fabs(output - example.getValue(0));
		if (output <= 0.01)
			++within01;
		else if (output <= 0.05)
			++within05;
		else if (output <= 0.1)
			++within10;
		else if (output <= 0.25)
			++within25;
		else
			++morethan25;
	}
	kFoldWithin01[modelNumber].push_back(within01);
	kFoldWithin05[modelNumber].push_back(within05);
	kFoldWithin10[modelNumber].push_back(within10);
	kFoldWithin25[modelNumber].push_back(within25);
	kFoldMoreThan25[modelNumber].push_back(morethan25);
}

void ANN::runExamples(Examples& exampleSet)
{
	int count = exampleSet.getCount();
	if (count == 0) 
		return;

	exampleSetOutput = std::vector<int>();
	int outId = layerEnd[numberOfLayers - 1];
	double out;
	Example exam = Example();
	exampleSet.resetPosition();
	for (int e = 0; e < count; ++e)
	{
		exam = exampleSet.getNextExample(exam);
		runExample(exam);
		out = theNet[outId].getOutput();
		if (out <= 0.250)
		{
			exampleSetOutput.push_back(0);
		}
		else if (out >= 0.750)
		{
			exampleSetOutput.push_back(1);
		}
		else
		{
			exampleSetOutput.push_back(2);
		}
	}

	saveOutput();
}

void ANN::trainNetwork()
{
	int count = examples.getCount();
	if (count == 0)
		return;

	//create the network
	createNetwork();

	//train the network until either the stopping criteria or number of epochs is reached
	Example example = Example();
	std::vector<double> output = std::vector<double>();
	bool trained = false;
	int numInRange = 0;
	int numEpochs = 0;
	double error = 0.0;
	int outputId = layerEnd[numberOfLayers - 1];
	examples.resetPosition();
	while (!trained)
	{
		for (int e = 0; e < count; ++e)
		{
			//get the current example
			example = examples.getNextExample(example);

			//evaluate the current example
			runExample(example);

			//get the error for this example
			evaluateOutputError(example);

			//adjust the link weights using back propagation
			adjustLinkWeights();

			//get the error for this example
			double expected = example.getValue(0);
			double actual = theNet[outputId].getOutput();
			error = fabs(expected - actual);
			//error = theNet[outputId].getOutputError();
			output.push_back(error);
		}

		int eeSize = output.size();
		if (eeSize >= 1)
		{
			error = 0.0;
			std::vector<double>::iterator it;
			for (it = output.begin(); it < output.end(); ++it)
				error += (*it);
			error = error / eeSize;
			if (error <= stoppingCriteria)
				++numInRange;
			else
				numInRange = 0;
		}
		output.clear();
		++numEpochs;

		if (numInRange == runs || numEpochs == epochs)
		{
			trained = true;
		}
	}
}

void ANN::trainIANNNetwork()
{
	int count = examples.getCount();
	if (count == 0)
		return;

	//create the network
	createIANNNetwork();

	//train the network until either the stopping criteria or number of epochs is reached
	Example example = Example();
	std::vector<double> output = std::vector<double>();
	bool trained = false;
	int numInRange = 0;
	int numEpochs = 0;
	double error = 0.0;
	int outputId = layerEnd[numberOfLayers - 1];
	examples.resetPosition();
	while (!trained)
	{
		for (int e = 0; e < count; ++e)
		{
			//get the current example
			example = examples.getNextExample(example);

			//evaluate the current example
			runExample(example);

			//get the error for this example
			evaluateOutputError(example);

			//adjust the link weights using back propagation
			adjustIANNLinkWeights();

			//get the error for this example
			double expected = example.getValue(0);
			double actual = theNet[outputId].getOutput();
			error = fabs(expected - actual);
			//error = theNet[outputId].getOutputError();
			output.push_back(error);
		}

		int eeSize = output.size();
		if (eeSize >= 1)
		{
			error = 0.0;
			std::vector<double>::iterator it;
			for (it = output.begin(); it < output.end(); ++it)
				error += (*it);
			error = error / eeSize;
			if (error <= stoppingCriteria)
				++numInRange;
			else
				numInRange = 0;
		}
		output.clear();
		++numEpochs;

		if (numInRange == runs || numEpochs == epochs)
		{
			trained = true;
		}
	}
}


//**************************************************************************
//***************  K FOLD CROSS VALIDATION METHODS   ***********************
//**************************************************************************

void ANN::runAllKFold()
{
	int totalruns = hiddenEndNodes[0] - hiddenStartNodes[0] + 1;
	if (hiddenStartNodes[1] > 0)
		totalruns *= (hiddenEndNodes[1] - hiddenStartNodes[1] + 1);
	/*
	epochCount = std::vector<std::vector<int>>(totalruns, folds);
	kFoldError = std::vector<std::vector<double>>(totalruns, folds);
	kFoldOutput = std::vector<std::vector<double>>(totalruns, folds);
	kFoldOutputError = std::vector<std::vector<double>>(totalruns, folds);
	kFoldWithin01 = std::vector<std::vector<int>>(totalruns, folds);
	kFoldWithin05 = std::vector<std::vector<int>>(totalruns, folds);
	kFoldWithin10 = std::vector<std::vector<int>>(totalruns, folds);
	kFoldWithin25 = std::vector<std::vector<int>>(totalruns, folds);
	kFoldMoreThan25 = std::vector<std::vector<int>>(totalruns, folds);
	*/
	epochCount.resize(totalruns);
	kFoldError.resize(totalruns);
	kFoldOutput.resize(totalruns);
	kFoldOutputError.resize(totalruns);
	kFoldWithin01.resize(totalruns);
	kFoldWithin05.resize(totalruns);
	kFoldWithin10.resize(totalruns);
	kFoldWithin25.resize(totalruns);
	kFoldMoreThan25.resize(totalruns);
	for (int i = 0; i < totalruns; i++)
	{
		epochCount[i].resize(folds);
		kFoldError[i].resize(folds);
		kFoldOutput[i].resize(folds);
		kFoldOutputError[i].resize(folds);
		kFoldWithin01[i].resize(folds);
		kFoldWithin05[i].resize(folds);
		kFoldWithin10[i].resize(folds);
		kFoldWithin25[i].resize(folds);
		kFoldMoreThan25[i].resize(folds);
	}
	for (int h1 = hiddenStartNodes[0]; h1 <= hiddenEndNodes[0]; ++h1)
	{
		nodesPerLayer[1] = h1;
		if (hiddenStartNodes[1] > 0)
		{
			for (int h2 = hiddenStartNodes[1]; h2 <= hiddenEndNodes[1]; ++h2)
			{
				nodesPerLayer[2] = h2;
				createNetwork();
				kFoldCrossValidation();
			}
		}
		else
		{
			createNetwork();
			kFoldCrossValidation();
		}
	}
}

//void ANN::runAllKFold()
//{
//	for (int h1 = hiddenStartNodes[0]; h1 <= hiddenEndNodes[0]; ++h1)
//	{
//		nodesPerLayer[1] = h1;
//		createNetwork();
//		kFoldCrossValidation();
//	}
//}


void ANN::kFoldCrossValidation()
{
	bool trained = false;
	Examples training = Examples();
	Examples testing = Examples();
	Example example = Example();
	double error = 0.0;
	std::vector<double> output = std::vector<double>();
	int numInRange;
	int numEpochs;
	int outputId = layerStart[numberOfLayers - 1];

	//create the folds
	createFolds();
	kFoldError[modelNumber].clear();
	kFoldOutput[modelNumber].clear();
	kFoldOutputError[modelNumber].clear();
	kFoldWithin01[modelNumber].clear();
	kFoldWithin05[modelNumber].clear();
	kFoldWithin10[modelNumber].clear();
	kFoldWithin25[modelNumber].clear();
	kFoldMoreThan25[modelNumber].clear();

	//each partition will serve as a test set once for the entire partitionedFolds vector
	//this means we will run "folds" number of neural networks
	for (int test = 0; test < folds; ++test)
	{
		buildBiasLinks();
		buildLinks();
		testing.clear();
		training.clear();
		//test is the number of the testing example set
		testing = partitionedFolds[test];

		//all other folds in the partitionedFolds vector are training folds
		for (int x = 0; x < folds; ++x)
		{
			if (x != test)
				training.appendExamples(partitionedFolds[x]);
		}

		//now that the training and testing folds are set
		//train this network on the training examples
		trained = false;
		numInRange = 0;
		numEpochs = 0;
		int count = training.getCount();
		while (!trained)
		{
			for (int e = 0; e < count; ++e)
			{
				//get the current example
				example = training.getNextExample(example);

				//evaluate the current example
				runExample(example);

				//get the error for this example
				evaluateOutputError(example);

				//adjust the link weights using back propagation
				adjustLinkWeights();

				//get the error for this example
				error = theNet[outputId].getOutputError();
				output.push_back(error);
			}

			int eeSize = output.size();
			if (eeSize >= 1)
			{
				error = 0.0;
				std::vector<double>::iterator it;
				for (it = output.begin(); it < output.end(); ++it)
					error += (*it);
				error = error / eeSize;
				if (error <= stoppingCriteria)
					++numInRange;
				else
					numInRange = 0;
			}
			output.clear();
			++numEpochs;

			if (numInRange == runs || numEpochs == epochs)
			{
				epochCount[modelNumber][test] = numEpochs;
				trained = true;
			}
		}

		//test the newly trained network with the testing fold
		testAndEvaluateFold(testing);
	}
	//all folds have been testing folds (there have been "folds" number of runs
	evaluateModel();
}

//creates the folds for k-fold cross-validation
//the starting point of the folds is based upon the member variable startingPoint
void ANN::createFolds()
{
	partitionedFolds.clear();

	Example example = Example();
	int position = 0;
	//for each fold add an Examples class to the partitionedFolds vector
	for (int x = 0; x < folds; ++x)
		partitionedFolds.push_back(Examples());

	int count = examples.getCount();
	examples.setPosition(startingPosition);

	for (int x = 0; x < count; ++x)
	{
		example = examples.getNextExample(example);
		partitionedFolds[position].addExample(example);

		position = (position + 1) % folds;
	}
}

void ANN::testAndEvaluateFold(Examples& testing)
{
	//test the network
	evaluateExamples(testing);

	//calculate and store the error
	//get the number of examples and the number of output nodes
	int numExamples = evaluationOutput.size();

	//error is the error of the sum of the output nodes errors / numOutputNodes
	double error = 0.0;
	double output = 0.0;
	double outputError = 0.0;
	

	if (numExamples < 1)
		return;

	for(int outId = 0; outId < numExamples; ++outId)
	{
		error += evaluationError[outId];
		output += evaluationOutput[outId];
		outputError += evaluationOutputError[outId];
	}
	error = error / numExamples;
	output = output / numExamples;
	outputError = outputError / numExamples;

	kFoldError[modelNumber].push_back(error);
	kFoldOutput[modelNumber].push_back(output);
	kFoldOutputError[modelNumber].push_back(outputError);
	
}

void ANN::evaluateModel()
{
	int kFoldErrorSize = kFoldError[modelNumber].size();

	if (kFoldErrorSize < 1)
		return;

	//error is the error for this model
	double error = 0.0;
	double output = 0.0;
	double outputError = 0.0;

	for (int fold = 0; fold < kFoldErrorSize; ++fold)
	{
		error += kFoldError[modelNumber][fold];
		output += kFoldOutput[modelNumber][fold];
		outputError += kFoldOutputError[modelNumber][fold];
	}

	error = error / kFoldErrorSize;
	output = output / kFoldErrorSize;
	outputError = outputError / kFoldErrorSize;

	//add this error to the modelError vector
	modelError.push_back(error);
	modelOutput.push_back(output);
	modelOutputError.push_back(outputError);

	//std::string test("test.list");
	saveModel(networkName);

	++modelNumber;
}

//**************************************************************************
//*********************  SERIALIZABLE METHODS   ****************************
//**************************************************************************

void ANN::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	int size; //this is the size of the current vector
	std::vector<int>::iterator itInt;
	std::vector<double>::iterator itDouble;
	std::vector<Node>::iterator itNode;
		
	if (ar.IsStoring())
	{
		//store the base network variables
		CString name(networkName.c_str());
		ar << name << numberOfLayers << learningRate << momentum;
		
		size = nodesPerLayer.size();
		ar << size;
		for(itInt = nodesPerLayer.begin(); itInt < nodesPerLayer.end(); ++itInt)
			ar << (*itInt);

		size = theNet.size();
		ar << size;
		for(itNode = theNet.begin(); itNode < theNet.end(); ++itNode)
			(*itNode).Serialize(ar);

		//store the k-fold variables
		ar << folds << epochs << runs << stoppingCriteria << startingLayer << endingLayer << startingPosition;

		size = hiddenStartNodes.size();
		ar << size;
		for(itInt = hiddenStartNodes.begin(); itInt < hiddenStartNodes.end(); ++itInt)
			ar << (*itInt);

		size = hiddenEndNodes.size();
		ar << size;
		for(itInt = hiddenEndNodes.begin(); itInt < hiddenEndNodes.end(); ++itInt)
			ar << (*itInt);

		//size = kFoldError.size();
		//ar << size;
		//for(itDouble = kFoldError.begin(); itDouble < kFoldError.end(); ++itDouble)
		//	ar << (*itDouble);

		size = modelError.size();
		ar << size;
		for(itDouble = modelError.begin(); itDouble < modelError.end(); ++itDouble)
			ar << (*itDouble);

		//store the attributes
		attributes.Serialize(ar);

		//store the values
		values.Serialize(ar);

		//store the links
//		links.Serialize(ar);

		//store the examples
		examples.Serialize(ar);
		
	}
	else
	{
		//temp variables
		int tempInt;
		double tempDouble;

		//load the base network variables
		CString name;
		ar >> name >> numberOfLayers >> learningRate >> momentum;
		CT2CA n(name);
		std::string newName(n);
		networkName = newName;

		ar >> size;
		nodesPerLayer.clear();
		for (int x = 0; x < size; ++x)
		{
			ar >> tempInt;
			nodesPerLayer.push_back(tempInt);
		}

		ar >> size;
		theNet.clear();
		Node temp;
		for (int x = 0; x < size; ++x)
		{
			temp.Serialize(ar);
			theNet.push_back(temp);
		}

		//load the k-fold variables
		ar >> folds >> epochs >> runs >> stoppingCriteria >> startingLayer >> endingLayer >> startingPosition;

		ar >> size;
		hiddenStartNodes.clear();
		for (int x = 0; x < size; ++x)
		{
			ar >> tempInt;
			hiddenStartNodes.push_back(tempInt);
		}

		ar >> size;
		hiddenEndNodes.clear();
		for (int x = 0; x < size; ++x)
		{
			ar >> tempInt;
			hiddenEndNodes.push_back(tempInt);
		}

	/*	ar >> size;
		kFoldError.clear();
		for (int x = 0; x < size; ++x)
		{
			ar >> tempDouble;
			kFoldError.push_back(tempDouble);
		}*/

		ar >> size;
		modelError.clear();
		for (int x = 0; x < size; ++x)
		{
			ar >> tempDouble;
			modelError.push_back(tempDouble);
		}

		//load attributes
		attributes.clear();
		attributes.Serialize(ar);

		//load values
		values.clear();
		values.Serialize(ar);

		//load links
//		links.clear();
//		links.Serialize(ar);

		//load examples
		examples.clear();
		examples.Serialize(ar);
	}
}

bool ANN::loadExampleFile(std::string& filename)
{
	std::cout << "trying to load : " << filename << std::endl;
	std::ifstream infile(filename);
	if (infile.is_open())
	{
		std::string line;
		while(std::getline(infile, line))
		{
			std::istringstream is(line);
			std::string s;

			//get the number of examples
			is >> s;
			std::stringstream numberof(s);
			int examps;
			numberof >> examps;

			//get the number of attributes
			is >> s;
			std::stringstream attnumber(s);
			int attSize;
			attnumber >> attSize;

			//get the number of values
			is >> s;
			std::stringstream valnumber(s);
			int valSize;
			valnumber >> valSize;

			//if the attribute size or the value size does not equal the number of attributes
			//or number of values, respectively, return false. This example set is different
			//from the make up of the current network

			int numAtts = attributes.getCount();
			int numVals = values.getCount();

			if (!(attSize == numAtts) || !(valSize == numVals))
				return false;

			//clear the current examples, if any
			examples.clear();
			examples.setAttributes(attributes);
			examples.setValues(values);

			std::vector<double> atts = std::vector<double>();
			std::vector<double> vals = std::vector<double>();
			double att;
			double val;
			for (int examId = 0; examId < examps; ++examId)
			{
				std::getline(infile, line);
				std::istringstream is(line);
				//clear the temp attribute and value
				atts.clear();
				vals.clear();

				for (int attCount = 0; attCount < attSize; ++attCount)
				{
					is >> s;
					std::stringstream attVal(s);
					attVal >> att;
					atts.push_back(att);
				}
				for (int valCount = 0; valCount < valSize; ++valCount)
				{
					is >> s;
					std::stringstream valVal(s);
					valVal >> val;
					vals.push_back(val);
				}
				examples.addExample(atts, vals);
			}
			infile.close();
			return true;
		}
	}
	std::cout << "Unable to open " << filename << std::endl;
	return false;
}

bool ANN::appendExampleFile(std::string& filename)
{
	std::ifstream infile(filename);
	if (infile.is_open())
	{
		std::string line;
		while(std::getline(infile, line))
		{
			std::istringstream is(line);
			std::string s;

			//get the number of examples
			is >> s;
			std::stringstream numberof(s);
			int examps;
			numberof >> examps;

			//get the number of attributes
			is >> s;
			std::stringstream attnumber(s);
			int attSize;
			attnumber >> attSize;

			//get the number of values
			is >> s;
			std::stringstream valnumber(s);
			int valSize;
			valnumber >> valSize;

			//if the attribute size or the value size does not equal the number of attributes
			//or number of values, respectively, return false. This example set is different
			//from the make up of the current network

			int numAtts = attributes.getCount();
			int numVals = values.getCount();

			if (!(attSize == numAtts) || !(valSize == numVals))
				return false;

			std::vector<double> atts = std::vector<double>();
			std::vector<double> vals = std::vector<double>();
			double att;
			double val;
			for (int examId = 0; examId < examps; ++examId)
			{
				std::getline(infile, line);
				std::istringstream is(line);
				//clear the temp attribute and value
				atts.clear();
				vals.clear();

				for (int attCount = 0; attCount < attSize; ++attCount)
				{
					is >> s;
					std::stringstream attVal(s);
					attVal >> att;
					atts.push_back(att);
				}
				for (int valCount = 0; valCount < valSize; ++valCount)
				{
					is >> s;
					std::stringstream valVal(s);
					valVal >> val;
					vals.push_back(val);
				}
				examples.addExample(atts, vals);
			}
			infile.close();
			return true;
		}
	}
	return false;
}

bool ANN::saveExamples(std::string& filename)
{
	std::ofstream out(filename);
	if (out.is_open())
	{
		int eSize = examples.getCount();
		int aSize = attributes.getCount();
		int vSize = values.getCount();
		std::vector<double> atts = std::vector<double>();
		std::vector<double> vals = std::vector<double>();

		out << eSize << " " << aSize << " " << vSize << std::endl;
		Example temp = Example();
		
		examples.resetPosition();

		for (int x = 0; x < eSize; ++x)
		{
			temp = examples.getNextExample(temp);
			atts.clear();
			vals.clear();
			atts = temp.getAttributes(atts);
			vals = temp.getValues(vals);

			std::vector<double>::iterator it;
			for (it = atts.begin(); it < atts.end(); ++it)
				out << (*it) << " ";
			for (it = vals.begin(); it < vals.end(); ++it)
				out << (*it) << " ";
			out << std::endl;
		}		
		out.close();
		return true;
	}
	return false;
}

bool ANN::saveModel(std::string& filename)
{
	std::stringstream mn;
	mn << modelNumber;
	std::string temp(mn.str());
	std::string fileName(filename);
	fileName += temp;
	fileName += ".list";
	std::ofstream out(fileName);
	if (out.is_open())
	{
		//************************************************
		//************** 2 27 2011 ***********************
		//************************************************
		//save the seed for this model
		if (testType == 0)
			out << "ANN" << std::endl;
		else if (testType == 1)
			out << "IANN" << std::endl;

		out << "Seed : " << currentSeed << std::endl;
		//end 2 27 2011


		//save the nodes of the network
		int inputNodes = nodesPerLayer[0];
		int outputNodes = nodesPerLayer[numberOfLayers - 1];
		
		out << "Input Nodes : " << inputNodes << " ";
		if (numberOfLayers >= 3 && nodesPerLayer[1] > 0)
		{
			out << "Hidden 1 Nodes : " << nodesPerLayer[1] << " ";
			if (numberOfLayers >= 4 && nodesPerLayer[2] > 0)
			{
				out << "Hidden 2 Nodes : " << nodesPerLayer[2] << " ";
				if (numberOfLayers >= 5 && nodesPerLayer[3] > 0)
				{
					out << "Hidden 3 Nodes : " << nodesPerLayer[3] << " ";
					if (numberOfLayers >= 6 && nodesPerLayer[4] > 0)
					{
						out << "Hidden 4 Nodes : " << nodesPerLayer[4] << " ";
					}
				}
			}
		}
		out << "Output Nodes : " << outputNodes << std::endl;

		//save the kfold parameters
		out << "K-Fold Parameters : " << std::endl;
		out << "Folds : " << folds << " Max Epochs : " << epochs << " Stopping Criteria : " << stoppingCriteria << " Consecutive Runs : " << runs << std::endl;
		out << "Starting Layer : " << startingLayer << " Ending Layer : " << endingLayer << std::endl;
		if (numberOfLayers >= 3 && hiddenStartNodes[0] > 0)
		{
			out << "First Hidden Layer Start Nodes : " << hiddenStartNodes[0] << " First Hidden Layer End Nodes : " << hiddenEndNodes[0] << std::endl;
			if (numberOfLayers >= 4 && hiddenStartNodes[1] > 0)
			{
				out << "Second Hidden Layer Start Nodes : " << hiddenStartNodes[1] << " Second Hidden Layer End Nodes : " << hiddenEndNodes[1] << std::endl;
				if (numberOfLayers >= 5 && hiddenStartNodes[2] > 0)
				{
					out << "Third Hidden Layer Start Nodes : " << hiddenStartNodes[2] << " Third Hidden Layer End Nodes : " << hiddenEndNodes[2] << std::endl;
					if (numberOfLayers >=6 && hiddenStartNodes[3] > 0)
					{
						out << "Fourth Hidden Layer Start Nodes : " << hiddenStartNodes[3] << " Fourth Hidden Layer End Nodes : " << hiddenEndNodes[3] << std::endl;
					}
				}
			}
		}

		//save start position of the example files and examples
		out << "Starting Example Position : " << startingPosition << " ";

		std::string file("savemodel.list");
		saveExamples(file);
		out << "Example File Name : " << file << std::endl;

		//save the error for this model
		out << "Average Model Output : " << modelOutput[modelNumber] << "\nAverage Model Error : " << modelError[modelNumber] << "\nAverage Model Squared Error : " << modelOutputError[modelNumber] << std::endl;

		//save the kFold errors
		int kSize = kFoldError[modelNumber].size();
		for (int x = 0; x < kSize; ++x)
		{
			out << x + 1 << ": Avg Fold Output : " << kFoldOutput[modelNumber][x] << " Avg Fold Error : " << kFoldError[modelNumber][x] << " Avg Fold Squared Error : " << kFoldOutputError[modelNumber][x] << " Num Epochs : " << epochCount[modelNumber][x] << std::endl;
		}
		int size = kFoldWithin01[modelNumber].size();
		for (int x = 0; x < size; ++x)
		{
			out << "x is the number of test examples within left hand range" << std::endl;
			out << "0 <= x <= 1 : " << kFoldWithin01[modelNumber][x] << "\n1 < x <= 5 : " << kFoldWithin05[modelNumber][x] << "\n5 < x <= 10 : " << kFoldWithin10[modelNumber][x] << "\n10 < x <= 25 : " << kFoldWithin25[modelNumber][x] << "\n25 < x : " << kFoldMoreThan25[modelNumber][x] << std::endl;
			out << std::endl;
		}

		out.close();
		return true;
	}
	return false;
}

bool ANN::loadAttributeFile(std::string& filename)
{
	std::ifstream infile(filename);
	if(infile.is_open())
	{
		std::string line;
		while(std::getline(infile, line))
		{
			std::istringstream is(line);
			std::string s;

			//get the number of attributes
			is >> s;
			std::stringstream nAtts(s);
			int attSize;
			nAtts >> attSize;

			//clear attributes
			attributes.clear();

			std::string name;
			double min;
			double max;
			double fri;

			for (int x = 0; x < attSize; ++x)
			{
				std::getline(infile, line);
				std::istringstream is(line);

				is >> name;

				is >> s;
				std::stringstream minVal(s);
				minVal >> min;

				is >> s;
				std::stringstream maxVal(s);
				maxVal >> max;

				is >> s;
				std::stringstream friVal(s);
				friVal >> fri;

				attributes.addAttribute(name, min, max, fri);
			}
			infile.close();
			return true;
		}
	}
	return false;
}

bool ANN::loadValueFile(std::string& filename)
{
	std::ifstream infile(filename);
	if (infile.is_open())
	{
		std::string line;
		while(std::getline(infile, line))
		{
			std::istringstream is(line);
			std::string s;

			//get the number of values
			is >> s;
			std::stringstream nVals(s);
			int valSize;
			nVals >> valSize;

			//clear values
			values.clear();

			std::string name;
			double min;
			double max;

			for (int x = 0; x < valSize; ++x)
			{
				std::getline(infile, line);
				std::istringstream is(line);

				is >> name;

				is >> s;
				std::stringstream minVal(s);
				minVal >> min;

				is >> s;
				std::stringstream maxVal(s);
				maxVal >> max;

				values.addValue(name, min, max);
			}
			infile.close();
			return true;
		}
	}
	return false;
}

int ANN::getExampleCount()
{
	return examples.getCount();
}

void ANN::shuffleExamples()
{
	examples.randomizeExamples();
}

void ANN::saveOutput()
{
	std::stringstream file;
	file << "results_" << testType << "_" << testsRun << ".list";
	std::ofstream out(file.str());
	if (out.is_open())
	{
		//************************************************
		//************** 2 27 2011 ***********************
		//************************************************
		if (testType == 0)
			out << "ANN" << std::endl;
		else if (testType == 1)
			out << "IANN" << std::endl;

		out << "Run : " << (testsRun + 1) << "\nSeed : " << currentSeed << std::endl;
		//end 2 27 2011

		int count = exampleSetOutput.size();
		out << "Example # \t\tOutput" << std::endl;
		for (int id = 0; id < count; ++id)
		{
			out << id << "\t\t\t" << exampleSetOutput[id] << std::endl;
		}
		out.close();
	}
}

bool ANN::loadOutputExamples(std::string& filename)
{
	std::ifstream in(filename);
	if (in.is_open())
	{
		std::string line;
		while(std::getline(in, line))
		{
			std::istringstream is(line);
			std::string s;

			//get the number of examples
			is >> s;
			std::stringstream numberof(s);
			int examps;
			numberof >> examps;

			//get the number of attributes
			is >> s;
			std::stringstream attnumber(s);
			int attSize;
			attnumber >> attSize;

			//get the number of values
			is >> s;
			std::stringstream valnumber(s);
			int valSize;
			valnumber >> valSize;

			int numAtts = attributes.getCount();
			int numVals = values.getCount();

			if (!(attSize == numAtts) || !(valSize == numVals))
				return false;

			//clear the current examples
			outputExamples.clear();
			outputExamples.setAttributes(attributes);
			outputExamples.setValues(values);

			std::vector<double> atts = std::vector<double>();
			std::vector<double> vals = std::vector<double>();
			double att;
			double val = -1.0;
			vals.push_back(val);
			for (int examId = 0; examId < examps; ++examId)
			{
				std::getline(in, line);
				std::istringstream is(line);
				//clear the temp attributes and values
				atts.clear();

				for (int attCount = 0; attCount < attSize; ++attCount)
				{
					is >> s;
					std::stringstream attVal(s);
					attVal >> att;
					atts.push_back(att);
				}
				outputExamples.addExample(atts, vals);
			}
			in.close();
			return true;
		}
	}
	return false;
}

//private methods
//**************************************************************************
//*************************  HELPER METHODS   ******************************
//**************************************************************************
int ANN::concatinateId(int from, int to)
{
	if (to >= 10000)
		return from * 100000 + to;
	if (to >= 1000)
		return from * 10000 + to;
	if (to >= 100)
		return from * 1000 + to;
	if (to >= 10)
		return from * 100 + to;
	return from * 10 + to;
}

int ANN::getFirstIdOfLayer(int layer)
{
	int size = theNet.size();
	for (int id = 0; id < size; ++id)
		if (theNet[id].getLayer() == layer)
			return id;
	return -1;
}

int ANN::getLastIdOfLayer(int layer)
{
	int size = theNet.size();
	int first = getFirstIdOfLayer(layer);
	for (int id = first; id < size; ++id)
		if (theNet[id].getLayer() > layer)
			return (id - 1);
	if (theNet[size- 1].getLayer() == layer)
		return (size - 1); //if this is the last node of the output layer
	return -1;
}

void ANN::setLayerStart()
{
	layerStart.clear();
	for(int x = 0; x < numberOfLayers; ++x)
		layerStart.push_back(getFirstIdOfLayer(x));
}

void ANN::setLayerEnd()
{
	layerEnd.clear();
	for(int x = 0; x < numberOfLayers; ++x)
		layerEnd.push_back(getLastIdOfLayer(x));
}

std::vector<double>& ANN::getNetworkOutput(std::vector<double>& out)
{
	out.clear();

	int start = layerStart[numberOfLayers - 1];
	int end = layerEnd[numberOfLayers - 1];

	for (int x = start; x <= end; ++x)
		out.push_back(theNet[x].getOutput());

	return out;
}

std::vector<double>& ANN::getNetworkOutputError(std::vector<double>& out)
{
	out.clear();

	int start = layerStart[numberOfLayers - 1];
	int end = layerEnd[numberOfLayers - 1];

	for (int x = start; x <= end; ++x)
		out.push_back(theNet[x].getOutputError());

	return out;
}

//**************************************************************************
//**********************  NETWORK CREATION METHODS   ***********************
//**************************************************************************
void ANN::buildNetwork()
{
	//add alll the nodes to the network with and individual node id and layer id
	//the first node id is 1 (there is an empty node in theNet[0]
	theNet.clear();
	theNet.push_back(Node(0,-1));

	int id = 1;
	int layer = 0;
	int count = 0;
	
	std::vector<int>::iterator layerIter;
	std::vector<int> tempNetwork = std::vector<int>();

	for (layerIter = nodesPerLayer.begin(); layerIter < nodesPerLayer.end(); ++layerIter)
	{
		for (count = 0; count < (*layerIter); ++count)
		{
			theNet.push_back(Node(id, layer));
			++id;
		}
		if (count > 0) //if there were any nodes in the layer just added, add those to the tempNetwork
		{
			tempNetwork.push_back(count);
			++layer;
		}
	}
	int size = theNet.size();
	//reset the network parameters according to the network made
	//i.e. if any of the layers in the previous nodesPerLayer were 0 or less they were removed
	nodesPerLayer.clear();
	nodesPerLayer = tempNetwork;
	numberOfLayers = layer;
	setLayerStart();
	setLayerEnd();

	//************************************************
	//************** 2 27 2011 ***********************
	//************************************************
	//set the random seed
	srand(currentSeed);
	//end 2 27 2011
}

void ANN::buildLinks()
{
	int conId = 0;
	int startOfFromLayer;
	int endOfFromLayer;
	int startOfToLayer;
	int endOfToLayer;
	int size = nodesPerLayer.size();
	double weight;

	for (int layer = 0; layer < size - 1; ++layer)
	{
		startOfFromLayer = layerStart[layer];
		endOfFromLayer = layerEnd[layer];
		startOfToLayer = layerStart[layer + 1];
		endOfToLayer = layerEnd[layer + 1];
		for (int from = startOfFromLayer; from <= endOfFromLayer; ++from)
		{
			for (int to = startOfToLayer; to <= endOfToLayer; ++to)
			{
				theLinks[from][to] = Link(from, to, conId);
				weight = RN * 2 - 1;
				theLinks[from][to].setWeight(weight);
			}
		}
	}
}

void ANN::buildIANNLinks()
{
	int conId = 0;
	int startOfFromLayer;
	int endOfFromLayer;
	int startOfToLayer;
	int endOfToLayer;
	int size = nodesPerLayer.size();
	double weight;
	int FRILinks;

	for (int layer = 0; layer < size - 1; ++layer)
	{
		startOfFromLayer = layerStart[layer];
		endOfFromLayer = layerEnd[layer];
		startOfToLayer = layerStart[layer + 1];
		endOfToLayer = layerEnd[layer + 1];
		if (layer == 0)
		{
			int range = endOfToLayer - startOfToLayer + 1;
			int start = startOfToLayer;
			for (int from = startOfFromLayer; from <= endOfFromLayer; ++from)
			{
				FRILinks = (int)(RN * range + 1); //get the number of random FRI links to use
				for (int to = startOfToLayer; to <= endOfToLayer; ++to)
				{
					int choice = (int)(RN * 100 + 1);
					int chance = (int)(RN * 100 + 1);
					if (choice > chance && FRILinks > 0)
					{
						theLinks[from][to] = Link(from, to, conId);
						int sign = (int)(RN * 100 + 1);
						weight = attributes.getFri(from - 1);
						if (sign > 50)
							weight = -weight;
						
						theLinks[from][to].setWeight(weight);
						--FRILinks;
					}
					else
					{
						theLinks[from][to] = Link(from, to, conId);
						weight = RN - 0.5;
						theLinks[from][to].setWeight(weight);
					}
				}
			}
		}
		else
		{
			for(int from = startOfFromLayer; from <= endOfFromLayer; ++from)
			{
				for(int to = startOfToLayer; to <= endOfToLayer; ++to)
				{
					theLinks[from][to] = Link(from, to, conId);
					weight = RN * 2 - 1;
					theLinks[from][to].setWeight(weight);
				}
			}
		}
	}
}

void ANN::buildBiasLinks()
{
	int conId;
	int end = layerEnd[numberOfLayers - 1];
	int start = layerStart[0];
	//theLinks = std::vector<std::vector<Link>>(end+1, end+1);
	theLinks.resize(end + 1);
	for (int i = 0; i < end + 1; i++)
	{
		theLinks[i].resize(end + 1);
	}
	double weight;

	for (int id = start; id <= end; ++id)
	{
		conId = concatinateId(10000, id);
		theLinks[0][id] = Link(0, id, conId);
		weight = RN * 2 - 1;
		theLinks[0][id].setWeight(weight);
	}
}

//**************************************************************************
//************   RUNNING & EVALUATE EXAMPLE(S) METHODS   *******************
//**************************************************************************

//runs one example through the network, saving the output values in the respective output nodees
void ANN::runExample(Example& example)
{
	double val;
	
	//set the output values for the input layer
	int start = layerStart[0];
	int end = layerEnd[0];
	//id is the id of the input layer node (they start at 1)
	//the corresponding attribute is id - 1 (attributes start at 0)
	for(int id = start; id <= end; ++id)
	{
		val = example.getNormalizedAttribute(id - 1);
		theNet[id].setOutput(val);
		theNet[id].setSumIntoNode(val);
	}

	//set the sum into node values and output values for the first hidden layer
	int firstHidden = layerStart[1];
	int lastHidden = layerEnd[1];
	int firstInput = layerStart[0];
	int lastInput = layerEnd[0];
	for (int id = firstHidden; id <= lastHidden; ++id)
	{
		//sum the values into the node id
		val = 0.0;
		for (int inputId = firstInput; inputId <= lastInput; ++inputId)
		{
			val += theLinks[inputId][id].getWeight() * theNet[inputId].getOutput();
		}
		//subtract the weight of the bias link (i.e. bias link weight * -1)
		val += theLinks[0][id].getWeight();
		//save the sum into this node
		theNet[id].setSumIntoNode(val);
		//apply the activation function to the sum into the node
		val = logistic(val);
		//save the value just computed as the output of this node
		theNet[id].setOutput(val);
	}

	//if there is a second layer, run that layer
	int size = nodesPerLayer.size();
	if (size > 3)
	{
		int startSecondHidden = layerStart[2];
		int endSecondHidden = layerEnd[2];
		for (int id = startSecondHidden; id <= endSecondHidden; ++id)
		{
			//sum the values into the node id
			val = 0.0;
			for (int inputId = firstHidden; inputId <= lastHidden; ++inputId)
				val += theLinks[inputId][id].getWeight() * theNet[inputId].getOutput();

			//subtract the weight of the bias link
			val += theLinks[0][id].getWeight();
			//save the sum into this nod
			theNet[id].setSumIntoNode(val);
			//apply the activation function to the sum into the node
			val = logistic(val);
			//save the value just computed as the output of this node
			theNet[id].setOutput(val);
		}
	}

	//set the sum into node value and output value for the output node
	firstHidden = layerStart[numberOfLayers - 2];
	lastHidden = layerEnd[numberOfLayers - 2];
	int outId = layerEnd[numberOfLayers - 1];
	val = 0.0;
	for (int prevId = firstHidden; prevId <= lastHidden; ++prevId)
	{
		val += theLinks[prevId][outId].getWeight() * theNet[prevId].getOutput();
	}
	//subtract the weight of the bias link
	val += theLinks[0][outId].getWeight();
	//save the sum into the output node
	theNet[outId].setSumIntoNode(val);
	//apply the activation funciton to the sum into the output node
	val = logistic(val);
	//save the value just computed as the output of the output node
	theNet[outId].setOutput(val);

}

//evaluates the error for the example given and stores the error of each output node
//in the respective node
//this method assumes:
//1)runExample was just executed
//2)the example used in runExample is the same input example to this method
void ANN::evaluateOutputError(Example& example)
{
	double expectedOut;
	double actualOut;
	double dlog;
	double error;
	int count = 0;
	//get the expected output for this example
	std::vector<double> expected = std::vector<double>();
	expected = example.getValues(expected);

	int start = layerStart[numberOfLayers - 1];
	int end = layerEnd[numberOfLayers - 1];

	for (int outId = start; outId <= end; ++outId)
	{
		expectedOut = expected[count];
		actualOut = theNet[outId].getOutput();
		dlog = Dlogistic(theNet[outId].getSumIntoNode());
		//dlog = Dlogistic(actualOut);
		error = dlog * (expectedOut - actualOut);
		theNet[outId].setError(error);
		double outError = (expectedOut - actualOut) * (expectedOut - actualOut) * 0.5;
		theNet[outId].setOutputError(outError);
	}
}

//This method performs the back propagation to the network
//should only be run after runExample and evaluateOutputError
void ANN::adjustLinkWeights()
{
	//propagate the error of the output back through the network
	//giveing each link a portion of the "blame" for the incorrect results

	double dlog = 0.0;
	double error = 0.0;
	double weight = 0.0;
	double delta = 0.0;
	int startFrom;
	int endFrom;
	int startTo;
	int endTo;

	//starting with the layer before the output layer, work backwards until
	//we update all links, layer by layer
	//start with numberOfLayers -2 (first layer is 0, last layer is numberOfLayers - 1)
	for (int layer = numberOfLayers - 2; layer >= 0; --layer)
	{
		startFrom = layerStart[layer];
		endFrom = layerEnd[layer];
		for (int from = startFrom; from <= endFrom; ++from)
		{
			dlog = Dlogistic(theNet[from].getSumIntoNode());
			//dlog = Dlogistic(theNet[from].getOutput());
			error = 0.0;
			startTo = layerStart[layer + 1];
			endTo = layerEnd[layer + 1];
			for (int to = startTo; to <= endTo; ++to)
			{
				error += theLinks[from][to].getWeight() * theNet[to].getError();
			}
			theNet[from].setError(dlog * error);

			for (int to = startTo; to <= endTo; ++to)
			{
				delta = learningRate * theNet[from].getOutput() * theNet[to].getError() + momentum * theLinks[from][to].getDeltaWeight();
				weight = theLinks[from][to].getWeight();
				weight += delta;

				theLinks[from][to].setWeight(weight);
				theLinks[from][to].setDeltaWeight(delta);
			}
			////adjust the bias weight
			//delta = learningRate * theNet[from].getError() + momentum * theLinks[0][from].getDeltaWeight();
			//weight = theLinks[0][from].getWeight();
			//weight += delta;

			//theLinks[0][from].setWeight(weight);
			//theLinks[0][from].setDeltaWeight(delta);
		}
	}				
}

void ANN::adjustIANNLinkWeights()
{
	double dlog = 0.0;
	double error = 0.0;
	double weight = 0.0;
	double delta = 0.0;
	int startFrom;
	int endFrom;
	int startTo;
	int endTo;

	for (int layer = numberOfLayers - 2; layer >= 0; --layer)
	{
		startFrom = layerStart[layer];
		endFrom = layerEnd[layer];
		if (layer == 0)
		{
			for (int from = startFrom; from <= endFrom; ++from)
			{
				dlog = Dlogistic(theNet[from].getSumIntoNode());
				error = 0.0;
				startTo = layerStart[layer + 1];
				endTo = layerEnd[layer + 1];
				for (int to = startTo; to <= endTo; ++to)
				{
					error += theLinks[from][to].getWeight() * theNet[to].getError();
				}
				theNet[from].setError(dlog * error);

				for (int to = startTo; to <= endTo; ++to)
				{
					delta = learningRate * theNet[from].getOutput() * theNet[to].getError() * attributes.getFri(from - 1) +
						momentum * theLinks[from][to].getDeltaWeight();
					weight = theLinks[from][to].getWeight();
					weight += delta;

					theLinks[from][to].setWeight(weight);
					theLinks[from][to].setDeltaWeight(delta);
				}
				
			}
		}
		else
		{
			for (int from = startFrom; from <= endFrom; ++from)
			{
				dlog = Dlogistic(theNet[from].getSumIntoNode());
				error = 0.0;
				startTo = layerStart[layer + 1];
				endTo = layerEnd[layer + 1];
				for (int to = startTo; to <= endTo; ++to)
				{
					error += theLinks[from][to].getWeight() * theNet[to].getError();
				}
				theNet[from].setError(dlog * error);

				for (from = startFrom; from <= endFrom; ++from)
				{
					for (int to = startTo; to <= endTo; ++to)
					{
						delta = learningRate * theNet[from].getOutput() * theNet[to].getError() + momentum * theLinks[from][to].getDeltaWeight();
						weight = theLinks[from][to].getWeight();
						weight += delta;

						theLinks[from][to].setWeight(weight);
						theLinks[from][to].setDeltaWeight(delta);
					}
				}
			}
		}
	}
}

//**************************************************************************
//**************   INTERFACE FOR MFC FRONT END METHODS   *******************
//**************************************************************************

//*********************************************************************
//***********************  ATTRIBUTE METHODS  *************************
//*********************************************************************
//accessor methods
double ANN::getAttributeMin(std::string& name)
{
	int id = attributes.getId(name);
	if (id == -1)
		return 0.0;
	return attributes.getMin(id);
}
double ANN::getAttributeMax(std::string& name)
{
	int id = attributes.getId(name);
	if (id == -1)
		return 0.0;
	return attributes.getMax(id);
}
double ANN::getAttributeFri(std::string& name)
{
	int id = attributes.getId(name);
	if (id == -1)
		return 0.0;
	return attributes.getFri(id);
}
std::string ANN::getAttributeName(int index)
{
	return attributes.getNameByIndex(index);
}
double ANN::getAttributeMin(int index)
{
	return attributes.getMinByIndex(index);
}
double ANN::getAttributeMax(int index)
{
	return attributes.getMaxByIndex(index);
}
double ANN::getAttributeFri(int index)
{
	return attributes.getFriByIndex(index);
}
int ANN::getNumberOfAttributes()
{
	return attributes.getCount();
}

//mutator methods
bool ANN::addAttribute(std::string& name, double min, double max, double fri)
{
	return attributes.addAttribute(name, min, max, fri);
}
bool ANN::editAttribute(std::string& previousName, std::string& editName, double min, double max, double fri)
{
	int id = attributes.getId(previousName);
	if (id == -1)
		return false;
	attributes.changeName(id, editName);
	attributes.changeMin(id, min);
	attributes.changeMax(id, max);
	attributes.changeFri(id, fri);
	return true;
}
bool ANN::removeAttribute(std::string& name)
{
	int id = attributes.getId(name);
	if (id == -1)
		return false;
	return attributes.removeAttribute(id);
}

//*********************************************************************
//************************  VALUE METHODS  ****************************
//*********************************************************************
//accessor methods
double ANN::getValueMin(std::string& name)
{
	int id = values.getId(name);
	if (id == -1)
		return 0.0;
	return values.getMin(id);
}
double ANN::getValueMax(std::string& name)
{
	int id = values.getId(name);
	if (id == -1)
		return 0.0;
	return values.getMax(id);
}
std::string ANN::getValueName(int index)
{
	return values.getNameByIndex(index);
}
double ANN::getValueMin(int index)
{
	return values.getMinByIndex(index);
}
double ANN::getValueMax(int index)
{
	return values.getMaxByIndex(index);
}
int ANN::getNumberOfValues()
{
	return values.getCount();
}

//mutator methods
bool ANN::addValue(std::string& name, double min, double max)
{
	return values.addValue(name, min, max);
}
bool ANN::editValue(std::string& previousName, std::string& editName, double min, double max)
{
	int id = values.getId(previousName);
	if (id == -1)
		return false;
	values.changeName(id, editName);
	values.changeMin(id, min);
	values.changeMax(id, max);
	return true;
}
bool ANN::removeValue(std::string& name)
{
	int id = values.getId(name);
	if (id == -1)
		return false;
	return values.removeValue(id);
}

//*********************************************************************
//****************  K-FOLD CROSS-VALIDATION METHODS  ******************
//*********************************************************************
//accessor methods
int ANN::getFolds()
{
	return folds;
}
int ANN::getEpochs()
{
	return epochs;
}
int ANN::getConsecutiveRuns()
{
	return runs;
}
double ANN::getStoppingCriteria()
{
	return stoppingCriteria;
}
int ANN::getStartingPosition()
{
	return startingPosition;
}
std::vector<int>& ANN::getNumberOfStartingHiddenNodes(std::vector<int>& starting)
{
	starting = hiddenStartNodes;
	return starting;
}
std::vector<int>& ANN::getNumberOfEndingHiddenNodes(std::vector<int>& ending)
{
	ending = hiddenEndNodes;
	return ending;
}
int ANN::getFoldStartingLayer()
{
	int size = nodesPerLayer.size();
	if (size == 2)
		return 0;
	return 1;
}
int ANN::getFoldEndingLayer()
{
	int size = nodesPerLayer.size();
	if (size == 2)
		return 0;
	return (size - 2);
}
int ANN::getFoldStartingNodeAtLayer(int layer)
{
	int size = hiddenStartNodes.size();
	if (layer >= 0 && layer < size)
		return hiddenStartNodes[layer];
	return 0;
}
int ANN::getFoldEndingNodeAtLayer(int layer)
{
	int size = hiddenEndNodes.size();
	if (layer >= 0 && layer < size)
		return hiddenEndNodes[layer];
	return 0;
}

//mutator methods
void ANN::setFolds(int folds)
{
	this->folds = folds;
}
void ANN::setEpochs(int epochs)
{
	this->epochs = epochs;
}
void ANN::setConsecutiveRuns(int runs)
{
	this->runs = runs;
}
void ANN::setStoppingCriteria(double stopping)
{
	stoppingCriteria = stopping;
}
bool ANN::setStartingPosition(int starting)
{
	int count = examples.getCount();
	if (starting >= 0 && starting < count)
	{
		startingPosition = starting;
		return true;
	}
	return false;
}
void ANN::setNumberOfStartingHiddenNodes(std::vector<int>& starting)
{
	hiddenStartNodes = starting;
}
void ANN::setNumberOfEndingHiddenNodes(std::vector<int>& ending)
{
	hiddenEndNodes = ending;
}
void ANN::setKFoldParameters(int folds, int epochs, double criteria, int runs, int startingLayer, int endingLayer,
	std::vector<int>& startingNodes, std::vector<int>& endingNodes)
{
	this->folds = folds;
	this->epochs = epochs;
	this->stoppingCriteria = criteria;
	this->runs = runs;
	this->startingLayer = startingLayer;
	this->endingLayer = endingLayer;
	hiddenStartNodes = startingNodes;
	hiddenEndNodes = endingNodes;
}	
void ANN::setKFoldStartingNodeAtLayer(int layer, int nodes)
{
	int size = hiddenStartNodes.size();
	if (layer >= 0 && layer < size)
		hiddenStartNodes[layer] = nodes;
}
void ANN::setKFoldEndingNodeAtLayer(int layer, int nodes)
{
	int size = hiddenEndNodes.size();
	if (layer >= 0 && layer < size)
		hiddenEndNodes[layer] = nodes;
}

//*********************************************************************
//**********************  NETWORK METHODS  ****************************
//*********************************************************************
//accessor methods
std::string ANN::getNetworkName()
{
	return networkName;
}
int ANN::getNumberOfLayers()
{
	return numberOfLayers;
}
double ANN::getLearningRate()
{
	return learningRate;
}
double ANN::getMomentum()
{
	return momentum;
}
int ANN::getNodesAtLayer(int layer)
{
	int size = nodesPerLayer.size();
	if (layer >= 0 && layer < size)
		return nodesPerLayer[layer];
	return 0;
}
int ANN::getInputNodes()
{
	return nodesPerLayer[0];
}
int ANN::getOutputNodes()
{
	int size = nodesPerLayer.size();
	if (size >= 2)
		return nodesPerLayer[size - 1];
	return 0;
}
int ANN::getHidden1()
{
	int size = nodesPerLayer.size();
	if (size >= 3)
		return nodesPerLayer[1];
	return 0;
}
int ANN::getHidden2()
{
	int size = nodesPerLayer.size();
	if (size >= 4)
		return nodesPerLayer[2];
	return 0;
}
int ANN::getHidden3()
{
	int size = nodesPerLayer.size();
	if (size >= 5)
		return nodesPerLayer[3];
	return 0;
}
int ANN::getHidden4()
{
	int size = nodesPerLayer.size();
	if (size >= 6)
		return nodesPerLayer[4];
	return 0;
}

//mutator methods
void ANN::setNetworkName(std::string& name)
{
	networkName = name;
}
void ANN::setNumberOfLayers(int layers)
{
	numberOfLayers = layers;
}
void ANN::setLearningRate(double learning)
{
	learningRate = learning;
}
void ANN::setMomentum(double momentum)
{
	this->momentum = momentum;
}
void ANN::setNodesPerLayer(std::vector<int>& nodes)
{
	nodesPerLayer = nodes;
}

//*********************************************************************
//*********************  NEW CODE 2 27 2011  **************************
//*********************************************************************

void ANN::setUserSeed(int seed)
{
	if (seed <= 0)
	{
		long ltime = time(NULL);
		userSeed = (unsigned)(ltime);
	}
	else
		userSeed = seed;
	currentSeed = userSeed;
}

void ANN::setConsecutiveTests(int tests)
{
	 if (tests >= 1) 
		 numTests = tests; 
	 else 
		 numTests = 1;
}

void ANN::setNewSeed()
{
	long ltime = time(NULL);
	currentSeed = (unsigned)(ltime);
}

void ANN::runConsecutiveTests()
{
	testType = 0; //set test type to ANN
	for (testsRun = 0; testsRun < numTests; ++testsRun)
	{
		if (testsRun > 0)
			setNewSeed();
		createNetwork();
		trainNetwork();
		if (outputExamples.getCount() > 0) 
			runExamples(outputExamples);
	}
	//testType = 1; //set test type to IANN
	//testsRun = 0;
	//currentSeed = userSeed;
	//for (testsRun = 0; testsRun < numTests; ++testsRun)
	//{
	//	if (testsRun > 0)
	//		setNewSeed();
	//	createIANNNetwork();
	//	trainIANNNetwork();
	//	if (outputExamples.getCount() > 0) 
	//		runExamples(outputExamples);
	//}
	
}

void ANN::runConsecutiveIANNTests()
{
	testType = 1;
	testsRun = 0;
	currentSeed = userSeed;
	for (testsRun = 0; testsRun < numTests; ++testsRun)
	{
		if (testsRun > 0 )
			setNewSeed();
		createIANNNetwork();
		trainIANNNetwork();
		if (outputExamples.getCount() > 0)
			runExamples(outputExamples);
	}
}
