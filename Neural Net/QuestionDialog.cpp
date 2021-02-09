// QuestionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Neural Net.h"
#include "QuestionDialog.h"
#include "afxdialogex.h"


// CQuestionDialog dialog

IMPLEMENT_DYNAMIC(CQuestionDialog, CDialogEx)

CQuestionDialog::CQuestionDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQuestionDialog::IDD, pParent)
	, message(_T(""))
{

}

CQuestionDialog::~CQuestionDialog()
{
}

void CQuestionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_QUESTIONMESSAGE, message);
}


BEGIN_MESSAGE_MAP(CQuestionDialog, CDialogEx)
END_MESSAGE_MAP()


// CQuestionDialog message handlers
