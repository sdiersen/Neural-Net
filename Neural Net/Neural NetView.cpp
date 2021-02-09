
// Neural NetView.cpp : implementation of the CNeuralNetView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Neural Net.h"
#endif

#include "Neural NetDoc.h"
#include "Neural NetView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNeuralNetView

IMPLEMENT_DYNCREATE(CNeuralNetView, CFormView)

BEGIN_MESSAGE_MAP(CNeuralNetView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_NNF_NETWORKADD, &CNeuralNetView::OnBnClickedNnfNetworkadd)
	ON_BN_CLICKED(IDC_NNF_NETWORKEDIT, &CNeuralNetView::OnBnClickedNnfNetworkedit)
	ON_BN_CLICKED(IDC_NNF_NETWORKRESET, &CNeuralNetView::OnBnClickedNnfNetworkreset)
	ON_BN_CLICKED(IDC_NNF_ATTRIBUTEADD, &CNeuralNetView::OnBnClickedNnfAttributeadd)
	ON_BN_CLICKED(IDC_NNF_ATTRIBUTEEDIT, &CNeuralNetView::OnBnClickedNnfAttributeedit)
	ON_BN_CLICKED(IDC_ATTRIBUTEDELETE, &CNeuralNetView::OnBnClickedAttributedelete)
	ON_CBN_SELCHANGE(IDC_NNF_ATTRIBUTEBOX, &CNeuralNetView::OnCbnSelchangeNnfAttributebox)
	ON_BN_CLICKED(IDC_NNF_VALUEADD, &CNeuralNetView::OnBnClickedNnfValueadd)
	ON_BN_CLICKED(IDC_NNF_VALUEEDIT, &CNeuralNetView::OnBnClickedNnfValueedit)
	ON_BN_CLICKED(IDC_NNF_VALUEDELETE, &CNeuralNetView::OnBnClickedNnfValuedelete)
	ON_CBN_SELCHANGE(IDC_NNF_VALUEBOX, &CNeuralNetView::OnCbnSelchangeNnfValuebox)
	ON_EN_CHANGE(IDC_NNF_EXAMPLENAME, &CNeuralNetView::OnEnChangeNnfExamplename)
	ON_BN_CLICKED(IDC_NNF_EXAMPLELOAD, &CNeuralNetView::OnBnClickedNnfExampleload)
	ON_BN_CLICKED(IDC_NNF_EXAMPLEAPPEND, &CNeuralNetView::OnBnClickedNnfExampleappend)
	ON_BN_CLICKED(IDC_NNF_EXAMPLERESET, &CNeuralNetView::OnBnClickedNnfExamplereset)
	ON_BN_CLICKED(IDC_NNF_FOLDSETUP, &CNeuralNetView::OnBnClickedNnfFoldsetup)
	ON_BN_CLICKED(IDC_NNF_FOLDMODIFY, &CNeuralNetView::OnBnClickedNnfFoldmodify)
	ON_BN_CLICKED(IDC_NNF_FOLDRESET, &CNeuralNetView::OnBnClickedNnfFoldreset)
	ON_BN_CLICKED(IDC_NNF_ATTRIBUTELOAD, &CNeuralNetView::OnBnClickedNnfAttributeload)
	ON_BN_CLICKED(IDC_NNF_VALUELOAD, &CNeuralNetView::OnBnClickedNnfValueload)
	ON_EN_CHANGE(IDC_NNF_ATTRIBUTEFILENAME, &CNeuralNetView::OnEnChangeNnfAttributefilename)
	ON_EN_CHANGE(IDC_NNF_VALUEFILENAME, &CNeuralNetView::OnEnChangeNnfValuefilename)
	ON_BN_CLICKED(IDC_NNF_EXAMPLEPOSITIONCHANGE, &CNeuralNetView::OnBnClickedNnfExamplepositionchange)
	ON_EN_CHANGE(IDC_NNF_EXAMPLESTARTPOSITION, &CNeuralNetView::OnEnChangeNnfExamplestartposition)
	ON_BN_CLICKED(IDC_NNF_EXAMPLESHUFFLE, &CNeuralNetView::OnBnClickedNnfExampleshuffle)
	ON_BN_CLICKED(IDC_NNF_EXAMPLESAVESHUFFLED, &CNeuralNetView::OnBnClickedNnfExamplesaveshuffled)
	ON_EN_CHANGE(IDC_NNF_EXAMPLESHUFFLENAME, &CNeuralNetView::OnEnChangeNnfExampleshufflename)
	ON_BN_CLICKED(IDC_NNF_FOLDRUNALL, &CNeuralNetView::OnBnClickedNnfFoldrunall)
	ON_EN_CHANGE(IDC_NNF_NETFILENAME, &CNeuralNetView::OnEnChangeNnfNetfilename)
	ON_BN_CLICKED(IDC_NNF_NETEXAMPLELOAD, &CNeuralNetView::OnBnClickedNnfNetexampleload)
	ON_BN_CLICKED(IDC_NNF_NETRUN, &CNeuralNetView::OnBnClickedNnfNetrun)
	ON_BN_CLICKED(IDC_NNF_NETTRAIN, &CNeuralNetView::OnBnClickedNnfNettrain)
	ON_BN_CLICKED(IDC_NNF_NETIANNTRAIN, &CNeuralNetView::OnBnClickedNnfNetianntrain)
	ON_BN_CLICKED(IDC_NNF_NETIANNTEST, &CNeuralNetView::OnBnClickedNnfNetianntest)
	ON_EN_CHANGE(IDC_NNF_VALUEMIN, &CNeuralNetView::OnEnChangeNnfValuemin)
	ON_EN_CHANGE(IDC_NN_TESTRUNS, &CNeuralNetView::OnEnChangeNnTestruns)
	ON_EN_CHANGE(IDC_NN_SEED, &CNeuralNetView::OnEnChangeNnSeed)
	ON_BN_CLICKED(IDC_NNF_TESTRUNSLOAD, &CNeuralNetView::OnBnClickedNnfTestrunsload)
	ON_BN_CLICKED(IDC_NNF_SEEDLOAD, &CNeuralNetView::OnBnClickedNnfSeedload)
	ON_BN_CLICKED(IDC_RUNCONCECUTIVETESTS, &CNeuralNetView::OnBnClickedRunconcecutivetests)
	ON_BN_CLICKED(IDC_RUNCONCECUTIVETESTS2, &CNeuralNetView::OnBnClickedRunconcecutivetests2)
END_MESSAGE_MAP()

// CNeuralNetView construction/destruction

CNeuralNetView::CNeuralNetView()
	: CFormView(CNeuralNetView::IDD)
	, netName(_T(""))
	, netInput(0)
	, netHidden1(0)
	, netHidden2(0)
	, netHidden3(0)
	, netHidden4(0)
	, netOutput(0)
	, netLearning(0)
	, netMomentum(0)
	, attributeName(_T(""))
	, attributeMin(0)
	, attributeMax(0)
	, attributeFri(0)
	, valueName(_T(""))
	, valueMin(0)
	, valueMax(0)
	, exampleName(_T(""))
	, foldFolds(0)
	, foldEpochs(0)
	, foldCriteria(0)
	, foldRuns(0)
	, foldStartingLayer(0)
	, foldEndingLayer(0)
	, foldStarting1(0)
	, foldStarting2(0)
	, foldStarting3(0)
	, foldStarting4(0)
	, foldEnding1(0)
	, foldEnding2(0)
	, foldEnding3(0)
	, foldEnding4(0)
	, attributeSelection(0)
	, valueSelection(0)
	, attributeFileName(_T(""))
	, valueFileName(_T(""))
	, exampleCount(0)
	, examplePosition(0)
	, exampleShuffleName(_T(""))
	, netExampleName(_T(""))
	, testRuns(0)
	, seed(0)
{
	// TODO: add construction code here

}

