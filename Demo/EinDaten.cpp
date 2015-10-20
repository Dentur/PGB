// EinDaten.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "EinDaten.h"
#include "afxdialogex.h"
#include "Daten.h"


// EinDaten-Dialogfeld

IMPLEMENT_DYNAMIC(EinDaten, CDialog)

EinDaten::EinDaten(CWnd* pParent /*=NULL*/)
	: CDialog(EinDaten::IDD, pParent)
	, auswahl(0)
	, nummrt(0)
	, wert(0)
{

}

EinDaten::~EinDaten()
{
}

void EinDaten::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_AUSWAHL, auswahl);
	DDX_Control(pDX, IDC_AUSWAHL, combobox);
	DDX_Text(pDX, IDC_NUMBER, nummrt);
	DDX_Control(pDX, IDC_SCROLL, scrollbar);
	DDX_Text(pDX, IDC_WERT, wert);
}


BEGIN_MESSAGE_MAP(EinDaten, CDialog)
END_MESSAGE_MAP()


// EinDaten-Meldungshandler


BOOL EinDaten::OnInitDialog()
{
	CDialog::OnInitDialog();

	for (int index = 0; index < DemoData.get_anz_z(); index++)
	{
		combobox.InsertString(index, DemoData.get_rname(index));
	}
	auswahl = 0;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}
