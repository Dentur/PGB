#pragma once


// Legende-Dialogfeld

class Legende : public CDialog
{
	DECLARE_DYNAMIC(Legende)

public:
	Legende(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~Legende();

// Dialogfelddaten
	enum { IDD = IDD_LEGENDE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};
