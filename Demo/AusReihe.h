#pragma once


// AusReihe-Dialogfeld

class AusReihe : public CDialog
{
	DECLARE_DYNAMIC(AusReihe)

public:
	AusReihe(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~AusReihe();

// Dialogfelddaten
	enum { IDD = IDD_AUSREIHE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	int m_darstellung;
	int m_selection;
	CComboBox m_reihe;
	BOOL m_xraster;
	BOOL m_yraster;
	afx_msg void OnClose();
};
