#pragma once


// Tabelle-Dialogfeld

class Tabelle : public CDialog
{
	DECLARE_DYNAMIC(Tabelle)

public:
	Tabelle(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~Tabelle();

// Dialogfelddaten
	enum { IDD = IDD_TABELLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()

public:
	int columns;
};
