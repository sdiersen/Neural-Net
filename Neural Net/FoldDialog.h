#pragma once
#include "afxwin.h"


// CFoldDialog dialog

class CFoldDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CFoldDialog)

public:
	CFoldDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFoldDialog();

// Dialog Data
	enum { IDD = IDD_KFOLDDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit foldControl;
	CEdit epochsControl;
	CEdit criteriaControl;
	CEdit runsControl;
	CEdit startingLayerControl;
	CEdit endingLayerControl;
	CEdit starting1Control;
	CEdit starting2Control;
	CEdit starting3Control;
	CEdit starting4Control;
	CEdit ending1Control;
	CEdit ending2Control;
	CEdit ending3Control;
	CEdit ending4Control;
	CEdit errorControl;
	CButton validateControl;
	CButton okControl;
	int folds;
	int epochs;
	double criteria;
	int runs;
	int startingLayer;
	int endingLayer;
	int starting1;
	int starting2;
	int starting3;
	int starting4;
	int ending1;
	int ending2;
	int ending3;
	int ending4;
	CString error;
	afx_msg void OnEnChangeFoldfolds();
	afx_msg void OnEnChangeFoldepochs();
	afx_msg void OnEnChangeFoldstopping();
	afx_msg void OnEnChangeFoldruns();
	afx_msg void OnEnChangeFoldstartinglayer();
	afx_msg void OnEnChangeFoldendinglayer();
	afx_msg void OnEnChangeFoldstarting1();
	afx_msg void OnEnChangeFoldstarting2();
	afx_msg void OnEnChangeFoldstarting3();
	afx_msg void OnEnChangeFoldstarting4();
	afx_msg void OnEnChangeFoldending1();
	afx_msg void OnEnChangeFoldending2();
	afx_msg void OnEnChangeFoldending3();
	afx_msg void OnEnChangeFoldending4();
	afx_msg void OnBnClickedFoldvalidate();
};
