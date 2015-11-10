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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung

	DECLARE_MESSAGE_MAP()

	CScrollBar sbar;
	CRect scrollrect;
	int actpos, maxpos;

public:
	int columns;
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};