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
	, nummer(0)
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
	DDX_Text(pDX, IDC_NUMBER, nummer);
	DDX_Control(pDX, IDC_SCROLL, scrollbar);
	DDX_Text(pDX, IDC_WERT, wert);
}


BEGIN_MESSAGE_MAP(EinDaten, CDialog)
	ON_CBN_SELCHANGE(IDC_AUSWAHL, &EinDaten::OnCbnSelchangeAuswahl)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_SPEICHERN, &EinDaten::OnBnClickedSpeichern)
	ON_BN_CLICKED(IDC_LOESCHEN, &EinDaten::OnBnClickedLoeschen)
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

	scrollbar.SetScrollRange(1, DemoData.get_anz_s());
	scroll_to(1);

	UpdateData(FALSE);

	GotoDlgCtrl(GetDlgItem(IDC_WERT));

	return TRUE;  // return TRUE unless you set the focus to a control
	// AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}


void EinDaten::scroll_to(int pos)
{
	if (pos < 1)
	{
		pos = 1;
	}
	if (pos>DemoData.get_anz_s())
	{
		pos = DemoData.get_anz_s();
	}

	nummer = pos;

	scrollbar.SetScrollPos( nummer);

	wert = DemoData.get_wert(auswahl, nummer - 1);

	UpdateData(FALSE);
}


void EinDaten::OnCbnSelchangeAuswahl()
{
	UpdateData(TRUE);
	wert = DemoData.get_wert(auswahl, nummer - 1);
	UpdateData(FALSE);
	GotoDlgCtrl(GetDlgItem(IDC_WERT));
}


void EinDaten::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	UpdateData(TRUE);
	if (pScrollBar == &scrollbar)
	{
		switch (nSBCode)
		{
		case SB_LEFT:
			scroll_to(1);
			break;
		case SB_RIGHT:
			scroll_to(DemoData.get_anz_s());
			break;
		case SB_LINELEFT:
			scroll_to(nummer-1);
			break;
		case SB_LINERIGHT:
			scroll_to(nummer+1);
			break;
		case SB_PAGELEFT:
			scroll_to(nummer-5);
			break;
		case SB_PAGERIGHT:
			scroll_to(nummer + 5);
			break;
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			scroll_to(nPos);
			break;
		case SB_ENDSCROLL:
			break;
		}
	}

	GotoDlgCtrl(GetDlgItem(IDC_WERT));
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void EinDaten::OnBnClickedSpeichern()
{
	UpdateData(TRUE);
	if (DemoData.get_wert(auswahl, nummer - 1) != wert)
	{
		DemoData.set_wert(auswahl, nummer - 1, wert);
		GetParentFrame()->GetActiveDocument()->SetModifiedFlag();
		update_wert(auswahl, nummer - 1);
	}
	scroll_to(nummer + 1);
	GotoDlgCtrl(GetDlgItem(IDC_WERT));
	UpdateData(FALSE);
}


void EinDaten::OnBnClickedLoeschen()
{
	UpdateData(TRUE);
	if (DemoData.get_wert(auswahl, nummer - 1) != 0)
	{
		DemoData.set_wert(auswahl, nummer - 1, 0);
		GetParentFrame()->GetActiveDocument()->SetModifiedFlag();
	}
	scroll_to(nummer + 1);
	GotoDlgCtrl(GetDlgItem(IDC_WERT));
	UpdateData(FALSE);
}