CNeuralNetView::~CNeuralNetView()
{
}

void CNeuralNetView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NNF_NETWORKADD, netAddControl);
	DDX_Control(pDX, IDC_NNF_NETWORKEDIT, netEditControl);
	DDX_Control(pDX, IDC_NNF_NETWORKSAVE, netSaveControl);
	DDX_Control(pDX, IDC_NNF_NETWORKRESET, netResetControl);
	DDX_Control(pDX, IDC_NNF_ATTRIBUTEADD, attributeAddControl);
	DDX_Control(pDX, IDC_NNF_ATTRIBUTEEDIT, attributeEditControl);
	DDX_Control(pDX, IDC_ATTRIBUTESAVE, attributeSaveControl);
	DDX_Control(pDX, IDC_ATTRIBUTEDELETE, attributeDeleteControl);
	DDX_Control(pDX, IDC_NNF_VALUEADD, valueAddControl);
	DDX_Control(pDX, IDC_NNF_VALUEEDIT, valueEditControl);
	DDX_Control(pDX, IDC_NNF_VALUESAVE, valueSaveControl);
	DDX_Control(pDX, IDC_NNF_VALUEDELETE, valueDeleteControl);
	DDX_Control(pDX, IDC_NNF_EXAMPLELOAD, exampleLoadControl);
	DDX_Control(pDX, IDC_NNF_EXAMPLEAPPEND, exampleAppendControl);
	DDX_Control(pDX, IDC_NNF_EXAMPLERESET, exampleResetControl);
	DDX_Control(pDX, IDC_NNF_FOLDSETUP, foldSetupControl);
	DDX_Control(pDX, IDC_NNF_FOLDMODIFY, foldModifyControl);
	DDX_Control(pDX, IDC_NNF_FOLDRESET, foldResetControl);
	DDX_Control(pDX, IDC_NNF_NAME, netNameControl);
	DDX_Control(pDX, IDC_NNF_INPUTNODES, netInputControl);
	DDX_Control(pDX, IDC_NNF_HIDDEN1, netHidden1Control);
	DDX_Control(pDX, IDC_NNF_HIDDEN2, netHidden2Control);
	DDX_Control(pDX, IDC_NNF_HIDDEN3, netHidden3Control);
	DDX_Control(pDX, IDC_NNF_HIDDEN4, netHidden4Control);
	DDX_Control(pDX, IDC_NNF_OUTPUTNODES, netOutputControl);
	DDX_Control(pDX, IDC_NNF_LEARNINGRATE, netLearningControl);
	DDX_Control(pDX, IDC_NNF_MOMENTUM, netMomentumControl);
	DDX_Control(pDX, IDC_NNF_ATTRIBUTEBOX, attributeBoxControl);
	DDX_Control(pDX, IDC_NNF_ATTRIBUTENAME, attributeNameControl);
	DDX_Control(pDX, IDC_NNF_ATTRIBUTEMIN, attributeMinControl);
	DDX_Control(pDX, IDC_NNF_ATTRIBUTEMAX, attributeMaxControl);
	DDX_Control(pDX, IDC_NNF_ATTRIBUTEFRI, attributeFriControl);
	DDX_Control(pDX, IDC_NNF_VALUEBOX, valueBoxControl);
	DDX_Control(pDX, IDC_NNF_VALUENAME, valueNameControl);
	DDX_Control(pDX, IDC_NNF_VALUEMIN, valueMinControl);
	DDX_Control(pDX, IDC_NNF_VALUEMAX, valueMaxControl);
	DDX_Control(pDX, IDC_NNF_EXAMPLENAME, exampleNameControl);
	DDX_Control(pDX, IDC_NNF_FOLDFOLDS, foldFoldsControl);
	DDX_Control(pDX, IDC_NNF_FOLDEPOCHS, foldEpochsControl);
	DDX_Control(pDX, IDC_NNF_FOLDCRITERIA, foldCriteriaControl);
	DDX_Control(pDX, IDC_NNF_FOLDRUNS, foldRunsControl);
	DDX_Control(pDX, IDC_NNF_FOLDSTARTINGLAYERS, foldStartingLayerControl);
	DDX_Control(pDX, IDC_NNF_ENDINGLAYERS, foldEndingLayerControl);
	DDX_Control(pDX, IDC_NNF_FOLDSTARTING1, foldStarting1Control);
	DDX_Control(pDX, IDC_NNF_FOLDSTARTING2, foldStarting2Control);
	DDX_Control(pDX, IDC_NNF_FOLDSTARTING3, foldStarting3Control);
	DDX_Control(pDX, IDC_NNF_FOLDSTARTING4, foldStarting4Control);
	DDX_Control(pDX, IDC_NNF_ENDINGHIDDING1, foldEnding1Control);
	DDX_Control(pDX, IDC_NNF_ENDINGHIDDING2, foldEnding2Control);
	DDX_Control(pDX, IDC_NNF_ENDINGHIDDING3, foldEnding3Control);
	DDX_Control(pDX, IDC_NNF_ENDINGHIDDING4, foldEnding4Control);
	DDX_Text(pDX, IDC_NNF_NAME, netName);
	DDX_Text(pDX, IDC_NNF_INPUTNODES, netInput);
	DDX_Text(pDX, IDC_NNF_HIDDEN1, netHidden1);
	DDX_Text(pDX, IDC_NNF_HIDDEN2, netHidden2);
	DDX_Text(pDX, IDC_NNF_HIDDEN3, netHidden3);
	DDX_Text(pDX, IDC_NNF_HIDDEN4, netHidden4);
	DDX_Text(pDX, IDC_NNF_OUTPUTNODES, netOutput);
	DDX_Text(pDX, IDC_NNF_LEARNINGRATE, netLearning);
	DDX_Text(pDX, IDC_NNF_MOMENTUM, netMomentum);
	DDX_Text(pDX, IDC_NNF_ATTRIBUTENAME, attributeName);
	DDX_Text(pDX, IDC_NNF_ATTRIBUTEMIN, attributeMin);
	DDX_Text(pDX, IDC_NNF_ATTRIBUTEMAX, attributeMax);
	DDX_Text(pDX, IDC_NNF_ATTRIBUTEFRI, attributeFri);
	DDX_Text(pDX, IDC_NNF_VALUENAME, valueName);
	DDX_Text(pDX, IDC_NNF_VALUEMIN, valueMin);
	DDX_Text(pDX, IDC_NNF_VALUEMAX, valueMax);
	DDX_Text(pDX, IDC_NNF_EXAMPLENAME, exampleName);
	DDX_Text(pDX, IDC_NNF_FOLDFOLDS, foldFolds);
	DDX_Text(pDX, IDC_NNF_FOLDEPOCHS, foldEpochs);
	DDX_Text(pDX, IDC_NNF_FOLDCRITERIA, foldCriteria);
	DDX_Text(pDX, IDC_NNF_FOLDRUNS, foldRuns);
	DDX_Text(pDX, IDC_NNF_FOLDSTARTINGLAYERS, foldStartingLayer);
	DDX_Text(pDX, IDC_NNF_ENDINGLAYERS, foldEndingLayer);
	DDX_Text(pDX, IDC_NNF_FOLDSTARTING1, foldStarting1);
	DDX_Text(pDX, IDC_NNF_FOLDSTARTING2, foldStarting2);
	DDX_Text(pDX, IDC_NNF_FOLDSTARTING3, foldStarting3);
	DDX_Text(pDX, IDC_NNF_FOLDSTARTING4, foldStarting4);
	DDX_Text(pDX, IDC_NNF_ENDINGHIDDING1, foldEnding1);
	DDX_Text(pDX, IDC_NNF_ENDINGHIDDING2, foldEnding2);
	DDX_Text(pDX, IDC_NNF_ENDINGHIDDING3, foldEnding3);
	DDX_Text(pDX, IDC_NNF_ENDINGHIDDING4, foldEnding4);
	DDX_CBIndex(pDX, IDC_NNF_ATTRIBUTEBOX, attributeSelection);
	DDX_CBIndex(pDX, IDC_NNF_VALUEBOX, valueSelection);
	DDX_Control(pDX, IDC_NNF_ATTRIBUTEFILENAME, attributeFileNameControl);
	DDX_Control(pDX, IDC_NNF_VALUEFILENAME, valueFileNameControl);
	DDX_Text(pDX, IDC_NNF_ATTRIBUTEFILENAME, attributeFileName);
	DDX_Text(pDX, IDC_NNF_VALUEFILENAME, valueFileName);
	DDX_Control(pDX, IDC_NNF_EXAMPLECOUNT, exampleCountControl);
	DDX_Control(pDX, IDC_NNF_EXAMPLESTARTPOSITION, examplePositionControl);
	DDX_Text(pDX, IDC_NNF_EXAMPLECOUNT, exampleCount);
	DDX_Text(pDX, IDC_NNF_EXAMPLESTARTPOSITION, examplePosition);
	DDX_Control(pDX, IDC_NNF_EXAMPLEPOSITIONCHANGE, examplePositionChangeControl);
	DDX_Control(pDX, IDC_NNF_EXAMPLESHUFFLE, exampleShuffleControl);
	DDX_Control(pDX, IDC_NNF_EXAMPLESAVESHUFFLED, exampleShuffleSaveControl);
	DDX_Control(pDX, IDC_NNF_EXAMPLESHUFFLENAME, exampleShuffleNameControl);
	DDX_Text(pDX, IDC_NNF_EXAMPLESHUFFLENAME, exampleShuffleName);
	DDX_Control(pDX, IDC_NNF_FOLDRUNALL, foldRunControl);
	DDX_Control(pDX, IDC_NNF_NETRUN, netRunTestControl);
	DDX_Text(pDX, IDC_NNF_NETFILENAME, netExampleName);
	DDX_Control(pDX, IDC_NNF_NETTRAIN, netTrainControl);
	DDX_Control(pDX, IDC_NNF_NETIANNTRAIN, IANNTrainControl);
	DDX_Control(pDX, IDC_NNF_NETIANNTEST, IANNTestControl);
	DDX_Text(pDX, IDC_NN_TESTRUNS, testRuns);
	DDX_Text(pDX, IDC_NN_SEED, seed);
}

