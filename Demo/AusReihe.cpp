// AusReihe.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "AusReihe.h"
#include "afxdialogex.h"
#include "Daten.h"
#include "draw.h"

#define paddingLeft 20
#define paddingRight 20
#define paddingWidth (paddingLeft + paddingRight)
#define paddingTop 20
#define paddingBottom 20
#define paddingHeight (paddingTop + paddingBottom)
#define anzHorizontalLines 10



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
	GetDlgItem(IDC_DIAGRAMM)->GetWindowRect(&rahmen);
	ScreenToClient(&rahmen);
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
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_LINIEN, &AusReihe::OnBnClickedLinien)
	ON_BN_CLICKED(IDC_SAEULEN, &AusReihe::OnBnClickedSaeulen)
	ON_CBN_SELCHANGE(IDC_REIHE, &AusReihe::OnCbnSelchangeReihe)
	ON_BN_CLICKED(IDC_XRASTER, &AusReihe::OnBnClickedXraster)
	ON_BN_CLICKED(IDC_YRASTER, &AusReihe::OnBnClickedYraster)
END_MESSAGE_MAP()


// AusReihe-Meldungshandler


void AusReihe::OnClose()
{
	DestroyWindow();
	delete this;

	//CDialog::OnClose();
}


void AusReihe::OnPaint()
{
	UpdateData(TRUE);
	CPaintDC dc(this); // device context for painting
	dc.FillRect(rahmen, &stdbrush.white);
	CPen *oldPen = dc.SelectObject(&stdpen.gray1);


	if (m_xraster)
	{
		for (int index = 0; index < DemoData.get_anz_s(); index++)
		{
			int x = paddingLeft + rahmen.left + (index*(rahmen.Width() - paddingWidth)) / (DemoData.get_anz_s() - 1);
			dc.MoveTo(x, rahmen.top + paddingTop);
			dc.LineTo(x, rahmen.bottom - paddingBottom);
		}
	}
	if (m_yraster)
	{
		for (int index = 0; index < anzHorizontalLines; index++)
		{
			int y = paddingTop + rahmen.top + (index*(rahmen.Height() - paddingHeight)) / (anzHorizontalLines-1);
			/*if (y > rahmen.bottom - paddingBottom)
				y = rahmen.bottom - paddingBottom;*/
			dc.MoveTo(rahmen.left + paddingLeft, y);
			dc.LineTo(rahmen.right - paddingRight, y);
		}
	}

	CSize dataRangeHeight, dataRangeWidth, windowRangeHeight, windowRangeWidth;
	dataRangeHeight = CSize(DemoData.minimum(m_selection), DemoData.maximum(m_selection));
	dataRangeWidth = CSize(0, DemoData.get_anz_s());
	//windowRangeHeight = CSize(rahmen.top + 1*paddingTop, rahmen.bottom - 1*paddingBottom);
	windowRangeHeight = CSize(paddingTop, rahmen.Height()-paddingHeight);
	windowRangeWidth = CSize(rahmen.left + paddingLeft, rahmen.right - 0*paddingRight);
	//draw null line
	dc.SelectObject(&stdpen.black2);
	if ((DemoData.minimum(m_selection) < 0) && (DemoData.maximum(m_selection) > 0))
	{
		int nullLine = rahmen.bottom-scalePoint(0, &dataRangeHeight, &windowRangeHeight);
		dc.MoveTo(rahmen.left + paddingLeft, nullLine);
		dc.LineTo(rahmen.right - paddingRight, nullLine);
	}

	if (m_darstellung == 0)
	{
		CPoint oldP, newP;
		oldP = CPoint(
			scalePoint(0, &dataRangeWidth, &windowRangeWidth),
			rahmen.bottom - scalePoint(DemoData.get_wert(m_selection, 0), &dataRangeHeight, &windowRangeHeight)
			);
		dc.MoveTo(oldP);
		for (int index = 0; index < DemoData.get_anz_s(); index++)
		{
			dc.SelectObject(&stdpen.black5);
			newP = CPoint(
				scalePoint(index, &dataRangeWidth, &windowRangeWidth),
				rahmen.bottom -scalePoint(DemoData.get_wert(m_selection, index), &dataRangeHeight, &windowRangeHeight)
				);
			dc.LineTo(newP);
			dc.SelectObject(&stdpen.gray3);
			dc.MoveTo(oldP);
			dc.LineTo(newP);
			oldP = newP;
		}
		//draw the points

		dc.SelectObject(&stdbrush.gray);
		dc.SelectObject(&stdpen.black1);
		for (int index = 0; index < DemoData.get_anz_s(); index++)
		{
			CPoint loc = CPoint(
				scalePoint(index, &dataRangeWidth, &windowRangeWidth),
				rahmen.bottom - scalePoint(DemoData.get_wert(m_selection, index), &dataRangeHeight, &windowRangeHeight)
				);
			dc.Ellipse(loc.x - 5, loc.y - 5, loc.x + 5, loc.y + 5);
		}
	}
	else
	{
		dc.SelectObject(&stdbrush.gray);
		dc.SelectObject(&stdpen.black1);
		for (int index = 0; index < DemoData.get_anz_s(); index++)
		{
			int loc = scalePoint(index, &dataRangeWidth, &windowRangeWidth);
			//dc.Rectangle(loc - 5, rahmen.bottom - scalePoint(0, &dataRangeHeight, &windowRangeHeight), loc + 5, rahmen.bottom - paddingBottom + nullLine - scalePoint(DemoData.get_wert(m_selection, index), &CSize(DemoData.minimum(m_selection), DemoData.maximum(m_selection)), &CSize(0, rahmen.Height() - paddingHeight)));
		
		}
	}
	dc.SelectObject(oldPen);
}


void AusReihe::OnBnClickedLinien()
{
	InvalidateRect(&rahmen, FALSE);
	UpdateWindow();
}


void AusReihe::OnBnClickedSaeulen()
{
	InvalidateRect(&rahmen, FALSE);
	UpdateWindow();
}


void AusReihe::OnCbnSelchangeReihe()
{
	InvalidateRect(&rahmen, FALSE);
	UpdateWindow();
}


void AusReihe::OnBnClickedXraster()
{
	InvalidateRect(&rahmen, FALSE);
	UpdateWindow();
}


void AusReihe::OnBnClickedYraster()
{
	InvalidateRect(&rahmen, FALSE);
	UpdateWindow();
}

int AusReihe::scalePoint(int p, CSize* s1, CSize* s2)
{
	return((p - s1->cx)*(s2->cy - s2->cx)) / (s1->cy - s1->cx) + s2->cx;
}