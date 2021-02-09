// NetworkDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Neural Net.h"
#include "NetworkDialog.h"
#include "afxdialogex.h"


// CNetworkDialog dialog

IMPLEMENT_DYNAMIC(CNetworkDialog, CDialogEx)

CNetworkDialog::CNetworkDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNetworkDialog::IDD, pParent)
	, name(_T(""))
	, input(0)
	, output(0)
	, hidden1(0)
	, hidden2(0)
	, hidden3(0)
	, hidden4(0)
	, learningRate(0)
	, momentum(0)
	, error(_T(""))
{

}

CNetworkDialog::~CNetworkDialog()
{
}

void CNetworkDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CN_NETNAME, nameControl);
	DDX_Control(pDX, IDC_CN_NETINPUT, inputControl);
	DDX_Control(pDX, IDC_CN_NETOUTPUT, outputControl);
	DDX_Control(pDX, IDC_CN_NETHIDDEN1, hidden1Control);
	DDX_Control(pDX, IDC_CN_NETHIDDEN2, hidden2Control);
	DDX_Control(pDX, IDC_CN_NETHIDDEN3, hidden3Control);
	DDX_Control(pDX, IDC_CN_NETHIDDEN4, hidden4Control);
	DDX_Control(pDX, IDC_CN_NETLEARNING, learningRateControl);
	DDX_Control(pDX, IDC_CN_NETMOMENTUM, momentumControl);
	DDX_Control(pDX, IDC_CN_NETVALIDATE, validateControl);
	DDX_Control(pDX, IDOK, okControl);
	DDX_Text(pDX, IDC_CN_NETNAME, name);
	DDX_Text(pDX, IDC_CN_NETINPUT, input);
	DDX_Text(pDX, IDC_CN_NETOUTPUT, output);
	DDX_Text(pDX, IDC_CN_NETHIDDEN1, hidden1);
	DDX_Text(pDX, IDC_CN_NETHIDDEN2, hidden2);
	DDX_Text(pDX, IDC_CN_NETHIDDEN3, hidden3);
	DDX_Text(pDX, IDC_CN_NETHIDDEN4, hidden4);
	DDX_Text(pDX, IDC_CN_NETLEARNING, learningRate);
	DDX_Text(pDX, IDC_CN_NETMOMENTUM, momentum);
	DDX_Text(pDX, IDC_CN_NETERROR, error);
	DDX_Control(pDX, IDC_CN_NETERROR, errorControl);
}


BEGIN_MESSAGE_MAP(CNetworkDialog, CDialogEx)
	ON_EN_CHANGE(IDC_CN_NETNAME, &CNetworkDialog::OnEnChangeCnNetname)
	ON_EN_CHANGE(IDC_CN_NETINPUT, &CNetworkDialog::OnEnChangeCnNetinput)
	ON_EN_CHANGE(IDC_CN_NETOUTPUT, &CNetworkDialog::OnEnChangeCnNetoutput)
	ON_EN_CHANGE(IDC_CN_NETHIDDEN1, &CNetworkDialog::OnEnChangeCnNethidden1)
	ON_EN_CHANGE(IDC_CN_NETHIDDEN2, &CNetworkDialog::OnEnChangeCnNethidden2)
	ON_EN_CHANGE(IDC_CN_NETHIDDEN3, &CNetworkDialog::OnEnChangeCnNethidden3)
	ON_EN_CHANGE(IDC_CN_NETHIDDEN4, &CNetworkDialog::OnEnChangeCnNethidden4)
	ON_EN_CHANGE(IDC_CN_NETLEARNING, &CNetworkDialog::OnEnChangeCnNetlearning)
	ON_EN_CHANGE(IDC_CN_NETMOMENTUM, &CNetworkDialog::OnEnChangeCnNetmomentum)
	ON_BN_CLICKED(IDC_CN_NETVALIDATE, &CNetworkDialog::OnBnClickedCnNetvalidate)
END_MESSAGE_MAP()


// CNetworkDialog message handlers


void CNetworkDialog::OnEnChangeCnNetname()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CNetworkDialog::OnEnChangeCnNetinput()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CNetworkDialog::OnEnChangeCnNetoutput()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CNetworkDialog::OnEnChangeCnNethidden1()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CNetworkDialog::OnEnChangeCnNethidden2()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CNetworkDialog::OnEnChangeCnNethidden3()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CNetworkDialog::OnEnChangeCnNethidden4()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CNetworkDialog::OnEnChangeCnNetlearning()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CNetworkDialog::OnEnChangeCnNetmomentum()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CNetworkDialog::OnBnClickedCnNetvalidate()
{
	UpdateData();

	if (name.IsEmpty())
	{
		okControl.EnableWindow(FALSE);
		error = _T("Please enter a Name for this network.");
		errorControl.SetWindowText(error);
	}
	else if (input <= 0)
	{
		okControl.EnableWindow(FALSE);
		error = _T("Input Nodes must be greater than or equal to 1.");
		errorControl.SetWindowText(error);
	}
	else if (output <= 0)
	{
		okControl.EnableWindow(FALSE);
		error = _T("Output Nodes must be greater than or equal to 1.");
		errorControl.SetWindowText(error);
	}
	else if (hidden1 == 0 && (hidden2 > 0 || hidden3 > 0 || hidden4 > 0))
	{
		okControl.EnableWindow(FALSE);
		error = _T("Hidden Nodes 1: must be greater than 0 to enable Hidden Nodes 2 - 4.");
		errorControl.SetWindowText(error);
	}
	else if (hidden2 == 0 && (hidden3 > 0 || hidden4 > 0))
	{
		okControl.EnableWindow(FALSE);
		error = _T("Hidden Nodes 2: must be greater than 0 to enable Hidden Nodes 3 - 4.");
		errorControl.SetWindowText(error);
	}
	else if (hidden3 == 0 && hidden4 > 0)
	{
		okControl.EnableWindow(FALSE);
		error = _T("Hidden Nodes 3: must be greater than 0 to enable Hidden Nodes 4.");
		errorControl.SetWindowText(error);
	}
	else if (learningRate < 0)
	{
		okControl.EnableWindow(FALSE);
		error = _T("Learning Rate must be greater than or equal to 0.");
		errorControl.SetWindowText(error);
	}
	else if (momentum < 0)
	{
		okControl.EnableWindow(FALSE);
		error = _T("Momentum must be greater than or equal to 0.");
		errorControl.SetWindowText(error);
	}
	else
	{
		error = _T("");
		errorControl.SetWindowText(error);
		okControl.EnableWindow();
	}
}
