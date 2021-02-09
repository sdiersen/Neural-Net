// FoldDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Neural Net.h"
#include "FoldDialog.h"
#include "afxdialogex.h"


// CFoldDialog dialog

IMPLEMENT_DYNAMIC(CFoldDialog, CDialogEx)

CFoldDialog::CFoldDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFoldDialog::IDD, pParent)
	, folds(0)
	, epochs(0)
	, criteria(0)
	, runs(0)
	, startingLayer(0)
	, endingLayer(0)
	, starting1(0)
	, starting2(0)
	, starting3(0)
	, starting4(0)
	, ending1(0)
	, ending2(0)
	, ending3(0)
	, ending4(0)
	, error(_T(""))
{

}

CFoldDialog::~CFoldDialog()
{
}

void CFoldDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FOLDFOLDS, foldControl);
	DDX_Control(pDX, IDC_FOLDEPOCHS, epochsControl);
	DDX_Control(pDX, IDC_FOLDSTOPPING, criteriaControl);
	DDX_Control(pDX, IDC_FOLDRUNS, runsControl);
	DDX_Control(pDX, IDC_FOLDSTARTINGLAYER, startingLayerControl);
	DDX_Control(pDX, IDC_FOLDENDINGLAYER, endingLayerControl);
	DDX_Control(pDX, IDC_FOLDSTARTING1, starting1Control);
	DDX_Control(pDX, IDC_FOLDSTARTING2, starting2Control);
	DDX_Control(pDX, IDC_FOLDSTARTING3, starting3Control);
	DDX_Control(pDX, IDC_FOLDSTARTING4, starting4Control);
	DDX_Control(pDX, IDC_FOLDENDING1, ending1Control);
	DDX_Control(pDX, IDC_FOLDENDING2, ending2Control);
	DDX_Control(pDX, IDC_FOLDENDING3, ending3Control);
	DDX_Control(pDX, IDC_FOLDENDING4, ending4Control);
	DDX_Control(pDX, IDC_FOLDERROR, errorControl);
	DDX_Control(pDX, IDC_FOLDVALIDATE, validateControl);
	DDX_Control(pDX, IDOK, okControl);
	DDX_Text(pDX, IDC_FOLDFOLDS, folds);
	DDX_Text(pDX, IDC_FOLDEPOCHS, epochs);
	DDX_Text(pDX, IDC_FOLDSTOPPING, criteria);
	DDX_Text(pDX, IDC_FOLDRUNS, runs);
	DDX_Text(pDX, IDC_FOLDSTARTINGLAYER, startingLayer);
	DDX_Text(pDX, IDC_FOLDENDINGLAYER, endingLayer);
	DDX_Text(pDX, IDC_FOLDSTARTING1, starting1);
	DDX_Text(pDX, IDC_FOLDSTARTING2, starting2);
	DDX_Text(pDX, IDC_FOLDSTARTING3, starting3);
	DDX_Text(pDX, IDC_FOLDSTARTING4, starting4);
	DDX_Text(pDX, IDC_FOLDENDING1, ending1);
	DDX_Text(pDX, IDC_FOLDENDING2, ending2);
	DDX_Text(pDX, IDC_FOLDENDING3, ending3);
	DDX_Text(pDX, IDC_FOLDENDING4, ending4);
	DDX_Text(pDX, IDC_FOLDERROR, error);
}


BEGIN_MESSAGE_MAP(CFoldDialog, CDialogEx)
	ON_EN_CHANGE(IDC_FOLDFOLDS, &CFoldDialog::OnEnChangeFoldfolds)
	ON_EN_CHANGE(IDC_FOLDEPOCHS, &CFoldDialog::OnEnChangeFoldepochs)
	ON_EN_CHANGE(IDC_FOLDSTOPPING, &CFoldDialog::OnEnChangeFoldstopping)
	ON_EN_CHANGE(IDC_FOLDRUNS, &CFoldDialog::OnEnChangeFoldruns)
	ON_EN_CHANGE(IDC_FOLDSTARTINGLAYER, &CFoldDialog::OnEnChangeFoldstartinglayer)
	ON_EN_CHANGE(IDC_FOLDENDINGLAYER, &CFoldDialog::OnEnChangeFoldendinglayer)
	ON_EN_CHANGE(IDC_FOLDSTARTING1, &CFoldDialog::OnEnChangeFoldstarting1)
	ON_EN_CHANGE(IDC_FOLDSTARTING2, &CFoldDialog::OnEnChangeFoldstarting2)
	ON_EN_CHANGE(IDC_FOLDSTARTING3, &CFoldDialog::OnEnChangeFoldstarting3)
	ON_EN_CHANGE(IDC_FOLDSTARTING4, &CFoldDialog::OnEnChangeFoldstarting4)
	ON_EN_CHANGE(IDC_FOLDENDING1, &CFoldDialog::OnEnChangeFoldending1)
	ON_EN_CHANGE(IDC_FOLDENDING2, &CFoldDialog::OnEnChangeFoldending2)
	ON_EN_CHANGE(IDC_FOLDENDING3, &CFoldDialog::OnEnChangeFoldending3)
	ON_EN_CHANGE(IDC_FOLDENDING4, &CFoldDialog::OnEnChangeFoldending4)
	ON_BN_CLICKED(IDC_FOLDVALIDATE, &CFoldDialog::OnBnClickedFoldvalidate)
