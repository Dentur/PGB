#pragma once


// EinReihe-Dialogfeld

class EinReihe : public CDialog
{
	DECLARE_DYNAMIC(EinReihe)

public:
	EinReihe(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~EinReihe();

// Dialogfelddaten
	enum { IDD = IDD_DATENREIHE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
private:
	void rowChanged(int pos);

public:
	int reihe;
	CString name;
	virtual BOOL OnInitDialog();
	CButton minus;
	CButton plus;
	afx_msg void OnBnClickedMinus();
	afx_msg void OnBnClickedPlus();
	afx_msg void OnBnClickedSpeichern();
	afx_msg void OnBnClickedAndern();
};
