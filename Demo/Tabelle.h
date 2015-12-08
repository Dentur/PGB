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

	CScrollBar sbar;
	CRect scrollrect;
	int actpos, maxpos;
	CPoint selectedField;

public:
	int columns;
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};