BOOL CNeuralNetView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CNeuralNetView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

void CNeuralNetView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if (lHint == 1)
	{
		CNeuralNetDoc* pDoc = GetDocument();
		
		//set up the network fields
		dspNetName(pDoc->getNetName());
		dspNetInput(pDoc->getNetInput());
		dspNetOutput(pDoc->getNetOutput());
		dspNetHidden1(pDoc->getNetHidden1());
		dspNetHidden2(pDoc->getNetHidden2());
		dspNetHidden3(pDoc->getNetHidden3());
		dspNetHidden4(pDoc->getNetHidden4());

		netAddControl.EnableWindow(FALSE);
		netEditControl.EnableWindow();
		netResetControl.EnableWindow();

		//set up the attributes
		int attSize = pDoc->getAttributeNumber();
		attributeBoxControl.ResetContent();
		for (int x = 0; x < attSize; ++x)
			attributeBoxControl.AddString(pDoc->getAttributeName(x));

		//set up the values
		int valSize = pDoc->getValueNumber();
		valueBoxControl.ResetContent();
		for (int x = 0; x < valSize; ++x)
			valueBoxControl.AddString(pDoc->getValueName(x));

		//set up the k-fold values
		dspFoldFolds(pDoc->getFoldFolds());
		dspFoldEpochs(pDoc->getFoldEpochs());
		dspFoldRuns(pDoc->getFoldRuns());
		dspFoldCriteria(pDoc->getFoldCriteria());
		dspFoldStartingLayer(pDoc->getFoldStartingLayer());
		dspFoldEndingLayer(pDoc->getFoldEndingLayer());
		dspFoldStarting1(pDoc->getStartingNodeLayer(0));
		dspFoldStarting2(pDoc->getStartingNodeLayer(1));
		dspFoldStarting3(pDoc->getStartingNodeLayer(2));
		dspFoldStarting4(pDoc->getStartingNodeLayer(3));
		dspFoldEnding1(pDoc->getEndingNodeLayer(0));
		dspFoldEnding2(pDoc->getEndingNodeLayer(1));
		dspFoldEnding3(pDoc->getEndingNodeLayer(2));
		dspFoldEnding4(pDoc->getEndingNodeLayer(3));

		if (foldFolds > 1)
		{
			foldSetupControl.EnableWindow(FALSE);
			foldModifyControl.EnableWindow();
			foldResetControl.EnableWindow();
		}
		else
		{
			foldSetupControl.EnableWindow();
			foldModifyControl.EnableWindow(FALSE);
			foldResetControl.EnableWindow(FALSE);
		}

		if (pDoc->getHaveExamples())
		{
			exampleLoadControl.EnableWindow(FALSE);
			exampleAppendControl.EnableWindow();
			exampleResetControl.EnableWindow();
			dspExampleCount(pDoc->getExampleCount());
			dspExamplePosition(pDoc->getStartingPosition());
			examplePositionChangeControl.EnableWindow();
			examplePositionControl.EnableWindow();
			exampleShuffleControl.EnableWindow();
			exampleShuffleSaveControl.EnableWindow();
			exampleShuffleNameControl.EnableWindow();
		}
		else
		{
			exampleLoadControl.EnableWindow();
			exampleAppendControl.EnableWindow(FALSE);
			exampleResetControl.EnableWindow(FALSE);
			examplePositionChangeControl.EnableWindow(FALSE);
			examplePositionControl.EnableWindow(FALSE);
			exampleShuffleControl.EnableWindow(FALSE);
			exampleShuffleSaveControl.EnableWindow(FALSE);
			exampleShuffleNameControl.EnableWindow(FALSE);			
		}
	}
	CView::OnUpdate(pSender, lHint, pHint);
}

void CNeuralNetView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CNeuralNetView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CNeuralNetView diagnostics

#ifdef _DEBUG
void CNeuralNetView::AssertValid() const
{
	CFormView::AssertValid();
}

void CNeuralNetView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CNeuralNetDoc* CNeuralNetView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNeuralNetDoc)));
	return (CNeuralNetDoc*)m_pDocument;
}
#endif //_DEBUG


// CNeuralNetView message handlers

