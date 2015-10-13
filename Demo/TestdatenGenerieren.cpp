// TestdatenGenerieren.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "TestdatenGenerieren.h"
#include "afxdialogex.h"
#include "LoeschWarnung.h"


// TestdatenGenerieren-Dialogfeld

IMPLEMENT_DYNAMIC(TestdatenGenerieren, CDialog)

TestdatenGenerieren::TestdatenGenerieren(CWnd* pParent /*=NULL*/)
	: CDialog(TestdatenGenerieren::IDD, pParent)
	, namen(FALSE)
	, farben(FALSE)
	, werte(FALSE)
	, minimum(0)
	, maximum(0)
	, maxAbweichung(0)
{

}

TestdatenGenerieren::~TestdatenGenerieren()
{
}

void TestdatenGenerieren::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_NAMEN, namen);
	DDX_Check(pDX, IDC_FARBEN, farben);
	DDX_Check(pDX, IDC_WERTE, werte);
	DDX_Text(pDX, IDC_MINIMUM, minimum);
	DDX_Text(pDX, IDC_MAXIMUM, maximum);
	DDX_Text(pDX, IDC_ABWEICHUNG, maxAbweichung);
}


BEGIN_MESSAGE_MAP(TestdatenGenerieren, CDialog)
END_MESSAGE_MAP()


// TestdatenGenerieren-Meldungshandler


void TestdatenGenerieren::OnOK()
{
	if (GetParentFrame()->GetActiveDocument()->IsModified())
	{
		LoeschWarnung lw;
		if (lw.DoModal() != IDOK)
		{
			return;
		}
	}

	CDialog::OnOK();
}
