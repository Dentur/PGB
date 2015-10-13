#pragma once


// DatenNeu-Dialogfeld

class DatenNeu : public CDialog
{
	DECLARE_DYNAMIC(DatenNeu)

public:
	DatenNeu(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~DatenNeu();

// Dialogfelddaten
	enum { IDD = IDD_DATENNEU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	CString datenname;
	int anzahl_z;
	int anzahl_s;
};
