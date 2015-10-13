
// MainFrm.h: Schnittstelle der Klasse CMainFrame
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // Nur aus Serialisierung erstellen
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attribute
public:

// Vorgänge
public:

// Überschreibungen
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementierung
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // Eingebettete Member der Steuerleiste
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// Generierte Funktionen für die Meldungstabellen
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEingabeTestdatein();
	afx_msg void OnUpdateEingabeTestdatein(CCmdUI *pCmdUI);
	afx_msg void OnEingabeName();
	afx_msg void OnUpdateEingabeName(CCmdUI *pCmdUI);
	afx_msg void OnEingabeDatenreihe();
	afx_msg void OnUpdateEingabeDatenreihe(CCmdUI *pCmdUI);
	afx_msg void OnEingabeDaten();
	afx_msg void OnUpdateEingabeDaten(CCmdUI *pCmdUI);
	afx_msg void OnFileNew();
	afx_msg void OnUpdateFileNew(CCmdUI *pCmdUI);
	afx_msg void OnAusgabeDatenreihe();
	afx_msg void OnUpdateAusgabeDatenreihe(CCmdUI *pCmdUI);
};


