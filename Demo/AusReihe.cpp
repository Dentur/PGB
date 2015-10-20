// AusReihe.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "AusReihe.h"
#include "afxdialogex.h"
#include "Daten.h"


// AusReihe-Dialogfeld

IMPLEMENT_DYNAMIC(AusReihe, CDialog)

AusReihe::AusReihe(CWnd* pParent /*=NULL*/)
	: CDialog(AusReihe::IDD, pParent)
	, m_darstellung(0)
	, m_selection(0)
	, m_xraster(FALSE)
	, m_yraster(FALSE)
{
	int i;

	Create(AusReihe::IDD, pParent);

	for (i = 0; i < DemoData.get_anz_z(); i++)
		m_reihe.InsertString(i, DemoData.get_rname(i));
	m_selection = 0;
	m_xraster = TRUE;
	m_yraster = TRUE;
	m_darstellung = 0;

	UpdateData(FALSE);
	SetWindowText("Datenreihe: " + DemoData.get_name());

	ShowWindow(SW_SHOW);
}

AusReihe::~AusReihe()
{
}

void AusReihe::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_LINIEN, m_darstellung);
	DDX_CBIndex(pDX, IDC_REIHE, m_selection);
	DDX_Control(pDX, IDC_REIHE, m_reihe);
	DDX_Check(pDX, IDC_XRASTER, m_xraster);
	DDX_Check(pDX, IDC_YRASTER, m_yraster);
}


BEGIN_MESSAGE_MAP(AusReihe, CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// AusReihe-Meldungshandler


void AusReihe::OnClose()
{
	DestroyWindow();
	delete this;

	CDialog::OnClose();
}