//DISPLAY METHODS
void CNeuralNetView::dspNetName(CString name)
{
	netName = name;
	netNameControl.SetWindowText(name);
}
void CNeuralNetView::dspNetInput(int nodes)
{
	netInput = nodes;
	CString temp;
	temp.Format(_T("%d"), netInput);
	netInputControl.SetWindowText(temp);
}
void CNeuralNetView::dspNetHidden1(int nodes)
{
	netHidden1 = nodes;
	CString temp;
	temp.Format(_T("%d"), netHidden1);
	netHidden1Control.SetWindowText(temp);
}
void CNeuralNetView::dspNetHidden2(int nodes)
{
	netHidden2 = nodes;
	CString temp;
	temp.Format(_T("%d"), netHidden2);
	netHidden2Control.SetWindowText(temp);
}
void CNeuralNetView::dspNetHidden3(int nodes)
{
	netHidden3 = nodes;
	CString temp;
	temp.Format(_T("%d"), netHidden3);
	netHidden3Control.SetWindowText(temp);
}
void CNeuralNetView::dspNetHidden4(int nodes)
{
	netHidden4 = nodes;
	CString temp;
	temp.Format(_T("%d"), netHidden4);
	netHidden4Control.SetWindowText(temp);
}
void CNeuralNetView::dspNetOutput(int output)
{
	netOutput = output;
	CString temp;
	temp.Format(_T("%d"), netOutput);
	netOutputControl.SetWindowText(temp);
}
void CNeuralNetView::dspNetLearning(double learning)
{
	netLearning = learning;
	CString temp;
	temp.Format(_T("%.3f"), netLearning);
	netLearningControl.SetWindowText(temp);
}
void CNeuralNetView::dspNetMomentum(double momentum)
{
	netMomentum = momentum;
	CString temp;
	temp.Format(_T("%.3f"), netMomentum);
	netMomentumControl.SetWindowText(temp);
}
void CNeuralNetView::dspAttributeName(CString name)
{
	attributeName = name;
	attributeNameControl.SetWindowText(attributeName);
}
void CNeuralNetView::dspAttributeMin(double min)
{
	attributeMin = min;
	CString temp;
	temp.Format(_T("%.3f"), attributeMin);
	attributeMinControl.SetWindowText(temp);
}
void CNeuralNetView::dspAttributeMax(double max)
{
	attributeMax = max;
	CString temp;
	temp.Format(_T("%.3f"), attributeMax);
	attributeMaxControl.SetWindowText(temp);
}
void CNeuralNetView::dspAttributeFri(double fri)
{
	attributeFri = fri;
	CString temp;
	temp.Format(_T("%.3f"), attributeFri);
	attributeFriControl.SetWindowText(temp);
}
void CNeuralNetView::dspValueName(CString name)
{
	valueName = name;
	valueNameControl.SetWindowText(valueName);
}
void CNeuralNetView::dspValueMin(double min)
{
	valueMin = min;
	CString temp;
	temp.Format(_T("%.3f"), valueMin);
	valueMinControl.SetWindowText(temp);
}
void CNeuralNetView::dspValueMax(double max)
{
	valueMax = max;
	CString temp;
	temp.Format(_T("%.3f"), valueMax);
	valueMaxControl.SetWindowText(temp);
}
void CNeuralNetView::dspExampleName(CString name)
{
	exampleName = name;
	exampleNameControl.SetWindowText(exampleName);
}
void CNeuralNetView::dspFoldFolds(int folds)
{
	foldFolds = folds;
	CString temp;
	temp.Format(_T("%d"), foldFolds);
	foldFoldsControl.SetWindowText(temp);
}
void CNeuralNetView::dspFoldEpochs(int epochs)
{
	foldEpochs = epochs;
	CString temp;
	temp.Format(_T("%d"), foldEpochs);
	foldEpochsControl.SetWindowText(temp);
}
void CNeuralNetView::dspFoldCriteria(double criteria)
{
	foldCriteria = criteria;
	CString temp;
	temp.Format(_T("%.3f"), foldCriteria);
	foldCriteriaControl.SetWindowText(temp);
}
void CNeuralNetView::dspFoldRuns(int runs)
{
	foldRuns = runs;
	CString temp;
	temp.Format(_T("%d"), foldRuns);
	foldRunsControl.SetWindowText(temp);
}
void CNeuralNetView::dspFoldStartingLayer(int starting)
{
	foldStartingLayer = starting;
	CString temp;
	temp.Format(_T("%d"), foldStartingLayer);
	foldStartingLayerControl.SetWindowText(temp);
}
void CNeuralNetView::dspFoldEndingLayer(int ending)
{
	foldEndingLayer = ending;
	CString temp;
	temp.Format(_T("%d"), foldEndingLayer);
	foldEndingLayerControl.SetWindowText(temp);
}
void CNeuralNetView::dspFoldStarting1(int nodes)
{
	foldStarting1 = nodes;
	CString temp;
	temp.Format(_T("%d"), foldStarting1);
	foldStarting1Control.SetWindowText(temp);
}
void CNeuralNetView::dspFoldStarting2(int nodes)
{
	foldStarting2 = nodes;
	CString temp;
	temp.Format(_T("%d"), foldStarting2);
	foldStarting2Control.SetWindowText(temp);
}
void CNeuralNetView::dspFoldStarting3(int nodes)
{
	foldStarting3 = nodes;
	CString temp;
	temp.Format(_T("%d"), foldStarting3);
	foldStarting3Control.SetWindowText(temp);
}
void CNeuralNetView::dspFoldStarting4(int nodes)
{
	foldStarting4 = nodes;
	CString temp;
	temp.Format(_T("%d"), foldStarting4);
	foldStarting4Control.SetWindowText(temp);
}
void CNeuralNetView::dspFoldEnding1(int nodes)
{
	foldEnding1 = nodes;
	CString temp;
	temp.Format(_T("%d"), foldEnding1);
	foldEnding1Control.SetWindowText(temp);
}
void CNeuralNetView::dspFoldEnding2(int nodes)
{
	foldEnding2 = nodes;
	CString temp;
	temp.Format(_T("%d"), foldEnding2);
	foldEnding2Control.SetWindowText(temp);
}
void CNeuralNetView::dspFoldEnding3(int nodes)
{
	foldEnding3 = nodes;
	CString temp;
	temp.Format(_T("%d"), foldEnding3);
	foldEnding3Control.SetWindowText(temp);
}
void CNeuralNetView::dspFoldEnding4(int nodes)
{
	foldEnding4 = nodes;
	CString temp;
	temp.Format(_T("%d"), foldEnding4);
	foldEnding4Control.SetWindowText(temp);
}
void CNeuralNetView::dspExampleCount(int count)
{
	exampleCount = count;
	CString temp;
	temp.Format(_T("%d"), exampleCount);
	exampleCountControl.SetWindowText(temp);
}
void CNeuralNetView::dspExamplePosition(int position)
{
	examplePosition = position;
	CString temp;
	temp.Format(_T("%d"), examplePosition);
	examplePositionControl.SetWindowText(temp);
}


