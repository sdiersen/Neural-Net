#pragma once


// CQuestionDialog dialog

class CQuestionDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CQuestionDialog)

public:
	CQuestionDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CQuestionDialog();

// Dialog Data
	enum { IDD = IDD_QUESTIONDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString message;
};
