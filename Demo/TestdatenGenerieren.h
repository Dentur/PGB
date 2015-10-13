#pragma once


// TestdatenGenerieren-Dialogfeld

class TestdatenGenerieren : public CDialog
{
	DECLARE_DYNAMIC(TestdatenGenerieren)

public:
	TestdatenGenerieren(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~TestdatenGenerieren();

// Dialogfelddaten
	enum { IDD = IDD_TESTDATEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	BOOL namen;
	BOOL farben;
	BOOL werte;
	int minimum;
	int maximum;
	int maxAbweichung;
	virtual void OnOK();
};
