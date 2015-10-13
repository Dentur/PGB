// NewName.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "NewName.h"
#include "afxdialogex.h"


// NewName-Dialogfeld

IMPLEMENT_DYNAMIC(NewName, CDialog)

NewName::NewName(CWnd* pParent /*=NULL*/)
	: CDialog(NewName::IDD, pParent)
	, name(_T(""))
{

}

NewName::~NewName()
{
}

void NewName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME, name);
}


BEGIN_MESSAGE_MAP(NewName, CDialog)
END_MESSAGE_MAP()


// NewName-Meldungshandler
