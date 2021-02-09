
// Neural NetDoc.h : interface of the CNeuralNetDoc class
//


#pragma once

#include "ANN.h"
#include "ErrorDlg.h"

class CNeuralNetDoc : public CDocument
{
protected: // create from serialization only
	CNeuralNetDoc();
	DECLARE_DYNCREATE(CNeuralNetDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CNeuralNetDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

	//private variables
private:
	ANN* theNet;
	//public accessor methods
public:
	//netork accessor methods
	CString getNetName();
	int getNetNodesLayer(int layerNumber);
	double getNetLearningRate();
	double getNetMomentum();
	int getNumberOfLayers();
	int getNetInput();
	int getNetOutput();
	int getNetHidden1();
	int getNetHidden2();
	int getNetHidden3();
	int getNetHidden4();

	//K-fold accessor methods
	int getFoldFolds();
	int getFoldEpochs();
	int getFoldRuns();
	double getFoldCriteria();
	int getFoldStartingLayer();
	int getFoldEndingLayer();
	int getStartingNodeLayer(int layer);
	int getEndingNodeLayer(int layer);

	//attribute accessor methods
	double getAttributeMin(CString name);
	double getAttributeMax(CString name);
	double getAttributeFri(CString name);
	CString getAttributeName(int index);
	double getAttributeMin(int index);
	double getAttributeMax(int index);
	double getAttributeFri(int index);
	int getAttributeNumber();

	//value accessor methods
	double getValueMin(CString name);
	double getValueMax(CString name);
	CString getValueName(int index);
	double getValueMin(int index);
	double getValueMax(int index);
	int getValueNumber();

	//example accessor methods
	bool getHaveExamples();
	int getExampleCount();
	int getStartingPosition();
	


	//public mutator methods
	//network mutator methods
	bool createNetwork(CString name, int input, int output, double learning, double momentum,
		int hidden1 = 0, int hidden2 = 0, int hidden3 = 0, int hidden4 = 0);
	bool editNetwork(CString name, int input, int output, double learning, double momentum,
		int hidden1 = 0, int hidden2 = 0, int hidden3 = 0, int hidden4 = 0);
	bool setNetworkName(CString name);
	bool setNetworkInput(int input);
	bool setNetworkOutput(int output);
	bool setNetworkLearning(double learning);
	bool setNetworkMomentum(double momentum);
	bool setHiddenLayerNodes(int layer, int nodes);
	void resetNetwork();

	//K-fold mutator methods
	bool setKFoldParameters(int folds, int epochs, double criteria, int runs, int startingLayer, int endingLayer,
		int starting1 = 0, int starting2 = 0, int starting3 = 0, int starting4 = 0,
		int ending1 = 0, int ending2 = 0, int ending3 = 0, int ending4 = 0);
	bool setKFoldFolds(int folds);
	bool setKFoldEpochs(int epochs);
	bool setKFoldCriteria(double criteria);
	bool setKFoldRuns(int runs);
	bool setKFoldStartingLayer(int layer);
	bool setKFoldEndingLayer(int layer);
	bool setKFoldStartingNodeLayer(int layer, int nodes);
	bool setKFoldEndingNodeLayer(int layer, int nodes);
	bool runKFoldModel();

	//attribute mutator methods
	bool addAttribute(CString name, double min, double max, double fri = 1.0);
	bool editAttribute(CString previousName, CString editName, double min, double max, double fri = 1.0);
	bool deleteAttribute(CString name);
	bool loadAttributes(CString filename);

	//value mutator methods
	bool addValue(CString name, double min, double max);
	bool editValue(CString previousName, CString editName, double min, double max);
	bool deleteValue(CString name);
	bool loadValues(CString filename);

	//example mutator methods
	bool loadExamples(CString filename);
	bool appendExamples(CString filename);
	bool resetExamples();
	bool setStartingPosition(int pos);
	bool shuffleExamples();
	bool saveShuffledExamples(CString filename);

	bool loadNetExamples(CString file);
	bool runNetExamples(void);
	bool trainNetwork(void);
	bool trainIANNNetwork(void);

	//****************************************
	//********* ADDED 2 27 2011 **************
	//****************************************
	bool setTestRuns(int tests);
	bool setSeed(int seed);
	bool runConsecutiveTests();
	bool runConsecutiveIANNTests();
};
