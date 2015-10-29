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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	DECLARE_MESSAGE_MAP()

	CRect rahmen;
public:
	int m_darstellung;
	int m_selection;
	CComboBox m_reihe;
	BOOL m_xraster;
	BOOL m_yraster;
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedLinien();
	afx_msg void OnBnClickedSaeulen();
	afx_msg void OnCbnSelchangeReihe();
	afx_msg void OnBnClickedXraster();
	afx_msg void OnBnClickedYraster();
};

CPoint scalePoint(CPoint p, CSize s1, CSize s2);