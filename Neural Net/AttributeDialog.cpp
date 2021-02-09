// AttributeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Neural Net.h"
#include "AttributeDialog.h"
#include "afxdialogex.h"


// CAttributeDialog dialog

IMPLEMENT_DYNAMIC(CAttributeDialog, CDialogEx)

CAttributeDialog::CAttributeDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAttributeDialog::IDD, pParent)
	, name(_T(""))
	, minRange(0)
	, maxRange(0)
	, fri(0)
	, error(_T(""))
{

}

CAttributeDialog::~CAttributeDialog()
{
}

void CAttributeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EA_ATTRIBUTENAME, nameControl);
	DDX_Control(pDX, IDC_EA_ATTRIBUTEMIN, minControl);
	DDX_Control(pDX, IDC_EA_ATTRIBUTEMAX, maxControl);
	DDX_Control(pDX, IDC_EA_ATTRIBUTEFRI, friControl);
	DDX_Control(pDX, IDC_EA_ATTRIBUTEERROR, errorControl);
	DDX_Control(pDX, IDC_EA_ATTRIBUTEVALIDATE, validateControl);
	DDX_Control(pDX, IDOK, okControl);
	DDX_Text(pDX, IDC_EA_ATTRIBUTENAME, name);
	DDX_Text(pDX, IDC_EA_ATTRIBUTEMIN, minRange);
	DDX_Text(pDX, IDC_EA_ATTRIBUTEMAX, maxRange);
	DDX_Text(pDX, IDC_EA_ATTRIBUTEFRI, fri);
	DDX_Text(pDX, IDC_EA_ATTRIBUTEERROR, error);
}


BEGIN_MESSAGE_MAP(CAttributeDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EA_ATTRIBUTENAME, &CAttributeDialog::OnEnChangeEaAttributename)
	ON_EN_CHANGE(IDC_EA_ATTRIBUTEMIN, &CAttributeDialog::OnEnChangeEaAttributemin)
	ON_EN_CHANGE(IDC_EA_ATTRIBUTEMAX, &CAttributeDialog::OnEnChangeEaAttributemax)
	ON_EN_CHANGE(IDC_EA_ATTRIBUTEFRI, &CAttributeDialog::OnEnChangeEaAttributefri)
	ON_BN_CLICKED(IDC_EA_ATTRIBUTEVALIDATE, &CAttributeDialog::OnBnClickedEaAttributevalidate)
END_MESSAGE_MAP()


// CAttributeDialog message handlers


void CAttributeDialog::OnEnChangeEaAttributename()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CAttributeDialog::OnEnChangeEaAttributemin()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CAttributeDialog::OnEnChangeEaAttributemax()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CAttributeDialog::OnEnChangeEaAttributefri()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CAttributeDialog::OnBnClickedEaAttributevalidate()
{
	UpdateData();

	if (minRange > maxRange)
	{
		okControl.EnableWindow(FALSE);
		error = _T("The Range Max must be greater than or equal to the Range Min.");
		errorControl.SetWindowText(error);
	}
	else if (name.IsEmpty())
	{
		okControl.EnableWindow(FALSE);
		error = _T("Please enter a name for this attribute.");
		errorControl.SetWindowText(error);
	}
	else if (fri < 0 || fri > 1)
	{
		okControl.EnableWindow(FALSE);
		error = _T("FRI value must be between 0 and 1 (inclusive).");
		errorControl.SetWindowText(error);
	}
	else
	{
		okControl.EnableWindow();
	}
}
