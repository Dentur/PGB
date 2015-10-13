// DatenNeu.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "DatenNeu.h"
#include "afxdialogex.h"
#include "LoeschWarnung.h"


// DatenNeu-Dialogfeld

IMPLEMENT_DYNAMIC(DatenNeu, CDialog)

DatenNeu::DatenNeu(CWnd* pParent /*=NULL*/)
	: CDialog(DatenNeu::IDD, pParent)
	, datenname(_T(""))
	, anzahl_z(0)
	, anzahl_s(0)
{

}

DatenNeu::~DatenNeu()
{
}

void DatenNeu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATENNAME, datenname);
	DDX_Text(pDX, IDC_ANZAHL_Z, anzahl_z);
	DDV_MinMaxInt(pDX, anzahl_z, 1, 20);
	DDX_Text(pDX, IDC_ANZAHL_S, anzahl_s);
	DDV_MinMaxInt(pDX, anzahl_s, 1, 50);
}


BEGIN_MESSAGE_MAP(DatenNeu, CDialog)
END_MESSAGE_MAP()


// DatenNeu-Meldungshandler


void DatenNeu::OnOK()
{
	// TODO: F�gen Sie hier Ihren spezialisierten Code ein, und/oder rufen Sie die Basisklasse auf.
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
