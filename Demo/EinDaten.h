#pragma once


// EinDaten-Dialogfeld

class EinDaten : public CDialog
{
	DECLARE_DYNAMIC(EinDaten)

public:
	EinDaten(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~EinDaten();

// Dialogfelddaten
	enum { IDD = IDD_EINDATEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
};