//BUTTON ACTIVATION METHODS
void CNeuralNetView::OnBnClickedNnfNetworkadd()
{
	CNeuralNetDoc* pDoc = GetDocument();

	bool valid = false;
	CString name = _T("");
	int input = netInput;
	int output = netOutput;
	int hidden1 = 0;
	int hidden2 = 0;
	int hidden3 = 0;
	int hidden4 = 0;
	double learning = 0.0;
	double momentum = 0.0;

	while (!valid)
	{
		CNetworkDialog dlg;
		dlg.name = name;
		dlg.input = input;
		dlg.output = output;
		dlg.hidden1 = hidden1;
		dlg.hidden2 = hidden2;
		dlg.hidden3 = hidden3;
		dlg.hidden4 = hidden4;
		dlg.learningRate = learning;
		dlg.momentum = momentum;

		INT_PTR nRet = dlg.DoModal();
		if (nRet == IDOK)
		{
			//get the values in case the network is not valid
			//so that the dialog is populated with the values just entered
			name = dlg.name;
			input = dlg.input;
			output = dlg.output;
			hidden1 = dlg.hidden1;
			hidden2 = dlg.hidden2;
			hidden3 = dlg.hidden3;
			hidden4 = dlg.hidden4;
			learning = dlg.learningRate;
			momentum = dlg.momentum;

			valid = pDoc->createNetwork(name, input, output, learning, momentum, hidden1, hidden2, hidden3, hidden4);

			if(valid)
			{
				dspNetName(dlg.name);
				dspNetInput(dlg.input);
				dspNetOutput(dlg.output);
				dspNetHidden1(dlg.hidden1);
				dspNetHidden2(dlg.hidden2);
				dspNetHidden3(dlg.hidden3);
				dspNetHidden4(dlg.hidden4);
				dspNetLearning(dlg.learningRate);
				dspNetMomentum(dlg.momentum);

				netAddControl.EnableWindow(FALSE);
				netEditControl.EnableWindow();
				//netSaveControl.EnableWindow();
				netResetControl.EnableWindow();

				if (exampleAppendControl.IsWindowEnabled() && foldModifyControl.IsWindowEnabled())
				{
					netTrainControl.EnableWindow();
					IANNTrainControl.EnableWindow();
				}
			}
		}
		else
			valid = true;
	}
}

void CNeuralNetView::OnBnClickedNnfNetworkedit()
{
	CNeuralNetDoc* pDoc = GetDocument();

	bool valid = false;
	CString name = netName;
	int input = netInput;
	int output = netOutput;
	int hidden1 = netHidden1;
	int hidden2 = netHidden2;
	int hidden3 = netHidden3;
	int hidden4 = netHidden4;
	double learning = netLearning;
	double momentum = netMomentum;

	while (!valid)
	{
		CNetworkDialog dlg;
		dlg.name = name;
		dlg.input = input;
		dlg.output = output;
		dlg.hidden1 = hidden1;
		dlg.hidden2 = hidden2;
		dlg.hidden3 = hidden3;
		dlg.hidden4 = hidden4;
		dlg.learningRate = learning;
		dlg.momentum = momentum;

		INT_PTR nRet = dlg.DoModal();
		if (nRet == IDOK)
		{
			//get the values in case the network is not valid
			//so that the dialog is populated with the values just entered
			name = dlg.name;
			input = dlg.input;
			output = dlg.output;
			hidden1 = dlg.hidden1;
			hidden2 = dlg.hidden2;
			hidden3 = dlg.hidden3;
			hidden4 = dlg.hidden4;
			learning = dlg.learningRate;
			momentum = dlg.momentum;

			valid = pDoc->editNetwork(name, input, output, learning, momentum, hidden1, hidden2, hidden3, hidden4);

			if(valid)
			{
				dspNetName(name);
				dspNetInput(input);
				dspNetOutput(output);
				dspNetHidden1(hidden1);
				dspNetHidden2(hidden2);
				dspNetHidden3(hidden3);
				dspNetHidden4(hidden4);
				dspNetLearning(learning);
				dspNetMomentum(momentum);
			}
		}
		else
			valid = true;
	}	
}

void CNeuralNetView::OnBnClickedNnfNetworkreset()
{
	CQuestionDialog dlg;
	dlg.message = _T("Are you sure you would like to Reset the network?");

	if (dlg.DoModal() == IDOK)
	{
		CNeuralNetDoc* pDoc = GetDocument();
		pDoc->resetNetwork();

		CString temp = _T("");
		dspNetName(temp);
		dspNetInput(0);
		dspNetOutput(0);
		dspNetHidden1(0);
		dspNetHidden2(0);
		dspNetHidden3(0);
		dspNetHidden4(0);
		dspNetLearning(0.0);
		dspNetMomentum(0.0);

		netAddControl.EnableWindow();
		netEditControl.EnableWindow(FALSE);
		//netSaveControl.EnableWindow(FALSE);
		netResetControl.EnableWindow(FALSE);
		netTrainControl.EnableWindow(FALSE);
		netRunTestControl.EnableWindow(FALSE);
		IANNTestControl.EnableWindow(FALSE);
		IANNTrainControl.EnableWindow(FALSE);
	}
}

void CNeuralNetView::OnBnClickedNnfAttributeadd()
{
	CNeuralNetDoc* pDoc = GetDocument();

	bool valid = false;
	CString name = _T("");
	double min = 0.0;
	double max = 0.0;
	double fri = 0.0;

	while (!valid)
	{
		CAttributeDialog dlg;
		dlg.name = name;
		dlg.minRange = min;
		dlg.maxRange = max;
		dlg.fri = fri;

		INT_PTR nRet = dlg.DoModal();
		if (nRet = IDOK)
		{
			//get the values
			name = dlg.name;
			min = dlg.minRange;
			max = dlg.maxRange;
			fri = dlg.fri;

			valid = pDoc->addAttribute(name, min, max, fri);

			if (valid)
			{
				attributeBoxControl.AddString(name);
				dspAttributeName(_T(""));
				dspAttributeMin(0.0);
				dspAttributeMax(0.0);
				dspAttributeFri(0.0);
				attributeEditControl.EnableWindow(FALSE);
			}
		}
		else
			valid = true;
	}
}

void CNeuralNetView::OnBnClickedNnfAttributeedit()
{
	CNeuralNetDoc* pDoc = GetDocument();

	bool valid = false;
	CString name = attributeName;
	CString previousName = attributeName;
	double min = attributeMin;
	double max = attributeMax;
	double fri = attributeFri;

	while (!valid)
	{
		CAttributeDialog dlg;
		dlg.name = name;
		dlg.minRange = min;
		dlg.maxRange = max;
		dlg.fri = fri;

		INT_PTR nRet = dlg.DoModal();
		if (nRet = IDOK)
		{
			//get the values
			name = dlg.name;
			min = dlg.minRange;
			max = dlg.maxRange;
			fri = dlg.fri;

			valid = pDoc->editAttribute(previousName, name, min, max, fri);

			if (valid)
			{
				attributeBoxControl.DeleteString(attributeSelection);
				attributeBoxControl.InsertString(attributeSelection, name);
				attributeBoxControl.SetCurSel(attributeSelection);
				dspAttributeName(name);
				dspAttributeMin(min);
				dspAttributeMax(max);
				dspAttributeFri(fri);
			}
		}
		else
			valid = true;
	}	
}

void CNeuralNetView::OnBnClickedAttributedelete()
{
	CQuestionDialog dlg;
	dlg.message = _T("Are you sure you wish to DELETE this Attribute?");
	if (dlg.DoModal() == IDOK)
	{
		CNeuralNetDoc* pDoc = GetDocument();
		if (pDoc->deleteAttribute(attributeName))
		{
			attributeBoxControl.DeleteString(attributeSelection);
			dspAttributeName(_T(""));
			dspAttributeMin(0.0);
			dspAttributeMax(0.0);
			dspAttributeFri(0.0);
		}
	}

}

