// Tabelle.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "Tabelle.h"
#include "afxdialogex.h"
#include "Daten.h"
#include "draw.h"
#include "AusReiheEin.h"


static const int feldhoehe = 16;
static const int feldbreite = 40;
static const int namenbreite = 70;
static const int abstand = 4;
static const int maxcolumns = 10;
static const int scrollbarhohe = 16;

#define MY_COMMAND_BASE 32782

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
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
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
		CRect dump;
		if (IntersectRect(&dump, &udp, &field))
		{
			dc.SelectObject(&stdbrush.white);
			dc.Rectangle(&field);
			CString s;
			s.Format("%d", index + 1);
			dc.DrawText(s, field, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			field.OffsetRect(0, abstand+feldhoehe);
			for (int jndex = 0; jndex < DemoData.get_anz_s(); jndex++)
			{
				dc.SelectObject(&stdbrush.white);
				CBrush b(RGB(20, 20, 255));
				if (selectedField == CPoint(index, jndex))
				{
					dc.SelectObject(&b);
				}
				dc.Rectangle(field);
				s.Format("%d", DemoData.get_wert(jndex, index));
				if (DemoData.get_wert(jndex, index) < 0)
				{
					dc.SetTextColor(RGB(255, 20, 20));
				}
				else
				{
					dc.SetTextColor(RGB(0, 0, 0));
				}
				if (selectedField == CPoint(index, jndex))
				{
					dc.SetTextColor(RGB(255, 255, 255));
				}
				dc.DrawText(s, field, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				dc.SetTextColor(RGB(0, 0, 0));
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


void Tabelle::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//Calculate the field that was clicked
	CPoint pRel = point - scrollrect.TopLeft();
	pRel.x += actpos;
	pRel.y -= feldhoehe + abstand;
	int x, y;
	y = pRel.y/(feldhoehe-1);
	x = pRel.x/(feldbreite-1);

	AusReiheEin ein;
	ein.wert = DemoData.get_wert(y, x);
	if (ein.DoModal() == IDOK)
	{
		DemoData.set_wert(y, x, ein.wert);
		GetParentFrame()->GetActiveDocument()->SetModifiedFlag();
		RedrawWindow();
	}

	CDialog::OnLButtonDblClk(nFlags, point);
}


void Tabelle::OnRButtonDown(UINT nFlags, CPoint point)
{
	CPoint pRel = point - scrollrect.TopLeft();
	pRel.x += actpos;
	pRel.y -= feldhoehe + abstand;
	selectedField.x = pRel.x / (feldbreite - 1);
	selectedField.y = pRel.y / (feldhoehe - 1);
	CMenu menu;
	menu.CreatePopupMenu();
	for (int index = 0; index < 7; index++)
	{
		//if (index == 3) continue;
		CString s;
		s.Format("%d", DemoData.get_wert(selectedField.y,selectedField.x)-3+index);
		menu.InsertMenu(index, MF_BYPOSITION | MF_STRING, MY_COMMAND_BASE+index, s);
		update_wert(selectedField.y, selectedField.x);
	}
	RedrawWindow();
	CPoint pos;
	GetCursorPos(&pos);
	menu.TrackPopupMenu(TPM_RIGHTALIGN | TPM_LEFTBUTTON, pos.x, pos.y, this);
	CDialog::OnRButtonDown(nFlags, point);
}


BOOL Tabelle::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if ((wParam >= MY_COMMAND_BASE) && (wParam < MY_COMMAND_BASE + 7))
	{
		//GetWindowPl
		DemoData.set_wert(selectedField.y, selectedField.x, DemoData.get_wert(selectedField.y, selectedField.x) + (wParam - MY_COMMAND_BASE- 3));
		selectedField.SetPoint(-1, -1);
		RedrawWindow();
		GetParentFrame()->GetActiveDocument()->SetModifiedFlag();
	}

	return CDialog::OnCommand(wParam, lParam);
}


BOOL Tabelle::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{

	switch (message)
	{
	case UPDATE_NAME:
		SetWindowText(DemoData.get_name());
		break;
	case UPDATE_REIHE:
		if (lParam&FLAG_NAME)
			RedrawWindow();
		break;
	case UPDATE_WERT:
		RedrawWindow();
		break;
	case UPDATE_ALL:
		if ((lParam&FLAG_NAME) || (lParam&FLAG_WERT))
			RedrawWindow();
		break;
	default:
		break;
	}
	return CDialog::OnWndMsg(message, wParam, lParam, pResult);
}
