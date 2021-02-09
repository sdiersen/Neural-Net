#pragma once
#include "afxwin.h"


// CAttributeDialog dialog

class CAttributeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CAttributeDialog)

public:
	CAttributeDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAttributeDialog();

// Dialog Data
	enum { IDD = IDD_ENTERATTRIBUTEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit nameControl;
	CEdit minControl;
	CEdit maxControl;
	CEdit friControl;
	CEdit errorControl;
	CButton validateControl;
	CButton okControl;
	CString name;
	double minRange;
	double maxRange;
	double fri;
	CString error;
	afx_msg void OnEnChangeEaAttributename();
	afx_msg void OnEnChangeEaAttributemin();
	afx_msg void OnEnChangeEaAttributemax();
	afx_msg void OnEnChangeEaAttributefri();
	afx_msg void OnBnClickedEaAttributevalidate();
};
