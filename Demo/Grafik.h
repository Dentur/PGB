#pragma once


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

private:
	CButton anzeigen;
	CButton glgroup;
	CButton glplus;
	CButton glminus;
	CButton vbgroup;
	CEdit von;
	CEdit bis;
	CListBox auswahl;

public:
	//virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
