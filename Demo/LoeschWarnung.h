#pragma once


// LoeschWarnung-Dialogfeld

class LoeschWarnung : public CDialog
{
	DECLARE_DYNAMIC(LoeschWarnung)

public:
	LoeschWarnung(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~LoeschWarnung();

// Dialogfelddaten
	enum { IDD = IDD_LOESCHWARNUNG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
};
