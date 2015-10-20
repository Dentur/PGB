// EinDaten.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "EinDaten.h"
#include "afxdialogex.h"


// EinDaten-Dialogfeld

IMPLEMENT_DYNAMIC(EinDaten, CDialog)

EinDaten::EinDaten(CWnd* pParent /*=NULL*/)
	: CDialog(EinDaten::IDD, pParent)
	, auswahl(0)
	, nummrt(0)
	, wert(0)
{

}

EinDaten::~EinDaten()
{
}

void EinDaten::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_AUSWAHL, auswahl);
	DDX_Control(pDX, IDC_AUSWAHL, combobox);
	DDX_Text(pDX, IDC_NUMBER, nummrt);
	DDX_Control(pDX, IDC_SCROLL, scrollbar);
	DDX_Text(pDX, IDC_WERT, wert);
}


BEGIN_MESSAGE_MAP(EinDaten, CDialog)
END_MESSAGE_MAP()


// EinDaten-Meldungshandler
