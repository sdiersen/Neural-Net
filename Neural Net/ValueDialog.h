#pragma once
#include "afxwin.h"


// CValueDialog dialog

class CValueDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CValueDialog)

public:
	CValueDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CValueDialog();

// Dialog Data
	enum { IDD = IDD_ENTERVALUEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit nameControl;
	CEdit minControl;
	CEdit maxControl;
	CEdit errorControl;
	CButton validateControl;
	CButton okControl;
	CString name;
	double minRange;
	double maxRange;
	CString error;
	afx_msg void OnEnChangeEvValuename();
	afx_msg void OnEnChangeEvValuemin();
	afx_msg void OnEnChangeEvValuemax();
	afx_msg void OnBnClickedEvValidate();
};
