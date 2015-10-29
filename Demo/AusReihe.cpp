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

	CDialog::OnClose();
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
	if (m_darstellung == 0)
	{
		int r = ;
		for (int index = 0; index < DemoData.get_anz_s(); index++)
		{

		}
	}
	else
	{
		
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

CPoint scalePoint(int p, CSize s1, CSize s2)
{
	return(p - s1.cx)*(s1.cy - s1.cx) / (s1.cy - s1.cx) + s1.cx;
}