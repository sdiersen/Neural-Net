// ValueDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Neural Net.h"
#include "ValueDialog.h"
#include "afxdialogex.h"


// CValueDialog dialog

IMPLEMENT_DYNAMIC(CValueDialog, CDialogEx)

CValueDialog::CValueDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CValueDialog::IDD, pParent)
	, name(_T(""))
	, minRange(0)
	, maxRange(0)
	, error(_T(""))
{

}

CValueDialog::~CValueDialog()
{
}

void CValueDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EV_VALUENAME, nameControl);
	DDX_Control(pDX, IDC_EV_VALUEMIN, minControl);
	DDX_Control(pDX, IDC_EV_VALUEMAX, maxControl);
	DDX_Control(pDX, IDC_EV_VALUEERROR, errorControl);
	DDX_Control(pDX, IDC_EV_VALIDATE, validateControl);
	DDX_Control(pDX, IDOK, okControl);
	DDX_Text(pDX, IDC_EV_VALUENAME, name);
	DDX_Text(pDX, IDC_EV_VALUEMIN, minRange);
	DDX_Text(pDX, IDC_EV_VALUEMAX, maxRange);
	DDX_Text(pDX, IDC_EV_VALUEERROR, error);
}


BEGIN_MESSAGE_MAP(CValueDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EV_VALUENAME, &CValueDialog::OnEnChangeEvValuename)
	ON_EN_CHANGE(IDC_EV_VALUEMIN, &CValueDialog::OnEnChangeEvValuemin)
	ON_EN_CHANGE(IDC_EV_VALUEMAX, &CValueDialog::OnEnChangeEvValuemax)
	ON_BN_CLICKED(IDC_EV_VALIDATE, &CValueDialog::OnBnClickedEvValidate)
END_MESSAGE_MAP()


// CValueDialog message handlers


void CValueDialog::OnEnChangeEvValuename()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CValueDialog::OnEnChangeEvValuemin()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CValueDialog::OnEnChangeEvValuemax()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CValueDialog::OnBnClickedEvValidate()
{
	UpdateData();

	if (minRange > maxRange)
	{
		okControl.EnableWindow(FALSE);
		error = _T("the Range Max must be greater than or equal to the Range Min.");
		errorControl.SetWindowText(error);
	}
	else if (name.IsEmpty())
	{
		okControl.EnableWindow(FALSE);
		error = _T("Please enter a Name for this Value.");
		errorControl.SetWindowText(error);
	}
	else
	{
		okControl.EnableWindow();
	}
}
