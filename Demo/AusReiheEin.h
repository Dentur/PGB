#pragma once


// AusReiheEin-Dialogfeld

class AusReiheEin : public CDialog
{
	DECLARE_DYNAMIC(AusReiheEin)

public:
	AusReiheEin(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~AusReiheEin();

// Dialogfelddaten
	enum { IDD = IDD_AusReiheEin };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	int wert;
	virtual BOOL OnInitDialog();
};
