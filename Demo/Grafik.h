#pragma once
#include "Daten.h"

// Grafik-Dialogfeld

class Grafik : public CDialog
{
	DECLARE_DYNAMIC(Grafik)

public:
	Grafik(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~Grafik();

// Dialogfelddaten
	enum { IDD = IDD_GRAFIK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
	void OnAnzeigen();
	void OnGlPlus();
	void OnGlMinus();
	int vmin;
	int vmax;


private:
	CButton anzeigen;
	CButton glgroup;
	CButton glplus;
	CButton glminus;
	CButton vbgroup;
	CEdit von;
	CEdit bis;
	CListBox auswahl;
	int scalePoint(int p, CSize* s1, CSize* s2);
	CRect drawRegion;
	bool row[MAX_ZEILEN];

public:
	//virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};
