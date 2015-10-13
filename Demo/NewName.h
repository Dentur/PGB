#pragma once


// NewName-Dialogfeld

class NewName : public CDialog
{
	DECLARE_DYNAMIC(NewName)

public:
	NewName(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~NewName();

// Dialogfelddaten
	enum { IDD = IDD_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	CString name;
};
