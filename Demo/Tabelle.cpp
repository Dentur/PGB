// Tabelle.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "Tabelle.h"
#include "afxdialogex.h"
#include "Daten.h"


static const int feldhoehe = 16;
static const int feldbreite = 40;
static const int namenbreite = 70;
static const int abstand = 4;
static const int maxcolumns = 10;
static const int scrollbarhohe = 16;


// Tabelle-Dialogfeld

IMPLEMENT_DYNAMIC(Tabelle, CDialog)

Tabelle::Tabelle(CWnd* pParent /*=NULL*/)
	: CDialog(Tabelle::IDD, pParent)
{
	int hoehe, breite;
	int as, az;
	CRect r, sbr;


	Create(Tabelle::IDD, pParent);
	as = DemoData.get_anz_s();
	az = DemoData.get_anz_z();

	//columns = as > maxcolumns ? maxcolumns : as;
	if (as > maxcolumns)
		columns = maxcolumns;
	else
		columns = as;
	hoehe = 3 * abstand + (az + 1)*feldhoehe;
	breite = 3 * abstand + namenbreite + columns*feldbreite;

	scrollrect.SetRect(2 * abstand + namenbreite + 1, abstand+1, breite - abstand-1, hoehe - abstand-1);
	maxpos = (as - maxcolumns)*feldbreite;
	actpos = 0;

	if (columns < as)
	{
		hoehe += abstand + scrollbarhohe;
		sbr.SetRect(2 * abstand + namenbreite,
			hoehe - abstand - scrollbarhohe,
			breite - abstand, hoehe - abstand);
		sbar.Create(WS_CHILD | WS_VISIBLE | SBS_HORZ, sbr, this, 1);
		sbar.SetScrollRange(0, maxpos);
		sbar.SetScrollPos(actpos);
	}
	r.SetRect(0, 0, breite, hoehe);
	r.OffsetRect(100, 100);
	CalcWindowRect(&r, 0);
	SetWindowText("Tabele: " + DemoData.get_name());
	MoveWindow(&r, TRUE);
	ShowWindow(SW_SHOW);

}

Tabelle::~Tabelle()
{
}

void Tabelle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Tabelle, CDialog)
END_MESSAGE_MAP()


// Tabelle-Meldungshandler
