// Grafik.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "Grafik.h"
#include "afxdialogex.h"
#include "dialogfont.h"
#include "Daten.h"
#include "draw.h"


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

static const int abstand = 5;

static const int minb = 400;
static const int minh = 200;

static dialogfont dfnt;

// Grafik-Dialogfeld

IMPLEMENT_DYNAMIC(Grafik, CDialog)

Grafik::Grafik(CWnd* pParent /*=NULL*/)
	: CDialog(Grafik::IDD, pParent)
	, vmin(1)
	, vmax(20)
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
	DDX_Text(pDX, VON, vmin);
	DDX_Text(pDX, BIS, vmax);
}


BEGIN_MESSAGE_MAP(Grafik, CDialog)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_CREATE()
	ON_WM_PAINT()

	ON_BN_CLICKED(ANZEIGEN, OnAnzeigen)
	ON_BN_CLICKED(GLPLUS, OnGlPlus)
	ON_BN_CLICKED(GLMINUS, OnGlMinus)

	ON_WM_CLOSE()
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
	//CRect temp;
	//GetWindowRect(&temp);
	drawRegion = new CRect(abstand, abstand, left_control_border - abstand, cy - abstand);
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

int Grafik::scalePoint(int p, CSize* s1, CSize* s2)
{
	return((p - s1->cx)*(s2->cy - s2->cx)) / (s1->cy - s1->cx) + s2->cx;
}


void Grafik::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	int minV, maxV;
	UpdateData(TRUE);
	//draw drawing rect
	dc.SelectObject(&stdpen.black1);
	dc.SelectObject(&stdbrush.white);
	dc.Rectangle(drawRegion);

	minV = DemoData.maximum();
	maxV = DemoData.minimum();
	//get the min and max values
	if (vmax > DemoData.get_anz_s())
		vmax = DemoData.get_anz_s();
	if (vmin < 1)
		vmin = 1;
	for (int index = 0; index < DemoData.get_anz_z(); index++)
	{
		for (int jndex = vmin-1; jndex < vmax; jndex++)
		{
			int wert = DemoData.get_wert(index, jndex);
			if (wert < minV)
			{
				minV = wert;
			}
			else
			{
				if (wert > maxV)
				{
					maxV = wert;
				}
			}
		}
	}
	
	dc.SelectObject(&stdpen.black1);
	for (int index = 0; index <= vmax - vmin; index++)
	{
		CPoint p = CPoint(scalePoint(index, &CSize(0, vmax - vmin), &CSize(drawRegion.left + abstand, drawRegion.right - abstand)), drawRegion.top);
		dc.MoveTo(p);
		p.y = drawRegion.bottom;
		dc.LineTo(p);
	}

	for (int index = 0; index < auswahl.GetCount(); index++)
	{
		if (!auswahl.GetSel(index))
			continue;
		CPen tempBrush = CPen(PS_SOLID, 5,DemoData.get_farbe(index));
		dc.SelectObject(&tempBrush);
		for (int jndex = vmin-1; jndex < vmax; jndex++)
		{
			CPoint p = CPoint(scalePoint(jndex, &CSize(vmin-1, vmax-1), &CSize(drawRegion.left + abstand, drawRegion.right - abstand)), scalePoint(DemoData.get_wert(index, jndex), &CSize(minV, maxV), &CSize(drawRegion.top + abstand, drawRegion.bottom - abstand)));
			if (jndex == vmin-1)
				dc.MoveTo(p);
			else
				dc.LineTo(p);
		}
	}




	UpdateData(FALSE);
}


void Grafik::OnClose()
{
	DestroyWindow();
	delete this;
}

void Grafik::OnAnzeigen()
{
	RedrawWindow(&drawRegion);
}

void Grafik::OnGlMinus()
{

}

void Grafik::OnGlPlus()
{

}
