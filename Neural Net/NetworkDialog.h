#pragma once
#include "afxwin.h"


// CNetworkDialog dialog

class CNetworkDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CNetworkDialog)

public:
	CNetworkDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNetworkDialog();

// Dialog Data
	enum { IDD = IDD_CREATENETWORK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit nameControl;
	CEdit inputControl;
	CEdit outputControl;
	CEdit hidden1Control;
	CEdit hidden2Control;
	CEdit hidden3Control;
	CEdit hidden4Control;
	CEdit learningRateControl;
	CEdit momentumControl;
	CButton validateControl;
	CButton okControl;
	CEdit errorControl;
	CString name;
	int input;
	int output;
	int hidden1;
	int hidden2;
	int hidden3;
	int hidden4;
	double learningRate;
	double momentum;
	CString error;
	
	afx_msg void OnEnChangeCnNetname();
	afx_msg void OnEnChangeCnNetinput();
	afx_msg void OnEnChangeCnNetoutput();
	afx_msg void OnEnChangeCnNethidden1();
	afx_msg void OnEnChangeCnNethidden2();
	afx_msg void OnEnChangeCnNethidden3();
	afx_msg void OnEnChangeCnNethidden4();
	afx_msg void OnEnChangeCnNetlearning();
	afx_msg void OnEnChangeCnNetmomentum();
	afx_msg void OnBnClickedCnNetvalidate();
};
