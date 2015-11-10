// Tabelle.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "Tabelle.h"
#include "afxdialogex.h"
#include "Daten.h"
#include "draw.h"


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
	ON_WM_PAINT()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// Tabelle-Meldungshandler


void Tabelle::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	int a;

	//Draw row names
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(&stdpen.black1);
	dc.SelectObject(&stdbrush.white);
	CRect tmp;
	for (int index = 0; index < DemoData.get_anz_z(); index++)
	{
		tmp.SetRect(0, 0, namenbreite, feldhoehe);
		tmp.OffsetRect(abstand, 2 * abstand + (index + 1)*feldhoehe-index);
		

		dc.Rectangle(tmp);
		dc.DrawText(DemoData.get_rname(index), tmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	dc.IntersectClipRect(scrollrect);
	CRect udp;
	dc.GetClipBox(&udp);
	for (int index = 0; index < DemoData.get_anz_z(); index++)
	{
		CRect field;
		field.SetRect(0, 0, feldbreite, feldhoehe);
		field.OffsetRect(feldbreite*index+2*abstand+namenbreite-actpos-index,abstand);
		//if (udp.IntersectRect(&field, &udp))
		{
			dc.Rectangle(&field);
			CString s;
			s.Format("%d", index + 1);
			dc.DrawText(s, field, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			field.OffsetRect(0, abstand+feldhoehe);
			for (int jndex = 0; jndex < DemoData.get_anz_s(); jndex++)
			{
				dc.Rectangle(field);
				s.Format("%d", DemoData.get_wert(index, jndex));
				dc.DrawText(s, field, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				field.OffsetRect(0, feldhoehe - 1);
			}
		}
	}


	dc.IntersectClipRect(NULL);

	/*dc.FrameRect(scrollrect, &stdbrush.black);

	for (a = 0; a <= scrollrect.Width(); a += 8)
	{
		dc.MoveTo(scrollrect.left+a, scrollrect.top);
		dc.LineTo(scrollrect.right - a, scrollrect.bottom);
	}
	for (a = 0; a <= scrollrect.Height(); a += 8)
	{
		dc.MoveTo(scrollrect.left, scrollrect.top + a);
		dc.LineTo(scrollrect.right, scrollrect.bottom-a);
	}*/
}


void Tabelle::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int newpos = actpos;
	if (pScrollBar == &sbar)
	{
		switch (nSBCode)
		{
		case SB_LEFT:
			newpos = 0;
			break;
		case SB_ENDSCROLL:
			break;
		case SB_LINELEFT:
			newpos -= 8;
			break;
		case SB_LINERIGHT:
			newpos += 8;
			break;
		case SB_PAGELEFT:
			newpos -= feldbreite;
			break;
		case SB_PAGERIGHT:
			newpos += feldbreite;
			break;
		case SB_RIGHT:
			newpos = maxpos;
			break;
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			newpos = nPos;
			break;
		}

		if (newpos < 0)
			newpos = 0;
		if (newpos > maxpos)
			newpos = maxpos;
		if (newpos != actpos)
		{
			sbar.SetScrollPos(newpos);
			ScrollWindow(actpos - newpos, 0, scrollrect, scrollrect);
			actpos = newpos;
			UpdateWindow();
		}
	}


	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
