// Grafik.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "Grafik.h"
#include "afxdialogex.h"
#include "dialogfont.h"
#include "Daten.h"


# define ANZEIGEN 1
# define GLGROUP 2
# define GLPLUS 3
# define GLMINUS 4
# define VBGROUP 5
# define VON 6
# define BIS 7
# define AUSWAHL 8 

static const int controlbreite = 72;
static const int offset1 = 22;
static const int hoehe1 = 20;
static const int offset2 = 66;
static const int hoehe2 = 40;
static const int offset3 = 50;
static const int hoehe3 = 20;
static const int offset4 = 110;
static const int hoehe4 = 40;
static const int offset5 = 94;
static const int hoehe5 = 20;
static const int offset6 = 114;

static const int minb = 400;
static const int minh = 200;

static dialogfont dfnt;

// Grafik-Dialogfeld

IMPLEMENT_DYNAMIC(Grafik, CDialog)

Grafik::Grafik(CWnd* pParent /*=NULL*/)
	: CDialog(Grafik::IDD, pParent)
{
	
	CRect r;
	Create(Grafik::IDD, pParent);
	r.SetRect(0, 0, minb * 3 / 2, minh * 3 / 2);
	r.OffsetRect(100, 100);
	CalcWindowRect(&r, 0);
	SetWindowText("Grafik: " + DemoData.get_name());
	MoveWindow(&r, TRUE);
	ShowWindow(SW_SHOW);
}

Grafik::~Grafik()
{
}

void Grafik::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Grafik, CDialog)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// Grafik-Meldungshandler


void Grafik::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	int left_control_border = cx - controlbreite;

	anzeigen.MoveWindow(left_control_border, cy - offset1, controlbreite, hoehe1, FALSE);
	glgroup.MoveWindow(left_control_border, cy - offset2, controlbreite, hoehe2, FALSE);
	glplus.MoveWindow(left_control_border + 2, cy - offset3, (controlbreite - 2) / 2, hoehe3, FALSE);
	glminus.MoveWindow(left_control_border + (controlbreite - 2) / 2 + 2, cy - offset3, (controlbreite - 2) / 2, hoehe3, FALSE);
	vbgroup.MoveWindow(left_control_border, cy - offset4, controlbreite, hoehe4, FALSE);
	von.MoveWindow(left_control_border + 2, cy - offset5, (controlbreite - 2) / 2, hoehe5, FALSE);
	bis.MoveWindow(left_control_border + (controlbreite - 2) / 2 + 2, cy - offset5, (controlbreite - 2) / 2, hoehe5, FALSE);
	auswahl.MoveWindow(left_control_border, 0, controlbreite, cy - offset6, FALSE);
	Invalidate();
}


void Grafik::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = minb;
	lpMMI->ptMinTrackSize.y = minh;

	CDialog::OnGetMinMaxInfo(lpMMI);
}


int Grafik::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CString txt;
	CRect r;
	int i;
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	anzeigen.Create("Anzeigen", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
		r, this, ANZEIGEN);
	anzeigen.SetFont(&dfnt.bold);
	glgroup.Create("Glättung 0", BS_GROUPBOX | WS_VISIBLE | WS_CHILD,
		r, this, GLGROUP);
	glgroup.SetFont(&dfnt.normal);
	glplus.Create("+", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
		r, this, GLPLUS);
	glplus.SetFont(&dfnt.bold);
	glminus.Create("-", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
		r, this, GLMINUS);
	glminus.SetFont(&dfnt.bold);
	glminus.EnableWindow(FALSE);

	vbgroup.Create("von bis", BS_GROUPBOX | WS_VISIBLE | WS_CHILD,
		r, this, VBGROUP);
	vbgroup.SetFont(&dfnt.normal);
	von.Create(WS_VISIBLE | WS_CHILD | WS_BORDER, r, this, VON);
	von.SetFont(&dfnt.bold);
	txt.Format("%d", 1);
	von.SetWindowText(txt);
	bis.Create(WS_VISIBLE | WS_CHILD | WS_BORDER, r, this, BIS);
	bis.SetFont(&dfnt.bold);
	txt.Format("%d", DemoData.get_anz_s());
	bis.SetWindowText(txt);
	auswahl.Create(WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL |
		LBS_EXTENDEDSEL | LBS_NOINTEGRALHEIGHT |
		LBS_DISABLENOSCROLL, r, this, AUSWAHL);
	auswahl.SetFont(&dfnt.bold);
	for (i = 0; i < DemoData.get_anz_z(); i++)
		auswahl.AddString(DemoData.get_rname(i));
	return 0;
}
