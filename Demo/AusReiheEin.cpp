// AusReiheEin.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "AusReiheEin.h"
#include "afxdialogex.h"


// AusReiheEin-Dialogfeld

IMPLEMENT_DYNAMIC(AusReiheEin, CDialog)

AusReiheEin::AusReiheEin(CWnd* pParent /*=NULL*/)
	: CDialog(AusReiheEin::IDD, pParent)
	, wert(0)
{

}

AusReiheEin::~AusReiheEin()
{
}

void AusReiheEin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, wert);
}


BEGIN_MESSAGE_MAP(AusReiheEin, CDialog)
END_MESSAGE_MAP()


// AusReiheEin-Meldungshandler


BOOL AusReiheEin::OnInitDialog()
{
	CDialog::OnInitDialog();

	POINT mouse;
	CRect r;

	GetCursorPos(&mouse);
	GetWindowRect(&r);
	r.OffsetRect(mouse.x - r.left, mouse.y - r.bottom);
	MoveWindow(r, true);

	return TRUE;  // return TRUE unless you set the focus to a control
	// AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}