void CNeuralNetView::OnCbnSelchangeNnfAttributebox()
{
	CNeuralNetDoc* pDoc = GetDocument();

	attributeSelection = attributeBoxControl.GetCurSel();

	if (attributeSelection >= 0)
	{
		dspAttributeName(pDoc->getAttributeName(attributeSelection));
		dspAttributeMin(pDoc->getAttributeMin(attributeSelection));
		dspAttributeMax(pDoc->getAttributeMax(attributeSelection));
		dspAttributeFri(pDoc->getAttributeFri(attributeSelection));
		
		attributeEditControl.EnableWindow();
	}
}

void CNeuralNetView::OnBnClickedNnfValueadd()
{
	CNeuralNetDoc* pDoc = GetDocument();

	bool valid = false;
	CString name = _T("");
	double min = 0.0;
	double max = 0.0;

	while (!valid)
	{
		CValueDialog dlg;
		dlg.name = name;
		dlg.minRange = min;
		dlg.maxRange = max;

		INT_PTR nRet = dlg.DoModal();
		if (nRet == IDOK)
		{
			name = dlg.name;
			min = dlg.minRange;
			max = dlg.maxRange;

			valid = pDoc->addValue(name, min, max);

			if (valid)
			{
				valueBoxControl.AddString(name);
				dspValueName(_T(""));
				dspValueMin(0.0);
				dspValueMax(0.0);
				valueEditControl.EnableWindow(FALSE);
			}
		}
		else
			valid = true;
	}
}

void CNeuralNetView::OnBnClickedNnfValueedit()
{
	CNeuralNetDoc* pDoc = GetDocument();

	bool valid = false;
	CString name = valueName;
	CString previousName = valueName;
	double min = valueMin;
	double max = valueMax;

	while (!valid)
	{
		CValueDialog dlg;
		dlg.name = name;
		dlg.minRange = min;
		dlg.maxRange = max;

		INT_PTR nRet = dlg.DoModal();
		if (nRet == IDOK)
		{
			name = dlg.name;
			min = dlg.minRange;
			max = dlg.maxRange;

			valid = pDoc->editValue(previousName, name, min, max);

			if (valid)
			{
				valueBoxControl.DeleteString(valueSelection);
				valueBoxControl.InsertString(valueSelection, name);
				valueBoxControl.SetCurSel(valueSelection);
				dspValueName(name);
				dspValueMin(min);
				dspValueMax(max);
			}
		}
		else
			valid = true;
	}
}

void CNeuralNetView::OnBnClickedNnfValuedelete()
{
	CQuestionDialog dlg;
	dlg.message = _T("Are you sure you wish to DELETE this Value?");
	if (dlg.DoModal() == IDOK)
	{
		CNeuralNetDoc* pDoc = GetDocument();
		if (pDoc->deleteValue(valueName))
		{
			valueBoxControl.DeleteString(valueSelection);
			dspValueName(_T(""));
			dspValueMin(0.0);
			dspValueMax(0.0);
		}
	}
}

void CNeuralNetView::OnCbnSelchangeNnfValuebox()
{
	CNeuralNetDoc* pDoc = GetDocument();

	valueSelection = valueBoxControl.GetCurSel();

	if (valueSelection >= 0)
	{
		dspValueName(pDoc->getValueName(valueSelection));
		dspValueMin(pDoc->getValueMin(valueSelection));
		dspValueMax(pDoc->getValueMax(valueSelection));
		
		valueEditControl.EnableWindow();
	}
}

void CNeuralNetView::OnEnChangeNnfExamplename()
{
	UpdateData();
}

void CNeuralNetView::OnBnClickedNnfExampleload()
{
	CNeuralNetDoc* pDoc = GetDocument();
	if (!(exampleName.IsEmpty()))
	{
		if (pDoc->loadExamples(exampleName))
		{
			dspExampleCount(pDoc->getExampleCount());
			if (pDoc->setStartingPosition(0))
				dspExamplePosition(pDoc->getStartingPosition());
			else
				dspExamplePosition(-1);
			examplePositionChangeControl.EnableWindow();
			examplePositionControl.EnableWindow();
			exampleLoadControl.EnableWindow(FALSE);
			exampleAppendControl.EnableWindow();
			exampleResetControl.EnableWindow();
			exampleShuffleControl.EnableWindow();
			exampleShuffleSaveControl.EnableWindow();
			
			if (foldModifyControl.IsWindowEnabled() && netEditControl.IsWindowEnabled())
			{
				netTrainControl.EnableWindow();
				IANNTrainControl.EnableWindow();
			}

		}
		else
		{
			CErrorDlg dlg;
			dlg.error = _T("Unable to load Example File");
			if (dlg.DoModal() == IDOK) {}
			
		}
	}
	else
	{
		CErrorDlg dlg;
		dlg.error = _T("the example filename is empty");
		if (dlg.DoModal() == IDOK) {}
		
	}
}

void CNeuralNetView::OnBnClickedNnfExampleappend()
{
	CNeuralNetDoc* pDoc = GetDocument();
	if (!(exampleName.IsEmpty()))
	{
		if (pDoc->appendExamples(exampleName))
		{
			dspExampleCount(pDoc->getExampleCount());
		}
		else
		{
			CErrorDlg dlg;
			dlg.error = _T("Unable to append Example File");
			if (dlg.DoModal() == IDOK) {}
		}
	}
	else
	{
		CErrorDlg dlg;
		dlg.error = _T("the example filename is empty");
		if (dlg.DoModal() == IDOK) {}
	}
}

void CNeuralNetView::OnBnClickedNnfExamplereset()
{
	CNeuralNetDoc* pDoc = GetDocument();
	CQuestionDialog dlg;
	dlg.message = _T("Are you sure you would like to reset ALL examples?");
	if (dlg.DoModal() == IDOK)
	{
		pDoc->resetExamples();
		dspExampleCount(pDoc->getExampleCount());
		if (pDoc->setStartingPosition(0))
			dspExamplePosition(pDoc->getStartingPosition());
		else
			dspExamplePosition(-1);
		examplePositionChangeControl.EnableWindow(FALSE);
		examplePositionControl.EnableWindow(FALSE);
		exampleShuffleControl.EnableWindow(FALSE);
		exampleShuffleSaveControl.EnableWindow(FALSE);
		exampleLoadControl.EnableWindow();
		exampleAppendControl.EnableWindow(FALSE);
		exampleResetControl.EnableWindow(FALSE);
		netTrainControl.EnableWindow(FALSE);
		netRunTestControl.EnableWindow(FALSE);
		IANNTestControl.EnableWindow(FALSE);
		IANNTrainControl.EnableWindow(FALSE);
	}
}