END_MESSAGE_MAP()


// CFoldDialog message handlers


void CFoldDialog::OnEnChangeFoldfolds()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CFoldDialog::OnEnChangeFoldepochs()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CFoldDialog::OnEnChangeFoldstopping()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CFoldDialog::OnEnChangeFoldruns()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CFoldDialog::OnEnChangeFoldstartinglayer()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CFoldDialog::OnEnChangeFoldendinglayer()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CFoldDialog::OnEnChangeFoldstarting1()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CFoldDialog::OnEnChangeFoldstarting2()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CFoldDialog::OnEnChangeFoldstarting3()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CFoldDialog::OnEnChangeFoldstarting4()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CFoldDialog::OnEnChangeFoldending1()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CFoldDialog::OnEnChangeFoldending2()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CFoldDialog::OnEnChangeFoldending3()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CFoldDialog::OnEnChangeFoldending4()
{
	UpdateData();
	okControl.EnableWindow(FALSE);
}


void CFoldDialog::OnBnClickedFoldvalidate()
{
	UpdateData();

	if (folds < 2)
	{
		okControl.EnableWindow(FALSE);
		error = _T("There must be at least 2 folds when using k-fold cross-validation.");
		errorControl.SetWindowText(error);
	}
	else if (epochs < 1)
	{
		okControl.EnableWindow(FALSE);
		error = _T("There must be at least 1 epoch when using k-fold cross-validation.");
		errorControl.SetWindowText(error);
	}
	else if (criteria <= 0.0)
	{
		okControl.EnableWindow(FALSE);
		error = _T("Stopping Criteria must be greater than 0.");
		errorControl.SetWindowText(error);
	}
	else if (runs < 1)
	{
		okControl.EnableWindow(FALSE);
		error = _T("There must be at least 1 consecutive run.");
		errorControl.SetWindowText(error);
	}
	else if (startingLayer < 0)
	{
		okControl.EnableWindow(FALSE);
		error = _T("Starting layer must be positive.");
		errorControl.SetWindowText(error);
	}
	else if (startingLayer > endingLayer)
	{
		okControl.EnableWindow(FALSE);
		error = _T("Ending Hidden Layer must be greater than or equal to Starting Hidden Layer");
		errorControl.SetWindowText(error);
	}
	else if (endingLayer > 4)
	{
		okControl.EnableWindow(FALSE);
		error = _T("Ending Hidden Layer can have a maximum value of 4.");
		errorControl.SetWindowText(error);
	}
	else if (starting1 > ending1)
	{
		okControl.EnableWindow(FALSE);
		error = _T("Ending Hidden Nodes 1 must be greater than or equal to Starting Hidden Nodes 1.");
		errorControl.SetWindowText(error);
	}
	else if (starting2 > ending2)
	{
		okControl.EnableWindow(FALSE);
		error = _T("Ending Hidden Nodes 2 must be greater than or equal to Starting Hidden Nodes 2.");
		errorControl.SetWindowText(error);
	}
	else if (starting3 > ending3)
	{
		okControl.EnableWindow(FALSE);
		error = _T("Ending Hidden Nodes 3 must be greater than or equal to Starting Hidden Nodes 3.");
		errorControl.SetWindowText(error);
	}
	else if (starting4 > ending4)
	{
		okControl.EnableWindow(FALSE);
		error = _T("Ending Hidden Nodes 4 must be greater than or equal to Starting Hidden Nodes 4.");
		errorControl.SetWindowText(error);
	}
	else
	{
		okControl.EnableWindow();
	}
}
