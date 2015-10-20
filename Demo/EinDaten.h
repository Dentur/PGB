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

private:
	void scroll_to(int pos);

public:
	int auswahl;
	CComboBox combobox;
	int nummer;
	CScrollBar scrollbar;
	int wert;
	virtual BOOL OnInitDialog();
};
