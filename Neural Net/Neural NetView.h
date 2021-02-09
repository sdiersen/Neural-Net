
// Neural NetView.h : interface of the CNeuralNetView class
//

#pragma once

#include "resource.h"
#include "afxwin.h"
#include "NetworkDialog.h"
#include "AttributeDialog.h"
#include "ValueDialog.h"
#include "FoldDialog.h"
#include "QuestionDialog.h"


class CNeuralNetView : public CFormView
{
protected: // create from serialization only
	CNeuralNetView();
	DECLARE_DYNCREATE(CNeuralNetView)

public:
	enum{ IDD = IDD_NEURALNET_FORM };

// Attributes
public:
	CNeuralNetDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

// Implementation
public:
	virtual ~CNeuralNetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeNnfAttributemin();
	CButton netAddControl;
	CButton netEditControl;
	CButton netSaveControl;
	CButton netResetControl;
	CButton attributeAddControl;
	CButton attributeEditControl;
	CButton attributeSaveControl;
	CButton attributeDeleteControl;
	CButton valueAddControl;
	CButton valueEditControl;
	CButton valueSaveControl;
	CButton valueDeleteControl;
	CButton exampleLoadControl;
	CButton exampleAppendControl;
	CButton exampleResetControl;
	CButton foldSetupControl;
	CButton foldModifyControl;
	CButton foldResetControl;
	CEdit netNameControl;
	CEdit netInputControl;
	CEdit netHidden1Control;
	CEdit netHidden2Control;
	CEdit netHidden3Control;
	CEdit netHidden4Control;
	CEdit netOutputControl;
	CEdit netLearningControl;
	CEdit netMomentumControl;
	CComboBox attributeBoxControl;
	CEdit attributeNameControl;
	CEdit attributeMinControl;
	CEdit attributeMaxControl;
	CEdit attributeFriControl;
	CComboBox valueBoxControl;
	CEdit valueNameControl;
	CEdit valueMinControl;
	CEdit valueMaxControl;
	CEdit exampleNameControl;
	CEdit foldFoldsControl;
	CEdit foldEpochsControl;
	CEdit foldCriteriaControl;
	CEdit foldRunsControl;
	CEdit foldStartingLayerControl;
	CEdit foldEndingLayerControl;
	CEdit foldStarting1Control;
	CEdit foldStarting2Control;
	CEdit foldStarting3Control;
	CEdit foldStarting4Control;
	CEdit foldEnding1Control;
	CEdit foldEnding2Control;
	CEdit foldEnding3Control;
	CEdit foldEnding4Control;
	CString netName;
	int netInput;
	int netHidden1;
	int netHidden2;
	int netHidden3;
	int netHidden4;
	int netOutput;
	double netLearning;
	double netMomentum;
	CString attributeName;
	double attributeMin;
	double attributeMax;
	double attributeFri;
	CString valueName;
	double valueMin;
	double valueMax;
	CString exampleName;
	int foldFolds;
	int foldEpochs;
	double foldCriteria;
	int foldRuns;
	int foldStartingLayer;
	int foldEndingLayer;
	int foldStarting1;
	int foldStarting2;
	int foldStarting3;
	int foldStarting4;
	int foldEnding1;
	int foldEnding2;
	int foldEnding3;
	int foldEnding4;
	void dspNetName(CString name);
	void dspNetInput(int nodes);
	void dspNetHidden1(int nodes);
	void dspNetHidden2(int nodes);
	void dspNetHidden3(int nodes);
	void dspNetHidden4(int nodes);
	void dspNetOutput(int output);
	void dspNetLearning(double learning);
	void dspNetMomentum(double momentum);
	void dspAttributeName(CString name);
	void dspAttributeMin(double min);
	void dspAttributeMax(double max);
	void dspAttributeFri(double fri);
	void dspValueName(CString name);
	void dspValueMin(double min);
	void dspValueMax(double max);
	void dspExampleName(CString name);
	void dspFoldFolds(int folds);
	void dspFoldEpochs(int epochs);
	void dspFoldCriteria(double criteria);
	void dspFoldRuns(int runs);
	void dspFoldStartingLayer(int starting);
	void dspFoldEndingLayer(int ending);
	void dspFoldStarting1(int nodes);
	void dspFoldStarting2(int nodes);
	void dspFoldStarting3(int nodes);
	void dspFoldStarting4(int nodes);
	void dspFoldEnding1(int nodes);
	void dspFoldEnding2(int nodes);
	void dspFoldEnding3(int nodes);
	void dspFoldEnding4(int nodes);
	afx_msg void OnBnClickedNnfNetworkadd();
	afx_msg void OnBnClickedNnfNetworkedit();
	afx_msg void OnBnClickedNnfNetworkreset();
	afx_msg void OnBnClickedNnfAttributeadd();
	afx_msg void OnBnClickedNnfAttributeedit();
	afx_msg void OnBnClickedAttributedelete();
	int attributeSelection;
	int valueSelection;
	afx_msg void OnCbnSelchangeNnfAttributebox();
	afx_msg void OnBnClickedNnfValueadd();
	afx_msg void OnBnClickedNnfValueedit();
	afx_msg void OnBnClickedNnfValuedelete();
	afx_msg void OnCbnSelchangeNnfValuebox();
	afx_msg void OnEnChangeNnfExamplename();
	afx_msg void OnBnClickedNnfExampleload();
	afx_msg void OnBnClickedNnfExampleappend();
	afx_msg void OnBnClickedNnfExamplereset();
	afx_msg void OnBnClickedNnfFoldsetup();
	afx_msg void OnBnClickedNnfFoldmodify();
	afx_msg void OnBnClickedNnfFoldreset();
	CEdit attributeFileNameControl;
	CEdit valueFileNameControl;
	CString attributeFileName;
	CString valueFileName;
	afx_msg void OnBnClickedNnfAttributeload();
	afx_msg void OnBnClickedNnfValueload();
	afx_msg void OnEnChangeNnfAttributefilename();
	afx_msg void OnEnChangeNnfValuefilename();
	CEdit exampleCountControl;
	CEdit examplePositionControl;
	int exampleCount;
	int examplePosition;
	CButton examplePositionChangeControl;
	void dspExampleCount(int count);
	void dspExamplePosition(int position);
	afx_msg void OnBnClickedNnfExamplepositionchange();
	afx_msg void OnEnChangeNnfExamplestartposition();
	afx_msg void OnBnClickedNnfExampleshuffle();
	afx_msg void OnBnClickedNnfExamplesaveshuffled();
	CButton exampleShuffleControl;
	CButton exampleShuffleSaveControl;
	CEdit exampleShuffleNameControl;
	CString exampleShuffleName;
	afx_msg void OnEnChangeNnfExampleshufflename();
	afx_msg void OnBnClickedNnfFoldrunall();
	CButton foldRunControl;
	CButton netRunTestControl;
	CString netExampleName;
	afx_msg void OnEnChangeNnfNetfilename();
	afx_msg void OnBnClickedNnfNetexampleload();
	afx_msg void OnBnClickedNnfNetrun();
	CButton netTrainControl;
	afx_msg void OnBnClickedNnfNettrain();
	CButton IANNTrainControl;
	CButton IANNTestControl;
	afx_msg void OnBnClickedNnfNetianntrain();
	afx_msg void OnBnClickedNnfNetianntest();
	afx_msg void OnEnChangeNnfValuemin();

	//*************************************************
	//*************** Added 2 27 2011 *****************
	//*************************************************
public:
	afx_msg void OnEnChangeNnTestruns();
	afx_msg void OnEnChangeNnSeed();
	afx_msg void OnBnClickedNnfTestrunsload();
	afx_msg void OnBnClickedNnfSeedload();
	afx_msg void OnBnClickedRunconcecutivetests();
	afx_msg void OnBnClickedRunconcecutivetests2();
	int testRuns;
	int seed;
};
	//end 2 27 2011

#ifndef _DEBUG  // debug version in Neural NetView.cpp
inline CNeuralNetDoc* CNeuralNetView::GetDocument() const
   { return reinterpret_cast<CNeuralNetDoc*>(m_pDocument); }
#endif

