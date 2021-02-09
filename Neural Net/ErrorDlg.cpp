// ErrorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Neural Net.h"
#include "ErrorDlg.h"
#include "afxdialogex.h"


// CErrorDlg dialog

IMPLEMENT_DYNAMIC(CErrorDlg, CDialogEx)

CErrorDlg::CErrorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CErrorDlg::IDD, pParent)
	, error(_T(""))
{

}

CErrorDlg::~CErrorDlg()
{
}

void CErrorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ERRORMESSAGE, errorControl);
	DDX_Text(pDX, IDC_ERRORMESSAGE, error);
}


BEGIN_MESSAGE_MAP(CErrorDlg, CDialogEx)
END_MESSAGE_MAP()


// CErrorDlg message handlers
