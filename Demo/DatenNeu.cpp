// DatenNeu.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "DatenNeu.h"
#include "afxdialogex.h"


// DatenNeu-Dialogfeld

IMPLEMENT_DYNAMIC(DatenNeu, CDialog)

DatenNeu::DatenNeu(CWnd* pParent /*=NULL*/)
	: CDialog(DatenNeu::IDD, pParent)
{

}

DatenNeu::~DatenNeu()
{
}

void DatenNeu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DatenNeu, CDialog)
END_MESSAGE_MAP()


// DatenNeu-Meldungshandler