void CNeuralNetView::OnBnClickedNnfFoldsetup()
{
	CNeuralNetDoc* pDoc = GetDocument();

	bool valid = false;
	int folds = 0;
	int epochs = 0;
	double criteria = 0.0;
	int runs = 0;
	int startingLayer = 0;
	int endingLayer = 0;
	int starting1 = 0;
	int starting2 = 0;
	int starting3 = 0;
	int starting4 = 0;
	int ending1 = 0;
	int ending2 = 0;
	int ending3 = 0;
	int ending4 = 0;

	while (!valid)
	{
		CFoldDialog dlg;
		dlg.folds = folds;
		dlg.epochs = epochs;
		dlg.criteria = criteria;
		dlg.runs = runs;
		dlg.startingLayer = startingLayer;
		dlg.endingLayer = endingLayer;
		dlg.starting1 = starting1;
		dlg.starting2 = starting2;
		dlg.starting3 = starting3;
		dlg.starting4 = starting4;
		dlg.ending1 = ending1;
		dlg.ending2 = ending2;
		dlg.ending3 = ending3;
		dlg.ending4 = ending4;

		INT_PTR nRet = dlg.DoModal();
		if (nRet == IDOK)
		{
			folds = dlg.folds;
			epochs = dlg.epochs;
			criteria = dlg.criteria;
			runs = dlg.runs;
			startingLayer = dlg.startingLayer;
			endingLayer = dlg.endingLayer;
			starting1 = dlg.starting1;
			starting2 = dlg.starting2;
			starting3 = dlg.starting3;
			starting4 = dlg.starting4;
			ending1 = dlg.ending1;
			ending2 = dlg.ending2;
			ending3 = dlg.ending3;
			ending4 = dlg.ending4;

			valid = pDoc->setKFoldParameters(folds, epochs, criteria, runs, startingLayer, endingLayer,
				starting1, starting2, starting3, starting4, ending1, ending2, ending3, ending4);

			if (valid)
			{
				dspFoldFolds(folds);
				dspFoldEpochs(epochs);
				dspFoldCriteria(criteria);
				dspFoldRuns(runs);
				dspFoldStartingLayer(startingLayer);
				dspFoldEndingLayer(endingLayer);
				dspFoldStarting1(starting1);
				dspFoldStarting2(starting2);
				dspFoldStarting3(starting3);
				dspFoldStarting4(starting4);
				dspFoldEnding1(ending1);
				dspFoldEnding2(ending2);
				dspFoldEnding3(ending3);
				dspFoldEnding4(ending4);

				foldSetupControl.EnableWindow(FALSE);
				foldModifyControl.EnableWindow();
				foldResetControl.EnableWindow();

				if (exampleAppendControl.IsWindowEnabled() && netEditControl.IsWindowEnabled())
				{
					netTrainControl.EnableWindow();
					IANNTrainControl.EnableWindow();
				}
			}
		}
		else
			valid = true;
	}
}

void CNeuralNetView::OnBnClickedNnfFoldmodify()
{
	CNeuralNetDoc* pDoc = GetDocument();
	
	bool valid = false;
	int folds = foldFolds;
	int epochs = foldEpochs;
	double criteria = foldCriteria;
	int runs = foldRuns;
	int startingLayer = foldStartingLayer;
	int endingLayer = foldEndingLayer;
	int starting1 = foldStarting1;
	int starting2 = foldStarting2;
	int starting3 = foldStarting3;
	int starting4 = foldStarting4;
	int ending1 = foldEnding1;
	int ending2 = foldEnding2;
	int ending3 = foldEnding3;
	int ending4 = foldEnding4;

	while (!valid)
	{
		CFoldDialog dlg;
		dlg.folds = folds;
		dlg.epochs = epochs;
		dlg.criteria = criteria;
		dlg.runs = runs;
		dlg.startingLayer = startingLayer;
		dlg.endingLayer = endingLayer;
		dlg.starting1 = starting1;
		dlg.starting2 = starting2;
		dlg.starting3 = starting3;
		dlg.starting4 = starting4;
		dlg.ending1 = ending1;
		dlg.ending2 = ending2;
		dlg.ending3 = ending3;
		dlg.ending4 = ending4;

		INT_PTR nRet = dlg.DoModal();
		if (nRet == IDOK)
		{
			folds = dlg.folds;
			epochs = dlg.epochs;
			criteria = dlg.criteria;
			runs = dlg.runs;
			startingLayer = dlg.startingLayer;
			endingLayer = dlg.endingLayer;
			starting1 = dlg.starting1;
			starting2 = dlg.starting2;
			starting3 = dlg.starting3;
			starting4 = dlg.starting4;
			ending1 = dlg.ending1;
			ending2 = dlg.ending2;
			ending3 = dlg.ending3;
			ending4 = dlg.ending4;

			valid = pDoc->setKFoldParameters(folds, epochs, criteria, runs, startingLayer, endingLayer,
				starting1, starting2, starting3, starting4, ending1, ending2, ending3, ending4);

			if (valid)
			{
				dspFoldFolds(folds);
				dspFoldEpochs(epochs);
				dspFoldCriteria(criteria);
				dspFoldRuns(runs);
				dspFoldStartingLayer(startingLayer);
				dspFoldEndingLayer(endingLayer);
				dspFoldStarting1(starting1);
				dspFoldStarting2(starting2);
				dspFoldStarting3(starting3);
				dspFoldStarting4(starting4);
				dspFoldEnding1(ending1);
				dspFoldEnding2(ending2);
				dspFoldEnding3(ending3);
				dspFoldEnding4(ending4);
			}
		}
		else
			valid = true;
	}
}

void CNeuralNetView::OnBnClickedNnfFoldreset()
{
	CNeuralNetDoc* pDoc = GetDocument();

	CQuestionDialog dlg;
	dlg.message = _T("Are you sure you want to reset the K-Fold parameters?");
	if (dlg.DoModal() == IDOK)
	{
		pDoc->setKFoldParameters(0, 0, 0.0, 0, 0, 0);

		dspFoldFolds(0);
		dspFoldEpochs(0);
		dspFoldCriteria(0.0);
		dspFoldRuns(0);
		dspFoldStartingLayer(0);
		dspFoldEndingLayer(0);
		dspFoldStarting1(0);
		dspFoldStarting2(0);
		dspFoldStarting3(0);
		dspFoldStarting4(0);
		dspFoldEnding1(0);
		dspFoldEnding2(0);
		dspFoldEnding3(0);
		dspFoldEnding4(0);

		foldSetupControl.EnableWindow();
		foldModifyControl.EnableWindow(FALSE);
		foldResetControl.EnableWindow(FALSE);
		netTrainControl.EnableWindow(FALSE);
		netRunTestControl.EnableWindow(FALSE);
		IANNTestControl.EnableWindow(FALSE);
		IANNTrainControl.EnableWindow(FALSE);
	}
}

void CNeuralNetView::OnBnClickedNnfAttributeload()
{
	CQuestionDialog dlg;
	dlg.message = _T("This action will remove all current Attributes. Do you want to continue?");
	if (dlg.DoModal() == IDOK)
	{
		CNeuralNetDoc* pDoc = GetDocument();
		if (!(attributeFileName.IsEmpty()))
		{
			if (pDoc->loadAttributes(attributeFileName))
			{
				attributeBoxControl.ResetContent();
				int atts = pDoc->getAttributeNumber();
				for (int x = 0; x < atts; ++x)
				{
					attributeBoxControl.AddString(pDoc->getAttributeName(x));
				}
			}
			else
			{
				CErrorDlg dlg;
				dlg.error = _T("Unable to load Attribute File");
				if (dlg.DoModal() == IDOK) {}
			}
		}
		else
		{
			CErrorDlg dlg;
			dlg.error = _T("Please enter an Attribute File Name to load");
			if (dlg.DoModal() == IDOK)  {}
		}
	}
}

