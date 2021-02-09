
// Neural NetDoc.cpp : implementation of the CNeuralNetDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Neural Net.h"
#endif

#include "Neural NetDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CNeuralNetDoc

IMPLEMENT_DYNCREATE(CNeuralNetDoc, CDocument)

BEGIN_MESSAGE_MAP(CNeuralNetDoc, CDocument)
END_MESSAGE_MAP()


// CNeuralNetDoc construction/destruction

CNeuralNetDoc::CNeuralNetDoc()
{
	theNet = NULL;

}

CNeuralNetDoc::~CNeuralNetDoc()
{
	if (theNet != NULL)
	{
		delete theNet;
		theNet = NULL;
	}
}

BOOL CNeuralNetDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CNeuralNetDoc serialization

void CNeuralNetDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		if (theNet != NULL)
			theNet->Serialize(ar);
	}
	else
	{
		if (theNet != NULL)
		{
			delete theNet;
			theNet = NULL;
		}
		theNet = new ANN();
		theNet->Serialize(ar);

		//update all views?
		UpdateAllViews(NULL, 1, NULL);
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CNeuralNetDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CNeuralNetDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CNeuralNetDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CNeuralNetDoc diagnostics

#ifdef _DEBUG
void CNeuralNetDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNeuralNetDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CNeuralNetDoc commands


//***************************************************************
//**********************  Network Methods  **********************
//***************************************************************
//network accessor methods
CString CNeuralNetDoc::getNetName()
{
	std::string sname;
	sname = theNet->getNetworkName();
	CString temp(sname.c_str());
	return temp;
}

int CNeuralNetDoc::getNetNodesLayer(int layerNumber)
{
	return theNet->getNodesAtLayer(layerNumber);
}

double CNeuralNetDoc::getNetLearningRate()
{
	return theNet->getLearningRate();
}

double CNeuralNetDoc::getNetMomentum()
{
	return theNet->getMomentum();
}

int CNeuralNetDoc::getNumberOfLayers()
{
	return theNet->getNumberOfLayers();
}
int CNeuralNetDoc::getNetInput()
{
	if (theNet != NULL)
		return theNet->getInputNodes();
	return 0;
}
int CNeuralNetDoc::getNetOutput()
{
	if (theNet != NULL)
		return theNet->getOutputNodes();
	return 0;
}
int CNeuralNetDoc::getNetHidden1()
{
	if (theNet != NULL)
		return theNet->getHidden1();
	return 0;
}
int CNeuralNetDoc::getNetHidden2()
{
	if (theNet != NULL)
		return theNet->getHidden2();
	return 0;
}
int CNeuralNetDoc::getNetHidden3()
{
	if (theNet != NULL)
		return theNet->getHidden3();
	return 0;
}
int CNeuralNetDoc::getNetHidden4()
{
	if (theNet != NULL)
		return theNet->getHidden4();
	return 0;
}
//network mutator methods
bool CNeuralNetDoc::createNetwork(CString name, int input, int output, double learning, double momentum,
		int hidden1, int hidden2, int hidden3, int hidden4)
{
	CT2CA s(name);
	std::string nName(s);

	bool hid1 = (hidden1 > 0);
	bool hid2 = (hidden2 > 0);
	bool hid3 = (hidden3 > 0);
	bool hid4 = (hidden4 > 0);

	std::vector<int> nodes = std::vector<int>();

	//put the nodes into the nodes vector
	if (input > 0)
		nodes.push_back(input);
	else
	{
		CErrorDlg dlg;
		CString msg = _T("Must have at least one input node.");
		dlg.error = msg;
		if (dlg.DoModal() == IDOK) {}

		return false;
	}

	if (hid1 && hid2 && hid3 && hid4)
	{
		nodes.push_back(hidden1);
		nodes.push_back(hidden2);
		nodes.push_back(hidden3);
		nodes.push_back(hidden4);
	}
	else if (hid1 && hid2 && hid3)
	{
		nodes.push_back(hidden1);
		nodes.push_back(hidden2);
		nodes.push_back(hidden3);
	}
	else if (hid1 && hid2)
	{
		nodes.push_back(hidden1);
		nodes.push_back(hidden2);
	}
	else if (hid1)
		nodes.push_back(hidden1);

	if (output > 0)
		nodes.push_back(output);
	else
	{
		CErrorDlg dlg;
		CString msg = _T("Must have at least one Output node.");
		dlg.error = msg;
		if (dlg.DoModal() == IDOK) {}

		return false;
	}

	//If we have gotten this far then the forms for the network have been met
	//See if there is already a network created if there is delete it
	if (theNet != NULL)
	{
		delete theNet;
		theNet = NULL;
	}

	theNet = new ANN(nodes, learning, momentum);
	theNet->setNetworkName(nName);

	return true;
}

bool CNeuralNetDoc::editNetwork(CString name, int input, int output, double learning, double momentum,
	int hidden1, int hidden2, int hidden3, int hidden4)
{
	if (theNet != NULL)
	{
		CT2CA s(name);
		std::string nName(s);

		bool hid1 = (hidden1 > 0);
		bool hid2 = (hidden2 > 0);
		bool hid3 = (hidden3 > 0);
		bool hid4 = (hidden4 > 0);

		std::vector<int> nodes = std::vector<int>();

		//put the nodes into the nodes vector
		if (input > 0)
			nodes.push_back(input);
		else
		{
			CErrorDlg dlg;
			CString msg = _T("Must have at least one input node.");
			dlg.error = msg;
			if (dlg.DoModal() == IDOK) {}

			return false;
		}

		if (hid1 && hid2 && hid3 && hid4)
		{
			nodes.push_back(hidden1);
			nodes.push_back(hidden2);
			nodes.push_back(hidden3);
			nodes.push_back(hidden4);
		}
		else if (hid1 && hid2 && hid3)
		{
			nodes.push_back(hidden1);
			nodes.push_back(hidden2);
			nodes.push_back(hidden3);
		}
		else if (hid1 && hid2)
		{
			nodes.push_back(hidden1);
			nodes.push_back(hidden2);
		}
		else if (hid1)
			nodes.push_back(hidden1);

		if (output > 0)
			nodes.push_back(output);
		else
		{
			CErrorDlg dlg;
			CString msg = _T("Must have at least one Output node.");
			dlg.error = msg;
			if (dlg.DoModal() == IDOK) {}

			return false;
		}
		if (momentum < 0)
		{
			CErrorDlg dlg;
			dlg.error = _T("Momentum must be greater than or equal to 0");
			if (dlg.DoModal() == IDOK) {}

			return false;
		}
		if (learning < 0)
		{
			CErrorDlg dlg;
			dlg.error = _T("Learning Rate must be greater than 0");
			if (dlg.DoModal() == IDOK) {}

			return false;
		}
		theNet->setNetworkName(nName);
		theNet->setLearningRate(learning);
		theNet->setMomentum(momentum);
		theNet->setNodesPerLayer(nodes);
		theNet->setNetworkName(nName);
		return true;
	}
	return false;
}
bool CNeuralNetDoc::setNetworkName(CString name)
{
	if (theNet != NULL)
	{
		CT2CA s(name);
		std::string sname(s);
		theNet->setNetworkName(sname);
		return true;
	}
	return false;
}
	
bool CNeuralNetDoc::setNetworkInput(int input)
{
	//need to think about how to adjust the nodes in the net on the fly
	/*if (theNet != NULL)
	{
		theNet->
		return true;
	}*/
	return false;
}

bool CNeuralNetDoc::setNetworkOutput(int output)
{
	//TODO same as setNetworkInput
	return false;
}

bool CNeuralNetDoc::setNetworkLearning(double learning)
{
	if (theNet != NULL)
	{
		theNet->setLearningRate(learning);
		return true;
	}
	return false;
}

bool CNeuralNetDoc::setNetworkMomentum(double momentum)
{
	if (theNet != NULL)
	{
		theNet->setMomentum(momentum);
		return true;
	}
	return false;
}

bool CNeuralNetDoc::setHiddenLayerNodes(int layer, int nodes)
{
	//TODO same as setNetworkInput
	return false;
}

void CNeuralNetDoc::resetNetwork()
{
	if (theNet != NULL)
	{
		delete theNet;
		theNet = NULL;
	}
}

//***************************************************************
//***********************  K-Fold Methods  **********************
//***************************************************************

//accessor methods
int CNeuralNetDoc::getFoldFolds()
{
	if (theNet != NULL)
	{
		return theNet->getFolds();
	}
	return 0;
}

int CNeuralNetDoc::getFoldEpochs()
{
	if (theNet != NULL)
	{
		return theNet->getEpochs();
	}
	return 0;
}

int CNeuralNetDoc::getFoldRuns()
{
	if (theNet != NULL)
	{
		return theNet->getConsecutiveRuns();
	}
	return 0;
}

double CNeuralNetDoc::getFoldCriteria()
{
	if (theNet != NULL)
	{
		return theNet->getStoppingCriteria();
	}
	return 0.0;
}

int CNeuralNetDoc::getFoldStartingLayer()
{
	if (theNet != NULL)
	{
		return theNet->getFoldStartingLayer();
	}
	return 0;
}

int CNeuralNetDoc::getFoldEndingLayer()
{
	if (theNet != NULL)
	{
		return theNet->getFoldEndingLayer();
	}
	return 0;
}

int CNeuralNetDoc::getStartingNodeLayer(int layer)
{
	if (theNet != NULL)
	{
		return theNet->getFoldStartingNodeAtLayer(layer);
	}
	return 0;
}

int CNeuralNetDoc::getEndingNodeLayer(int layer)
{
	if (theNet != NULL)
	{
		return theNet->getFoldEndingNodeAtLayer(layer);
	}
	return 0;
}

bool CNeuralNetDoc::runKFoldModel()
{
	if (theNet != NULL)
	{
		theNet->runAllKFold();
		return true;
	}
	return false;
}

//mutator methods

bool CNeuralNetDoc::setKFoldParameters(int fold, int epochs, double criteria, int runs, int startingLayer, int endingLayer,
										int starting1, int starting2, int starting3, int starting4,
										int ending1, int ending2, int ending3, int ending4)
{
	if (theNet != NULL)
	{
		std::vector<int> start = std::vector<int>();
		std::vector<int> end = std::vector<int>();
		start.push_back(starting1);
		start.push_back(starting2);
		start.push_back(starting3);
		start.push_back(starting4);
		end.push_back(ending1);
		end.push_back(ending2);
		end.push_back(ending3);
		end.push_back(ending4);

		theNet->setKFoldParameters(fold, epochs, criteria, runs, startingLayer, endingLayer, start, end);
		return true;
	}
	return false;
}

bool CNeuralNetDoc::setKFoldFolds(int folds)
{
	if (theNet != NULL)
	{
		theNet->setFolds(folds);
		return true;
	}
	return false;
}

bool CNeuralNetDoc::setKFoldEpochs(int epochs)
{
	if (theNet != NULL)
	{
		theNet->setEpochs(epochs);
		return true;
	}
	return false;
}

bool CNeuralNetDoc::setKFoldCriteria(double criteria)
{
	if (theNet != NULL)
	{
		theNet->setStoppingCriteria(criteria);
		return true;
	}
	return false;
}

bool CNeuralNetDoc::setKFoldRuns(int runs)
{
	if (theNet != NULL)
	{
		theNet->setConsecutiveRuns(runs);
		return true;
	}
	return false;
}

bool CNeuralNetDoc::setKFoldStartingLayer(int layer)
{
	/*if (theNet != NULL)
	{
		theNet
		return true;
	}*/
	return false;
}

bool CNeuralNetDoc::setKFoldEndingLayer(int layer)
{
	/*if (theNet != NULL)
	{
		theNet
		return true;
	}*/
	return false;
}

bool CNeuralNetDoc::setKFoldStartingNodeLayer(int layer, int nodes)
{
	if (theNet != NULL)
	{
		theNet->setKFoldStartingNodeAtLayer(layer, nodes);
		return true;
	}
	return false;
}

bool CNeuralNetDoc::setKFoldEndingNodeLayer(int layer, int nodes)
{
	if (theNet != NULL)
	{
		theNet->setKFoldEndingNodeAtLayer(layer, nodes);
		return true;
	}
	return false;
}

//***************************************************************
//********************  Attribute Methods  **********************
//***************************************************************

//accessor methods
double CNeuralNetDoc::getAttributeMin(CString name)
{
	if (theNet != NULL)
	{
		CT2CA s(name);
		std::string sName(s);
		return theNet->getAttributeMin(sName);
	}
	return 0.0;
}

double CNeuralNetDoc::getAttributeMax(CString name)
{
	if (theNet != NULL)
	{
		CT2CA s(name);
		std::string sName(s);
		return theNet->getAttributeMax(sName);
	}
	return 0.0;
}

double CNeuralNetDoc::getAttributeFri(CString name)
{
	if (theNet != NULL)
	{
		CT2CA s(name);
		std::string sName(s);
		return theNet->getAttributeFri(sName);
	}
	return 0.0;
}

CString CNeuralNetDoc::getAttributeName(int index)
{
	if (theNet != NULL)
	{
		std::string name;
		name = theNet->getAttributeName(index);
		CString temp(name.c_str());
		return temp;
	}
	return _T("There is no Network!");
}

double CNeuralNetDoc::getAttributeMin(int index)
{
	if (theNet != NULL)
	{
		return theNet->getAttributeMin(index);
	}
	return 0.0;
}

double CNeuralNetDoc::getAttributeMax(int index)
{
	if (theNet != NULL)
	{
		return theNet->getAttributeMax(index);
	}
	return 0.0;
}

double CNeuralNetDoc::getAttributeFri(int index)
{
	if (theNet != NULL)
	{
		return theNet->getAttributeFri(index);
	}
	return 0.0;
}

int CNeuralNetDoc::getAttributeNumber()
{
	if (theNet != NULL)
		return theNet->getNumberOfAttributes();
	return 0;
}

bool CNeuralNetDoc::addAttribute(CString name, double min, double max, double fri)
{
	if (theNet != NULL)
	{
		CT2CA s(name);
		std::string sName(s);
		return theNet->addAttribute(sName, min, max, fri);
	}
	return false;
}

bool CNeuralNetDoc::editAttribute(CString previousName, CString editName, double min, double max, double fri)
{
	if (theNet != NULL)
	{
		CT2CA p(previousName);
		std::string pName(p);
		CT2CA e(editName);
		std::string eName(e);

		return theNet->editAttribute(pName, eName, min, max, fri);
	}	
	return false;
}

bool CNeuralNetDoc::deleteAttribute(CString name)
{
	if (theNet != NULL)
	{
		CT2CA s(name);
		std::string sName(s);
		return theNet->removeAttribute(sName);
	}
	return false;
}

bool CNeuralNetDoc::loadAttributes(CString filename)
{
	if (theNet != NULL)
	{
		CT2CA s(filename);
		std::string sName(s);
		return theNet->loadAttributeFile(sName);
	}
	return false;
}

//***************************************************************
//********************  Value Methods  **************************
//***************************************************************

//accessor methods
double CNeuralNetDoc::getValueMin(CString name)
{
	if (theNet != NULL)
	{
		CT2CA s(name);
		std::string sName(s);
		return theNet->getValueMin(sName);
	}
	return 0.0;
}

double CNeuralNetDoc::getValueMax(CString name)
{
	if (theNet != NULL)
	{
		CT2CA s(name);
		std::string sName(s);
		return theNet->getValueMax(sName);
	}
	return 0.0;
}

CString CNeuralNetDoc::getValueName(int index)
{
	if (theNet != NULL)
	{
		std::string name;
		name = theNet->getValueName(index);
		CString temp(name.c_str());
		return temp;
	}
	return _T("There is no network!");
}

double CNeuralNetDoc::getValueMin(int index)
{
	if (theNet != NULL)
	{
		return theNet->getValueMin(index);
	}
	return 0.0;
}

double CNeuralNetDoc::getValueMax(int index)
{
	if (theNet != NULL)
	{
		return theNet->getValueMax(index);
	}
	return 0.0;
}

int CNeuralNetDoc::getValueNumber()
{
	if (theNet != NULL)
		return theNet->getNumberOfValues();
	return 0;
}
//mutator methods
bool CNeuralNetDoc::addValue(CString name, double min, double max)
{
	if (theNet != NULL)
	{
		CT2CA s(name);
		std::string sName(s);
		return theNet->addValue(sName, min, max);
	}
	return false;
}

bool CNeuralNetDoc::editValue(CString previousName, CString editName, double min, double max)
{
	if (theNet != NULL)
	{
		CT2CA p(previousName);
		std::string pName(p);
		CT2CA e(editName);
		std::string eName(e);

		return theNet->editValue(pName, eName, min, max);
	}
	return false;
}

bool CNeuralNetDoc::deleteValue(CString name)
{
	if (theNet != NULL)
	{
		CT2CA s(name);
		std::string sName(s);
		return theNet->removeValue(sName);
	}
	return false;
}

bool CNeuralNetDoc::loadValues(CString filename)
{
	if (theNet != NULL)
	{
		CT2CA s(filename);
		std::string sName(s);
		return theNet->loadValueFile(sName);
	}
	return false;
}

//***************************************************************
//********************  Example Methods  ************************
//***************************************************************

//mutator methods
bool CNeuralNetDoc::loadExamples(CString filename)
{
	if (theNet != NULL)
	{
		CT2CA f(filename);
		std::string fName(f);

		return theNet->loadExampleFile(fName);
	}
	return false;
}

bool CNeuralNetDoc::appendExamples(CString filename)
{
	if (theNet != NULL)
	{
		CT2CA f(filename);
		std::string fName(f);

		return theNet->appendExampleFile(fName);
	}
	return false;
}

bool CNeuralNetDoc::resetExamples()
{
	if (theNet != NULL)
	{
		return theNet->resetExamples();
	}
	return false;
}

bool CNeuralNetDoc::setStartingPosition(int pos)
{
	if (theNet != NULL)
		return theNet->setStartingPosition(pos);
	return false;
}

bool CNeuralNetDoc::shuffleExamples()
{
	if (theNet != NULL)
	{
		theNet->shuffleExamples();
		return true;
	}
	return false;
}

bool CNeuralNetDoc::saveShuffledExamples(CString filename)
{
	if (theNet != NULL)
	{
		CT2CA s(filename);
		std::string name(s);
		return theNet->saveExamples(name);
	}
	return false;
}

//accessor methods
bool CNeuralNetDoc::getHaveExamples()
{
	if (theNet != NULL)
	{
		return theNet->haveExamples();
	}
	return false;
}

int CNeuralNetDoc::getExampleCount()
{
	if (theNet != NULL)
		return theNet->getExampleCount();
	return 5;
}

int CNeuralNetDoc::getStartingPosition()
{
	if (theNet != NULL)
		return theNet->getStartingPosition();
	return 0;
}

//bool CNeuralNetDoc::runKFoldModel()
//{
//	if (theNet != NULL)
//	{
//		theNet->runAllKFold();
//		return true;
//	}
//	return false;
//}


bool CNeuralNetDoc::loadNetExamples(CString file)
{
	if (theNet != NULL)
	{
		CT2CA s(file);
		std::string name(s);
		return theNet->loadOutputExamples(name);
	}
	return false;
}


bool CNeuralNetDoc::runNetExamples(void)
{
	if (theNet != NULL)
	{
		theNet->runExamples();
		return true;
	}
	return false;
}


bool CNeuralNetDoc::trainNetwork(void)
{
	if (theNet != NULL)
	{
		theNet->trainNetwork();
		return true;
	}
	return false;
}


bool CNeuralNetDoc::trainIANNNetwork(void)
{
	if (theNet != NULL)
	{
		theNet->trainIANNNetwork();
		return true;
	}
	return false;
}

//***************************************
//********* ADDED 2 27 2011 *************
//***************************************
bool CNeuralNetDoc::setTestRuns(int tests)
{
	if (theNet != NULL)
	{
		theNet->setConsecutiveTests(tests);
		return true;
	}
	return false;
}

bool CNeuralNetDoc::setSeed(int seed)
{
	if (theNet != NULL)
	{
		theNet->setUserSeed(seed);
		return true;
	}
	return false;
}

bool CNeuralNetDoc::runConsecutiveTests()
{
	if (theNet != NULL)
	{
		theNet->runConsecutiveTests();
		return true;
	}
	return false;
}

bool CNeuralNetDoc::runConsecutiveIANNTests()
{
	if (theNet != NULL)
	{
		theNet->runConsecutiveIANNTests();
		return true;
	}
	return false;
}