// LoeschWarnung.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "LoeschWarnung.h"
#include "afxdialogex.h"


// LoeschWarnung-Dialogfeld

IMPLEMENT_DYNAMIC(LoeschWarnung, CDialog)

LoeschWarnung::LoeschWarnung(CWnd* pParent /*=NULL*/)
	: CDialog(LoeschWarnung::IDD, pParent)
{

}

LoeschWarnung::~LoeschWarnung()
{
}

void LoeschWarnung::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LoeschWarnung, CDialog)
END_MESSAGE_MAP()


// LoeschWarnung-Meldungshandler