void CNeuralNetView::OnBnClickedNnfValueload()
{
	CQuestionDialog dlg;
	dlg.message = _T("This action will remove all current Values. Do you want to continue?");
	if (dlg.DoModal() == IDOK)
	{
		CNeuralNetDoc* pDoc = GetDocument();
		if(!(valueFileName.IsEmpty()))
		{
			if (pDoc->loadValues(valueFileName))
			{
				valueBoxControl.ResetContent();
				int vals = pDoc->getValueNumber();
				for (int x = 0; x < vals; ++x)
				{
					valueBoxControl.AddString(pDoc->getValueName(x));
				}
			}
			else
			{
				CErrorDlg dlg;
				dlg.error = _T("Unable to load Value File");
				if (dlg.DoModal() == IDOK) {}
			}
		}
		else
		{
			CErrorDlg dlg;
			dlg.error = _T("Please enter a Value File Name to load");
			if (dlg.DoModal() == IDOK) {}
		}
	}
}

void CNeuralNetView::OnEnChangeNnfAttributefilename()
{
	UpdateData();
}

void CNeuralNetView::OnEnChangeNnfValuefilename()
{
	UpdateData();
}

void CNeuralNetView::OnBnClickedNnfExamplepositionchange()
{
	CNeuralNetDoc* pDoc = GetDocument();
	if (!(pDoc->setStartingPosition(examplePosition)))
	{
		CErrorDlg dlg;
		dlg.error = _T("Unable to set starting position to that value.");
		if (dlg.DoModal() == IDOK) {}
	}
	else
	{
		dspExamplePosition(examplePosition);
	}
}

void CNeuralNetView::OnEnChangeNnfExamplestartposition()
{
	UpdateData();
}

void CNeuralNetView::OnBnClickedNnfExampleshuffle()
{
	CNeuralNetDoc* pDoc = GetDocument();
	pDoc->shuffleExamples();
	exampleShuffleSaveControl.EnableWindow();
	exampleShuffleNameControl.EnableWindow();
}

void CNeuralNetView::OnBnClickedNnfExamplesaveshuffled()
{
	if (exampleShuffleName.IsEmpty())
	{
		CErrorDlg dlg;
		dlg.error = _T("Please enter a valid file name to save the shuffled examples.");
		if (dlg.DoModal() == IDOK) {}
	}
	else
	{
		CNeuralNetDoc* pDoc = GetDocument();
		if (pDoc->saveShuffledExamples(exampleShuffleName))
		{
			CErrorDlg dlg;
			dlg.error = _T("Shuffled examples have been saved.");
			if (dlg.DoModal() == IDOK) {}
		}
		else
		{
			CErrorDlg dlg;
			dlg.error = _T("Unable to save shuffled examples.");
			if (dlg.DoModal() == IDOK) {}
		}
	}
}

void CNeuralNetView::OnEnChangeNnfExampleshufflename()
{
	UpdateData();
}

void CNeuralNetView::OnBnClickedNnfFoldrunall()
{
	CNeuralNetDoc* pDoc = GetDocument();
	pDoc->runKFoldModel();
}

void CNeuralNetView::OnEnChangeNnfNetfilename()
{
	UpdateData();
}

void CNeuralNetView::OnBnClickedNnfNetexampleload()
{
	CNeuralNetDoc* pDoc = GetDocument();
	if (pDoc->loadNetExamples(netExampleName))
	{
		CErrorDlg dlg;
		dlg.error = _T("Net Examples Loaded Correctly");
		if (dlg.DoModal() == IDOK) {}
		netRunTestControl.EnableWindow();
	}
	else
	{
		CErrorDlg dlg;
		dlg.error = _T("Unable to load Net Examples!!");
		if (dlg.DoModal() == IDOK) {}
		netRunTestControl.EnableWindow(FALSE);
		IANNTestControl.EnableWindow(FALSE);
	}
}

void CNeuralNetView::OnBnClickedNnfNetrun()
{
	CNeuralNetDoc* pDoc = GetDocument();
	if (pDoc->runNetExamples())
	{
		CErrorDlg dlg;
		dlg.error = _T("Finished running examples");
		if (dlg.DoModal() == IDOK) {}
	}
	else
	{
		CErrorDlg dlg;
		dlg.error = _T("Unable to run the examples.");
		if (dlg.DoModal() == IDOK) {}
	}
}

void CNeuralNetView::OnBnClickedNnfNettrain()
{
	CNeuralNetDoc* pDoc = GetDocument();
	if (pDoc->trainNetwork())
	{
		CErrorDlg dlg;
		dlg.error = _T("Finished Training the Network");
		if (dlg.DoModal() == IDOK) {}
		netRunTestControl.EnableWindow();
	}
	else
	{
		CErrorDlg dlg;
		dlg.error = _T("Unable to Train the Network");
		if (dlg.DoModal() == IDOK) {}
	}
}

void CNeuralNetView::OnBnClickedNnfNetianntrain()
{
	CNeuralNetDoc* pDoc = GetDocument();
	if (pDoc->trainIANNNetwork())
	{
		CErrorDlg dlg;
		dlg.error = _T("Finished Training the IANN Network");
		if (dlg.DoModal() == IDOK) {}
		IANNTestControl.EnableWindow();
	}
	else
	{
		CErrorDlg dlg;
		dlg.error = _T("Unable to Train the IANN Network");
		if (dlg.DoModal() == IDOK) {}
	}
}

void CNeuralNetView::OnBnClickedNnfNetianntest()
{
	CNeuralNetDoc* pDoc = GetDocument();
	if (pDoc->runNetExamples())
	{
		CErrorDlg dlg;
		dlg.error = _T("Finished running examples");
		if (dlg.DoModal() == IDOK) {}
	}
	else
	{
		CErrorDlg dlg;
		dlg.error = _T("Unable to run the examples.");
		if (dlg.DoModal() == IDOK) {}
	}
}


void CNeuralNetView::OnEnChangeNnfValuemin()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

//*****************************************
//********* ADDED 2 27 2011 ***************
//*****************************************
void CNeuralNetView::OnEnChangeNnTestruns()
{
	UpdateData();
}

void CNeuralNetView::OnEnChangeNnSeed()
{
	UpdateData();
}

void CNeuralNetView::OnBnClickedNnfTestrunsload()
{
	CNeuralNetDoc* pDoc = GetDocument();
	UpdateData();
	if (!pDoc->setTestRuns(testRuns))
	{
		CErrorDlg dlg;
		dlg.error = _T("Unable to set number of test runs.");
		if (dlg.DoModal() == IDOK) {}
	}
}

void CNeuralNetView::OnBnClickedNnfSeedload()
{
	CNeuralNetDoc* pDoc = GetDocument();
	UpdateData();
	if (!pDoc->setSeed(seed))
	{
		CErrorDlg dlg;
		dlg.error = _T("Unable to set seed for test runs.");
		if (dlg.DoModal() == IDOK) {}
	}
}


void CNeuralNetView::OnBnClickedRunconcecutivetests()
{
	CNeuralNetDoc* pDoc = GetDocument();

	if (!pDoc->runConsecutiveTests())
	{
		CErrorDlg dlg;
		dlg.error = _T("Unable to start concecutive tests for ANN.");
		if (dlg.DoModal() == IDOK) {}
	}
}


void CNeuralNetView::OnBnClickedRunconcecutivetests2()
{
	CNeuralNetDoc* pDoc = GetDocument();

	if (!pDoc->runConsecutiveIANNTests())
	{
		CErrorDlg dlg;
		dlg.error = _T("Unable to start consecutive tests for IANN.");
		if (dlg.DoModal() == IDOK) {}
	}
}
