#pragma once
#include "afxwin.h"


// CErrorDlg dialog

class CErrorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CErrorDlg)

public:
	CErrorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CErrorDlg();

// Dialog Data
	enum { IDD = IDD_ERRORDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit errorControl;
	CString error;
};
