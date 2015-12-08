// EinReihe.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "EinReihe.h"
#include "afxdialogex.h"
#include "Daten.h"
#include "draw.h"


// EinReihe-Dialogfeld

IMPLEMENT_DYNAMIC(EinReihe, CDialog)

EinReihe::EinReihe(CWnd* pParent /*= NULL*/, int rno/* = 1*/)
	: CDialog(EinReihe::IDD, pParent)
	, reihe(0)
	, name(_T(""))
{
	reihe = rno+1;
	//rowChanged(reihe);
}

EinReihe::~EinReihe()
{
}

void EinReihe::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_REIHE, reihe);
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Control(pDX, IDC_MINUS, minus);
	DDX_Control(pDX, IDC_PLUS, plus);
}


BEGIN_MESSAGE_MAP(EinReihe, CDialog)
	ON_BN_CLICKED(IDC_MINUS, &EinReihe::OnBnClickedMinus)
	ON_BN_CLICKED(IDC_PLUS, &EinReihe::OnBnClickedPlus)
	ON_BN_CLICKED(IDC_SPEICHERN, &EinReihe::OnBnClickedSpeichern)
	ON_BN_CLICKED(IDC_ANDERN, &EinReihe::OnBnClickedAndern)
END_MESSAGE_MAP()


// EinReihe-Meldungshandler


BOOL EinReihe::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateData(TRUE);
	//reihe = 1;
	rowChanged(reihe);

	return TRUE;  // return TRUE unless you set the focus to a control
	// AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void EinReihe::rowChanged(int pos)
{
	if (pos < 1)
		pos = 1;
	if (pos > DemoData.get_anz_z())
		pos = DemoData.get_anz_z();
	name = DemoData.get_rname(pos - 1);
	if (pos == 1)
	{
		minus.EnableWindow(FALSE);
	}
	else
	{
		minus.EnableWindow(TRUE);
	}
	if (pos == DemoData.get_anz_z())
	{
		plus.EnableWindow(FALSE);
	}
	else
	{
		plus.EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}


void EinReihe::OnBnClickedMinus()
{

	reihe = reihe - 1;
	rowChanged(reihe);
}


void EinReihe::OnBnClickedPlus()
{
	reihe = reihe + 1;
	rowChanged(reihe);

}


void EinReihe::OnBnClickedSpeichern()
{
	UpdateData(TRUE);
	if (name != DemoData.get_rname(reihe - 1))
	{
		DemoData.set_rname(reihe - 1, name);
		GetParentFrame()->GetActiveDocument()->SetModifiedFlag();
		update_reihe(reihe - 1, true, false);
	}


	UpdateData(FALSE);
}


void EinReihe::OnBnClickedAndern()
{
	CColorDialog cd(DemoData.get_farbe(reihe - 1));
	if (cd.DoModal() == IDOK)
	{
		DemoData.set_farbe(reihe - 1, cd.GetColor());
		GetParentFrame()->GetActiveDocument()->SetModifiedFlag();

		stdbrush.set(reihe-1);
		stdpen.set(reihe-1);
	}
}
