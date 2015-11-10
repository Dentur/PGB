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
	CRect r;

	Create(Tabelle::IDD, pParent);
	as = DemoData.get_anz_s();
	az = DemoData.get_anz_z();

	columns = as > maxcolumns ? maxcolumns : as;
	hoehe = 3 * abstand + (az + 1)*feldhoehe;
	breite = 3 * abstand + namenbreite + columns*feldbreite;
	if (columns < as)
		hoehe += abstand + scrollbarhohe;
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
