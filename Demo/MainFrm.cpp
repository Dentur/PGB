
// MainFrm.cpp: Implementierung der Klasse CMainFrame
//

#include "stdafx.h"
#include "Demo.h"
#include "Daten.h"
#include "DatenNeu.h"
#include "NewName.h"
#include "TestdatenGenerieren.h"
#include "MainFrm.h"
#include "EinDaten.h"
#include "EinReihe.h"
#include "AusReihe.h"
#include "draw.h"
#include "Legende.h"
#include "Tabelle.h"
#include "Grafik.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_EINGABE_TESTDATEIN, &CMainFrame::OnEingabeTestdatein)
	ON_UPDATE_COMMAND_UI(ID_EINGABE_TESTDATEIN, &CMainFrame::OnUpdateEingabeTestdatein)
	ON_COMMAND(ID_EINGABE_NAME, &CMainFrame::OnEingabeName)
	ON_UPDATE_COMMAND_UI(ID_EINGABE_NAME, &CMainFrame::OnUpdateEingabeName)
	ON_COMMAND(ID_EINGABE_DATENREIHE, &CMainFrame::OnEingabeDatenreihe)
	ON_UPDATE_COMMAND_UI(ID_EINGABE_DATENREIHE, &CMainFrame::OnUpdateEingabeDatenreihe)
	ON_COMMAND(ID_EINGABE_DATEN, &CMainFrame::OnEingabeDaten)
	ON_UPDATE_COMMAND_UI(ID_EINGABE_DATEN, &CMainFrame::OnUpdateEingabeDaten)
	ON_COMMAND(ID_FILE_NEW, &CMainFrame::OnFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, &CMainFrame::OnUpdateFileNew)
	ON_COMMAND(ID_AUSGABE_DATENREIHE, &CMainFrame::OnAusgabeDatenreihe)
	ON_UPDATE_COMMAND_UI(ID_AUSGABE_DATENREIHE, &CMainFrame::OnUpdateAusgabeDatenreihe)
	ON_COMMAND(ID_EINGABE_TESTDATEN, &CMainFrame::OnEingabeTestdaten)
	ON_UPDATE_COMMAND_UI(ID_EINGABE_TESTDATEN, &CMainFrame::OnUpdateEingabeTestdaten)
	ON_COMMAND(ID_ANSICHT_EINGABELEISTE, &CMainFrame::OnAnsichtEingabeleiste)
	ON_UPDATE_COMMAND_UI(ID_ANSICHT_EINGABELEISTE, &CMainFrame::OnUpdateAnsichtEingabeleiste)
	ON_COMMAND(ID_AUSGABE_LEGENDE, &CMainFrame::OnAusgabeLegende)
	ON_UPDATE_COMMAND_UI(ID_AUSGABE_LEGENDE, &CMainFrame::OnUpdateAusgabeLegende)
	ON_COMMAND(ID_AUSGABE_TABELLE, &CMainFrame::OnAusgabeTabelle)
	ON_UPDATE_COMMAND_UI(ID_AUSGABE_TABELLE, &CMainFrame::OnUpdateAusgabeTabelle)
	ON_COMMAND(ID_AUSGABE_GRAFIK, &CMainFrame::OnAusgabeGrafik)
	ON_UPDATE_COMMAND_UI(ID_AUSGABE_GRAFIK, &CMainFrame::OnUpdateAusgabeGrafik)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // Statusleistenanzeige
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame-Erstellung/Zerst�rung

CMainFrame::CMainFrame()
{
	// TODO: Hier Code f�r die Memberinitialisierung einf�gen
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Fehler beim Erstellen der Symbolleiste.\n");
		return -1;      // Fehler beim Erstellen
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Fehler beim Erstellen der Statusleiste.\n");
		return -1;      // Fehler beim Erstellen
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: L�schen Sie diese drei Zeilen, wenn Sie nicht m�chten, dass die Systemleiste andockbar ist
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	dialogbar_ein.Create(this, IDD_DIALOGBAR_EIN, CBRS_ALIGN_BOTTOM, AFX_IDW_CONTROLBAR_FIRST + 50);
	dialogbar_ein.EnableDocking(CBRS_ALIGN_ANY);
	dialogbar_ein.SetWindowText("Eingaben");
	DockControlBar(&dialogbar_ein, AFX_IDW_DOCKBAR_BOTTOM);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ndern Sie hier die Fensterklasse oder die Darstellung, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return TRUE;
}

// CMainFrame-Diagnose

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame-Meldungshandler

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}



void CMainFrame::OnEingabeTestdatein()
{
		
}


void CMainFrame::OnUpdateEingabeTestdatein(CCmdUI *pCmdUI)
{
	// TODO: F�gen Sie hier Ihren Befehlsaktualisierungs-UI-Behandlungscode ein.
}


void CMainFrame::OnEingabeName()
{
	NewName nn;
	nn.name = DemoData.get_name();
	if (nn.DoModal() == IDOK)
	{
		DemoData.set_name(nn.name);
		GetActiveDocument()->SetModifiedFlag();
		update_name();
	}
}


void CMainFrame::OnUpdateEingabeName(CCmdUI *pCmdUI)
{
	// TODO: F�gen Sie hier Ihren Befehlsaktualisierungs-UI-Behandlungscode ein.
}


void CMainFrame::OnEingabeDatenreihe()
{
	EinReihe reihe = new EinReihe(this);
	reihe.DoModal();
}


void CMainFrame::OnUpdateEingabeDatenreihe(CCmdUI *pCmdUI)
{
	// TODO: F�gen Sie hier Ihren Befehlsaktualisierungs-UI-Behandlungscode ein.
}


void CMainFrame::OnEingabeDaten()
{
	EinDaten eDat = new EinDaten(this);
	eDat.DoModal();
}


void CMainFrame::OnUpdateEingabeDaten(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnFileNew()
{
	DatenNeu dn;

	dn.datenname = DemoData.get_name();
	dn.anzahl_z = 10;
	dn.anzahl_s = 10;
	if (dn.DoModal() == IDOK)
	{
		DemoData.init(dn.anzahl_z, dn.anzahl_s, dn.datenname);
		GetActiveDocument()->SetModifiedFlag();

		stdbrush.setall();
		stdpen.setall();
	}

}


void CMainFrame::OnUpdateFileNew(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnAusgabeDatenreihe()
{
	//AfxMessageBox("Men� Augabe->Datenreihe noch nicht implementiert!", MB_OK | MB_ICONINFORMATION, 0);
	new AusReihe;

}



void CMainFrame::OnUpdateAusgabeDatenreihe(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(DemoData.get_anz_z());
}


void CMainFrame::OnEingabeTestdaten()
{
	TestdatenGenerieren tg;
	tg.namen = true;
	tg.farben = true;
	tg.werte = true;
	tg.minimum = -10;
	tg.maximum = 10;
	tg.maxAbweichung = 2;
	if (tg.DoModal())
	{
		DemoData.testdaten(tg.minimum, tg.maximum, tg.maxAbweichung, tg.namen, tg.farben, tg.werte);
		GetActiveDocument()->SetModifiedFlag();
	}

	stdbrush.setall();
	stdpen.setall();
	update_all(true, true, true);
}


void CMainFrame::OnUpdateEingabeTestdaten(CCmdUI *pCmdUI)
{
	// TODO: F�gen Sie hier Ihren Befehlsaktualisierungs-UI-Behandlungscode ein.
}


void CMainFrame::OnAnsichtEingabeleiste()
{
	ShowControlBar(&dialogbar_ein, !dialogbar_ein.IsWindowVisible(), TRUE);
}


void CMainFrame::OnUpdateAnsichtEingabeleiste(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(dialogbar_ein.IsWindowVisible());
}


void CMainFrame::OnAusgabeLegende()
{
	new Legende;
}


void CMainFrame::OnUpdateAusgabeLegende(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnAusgabeTabelle()
{
	new Tabelle;
}


void CMainFrame::OnUpdateAusgabeTabelle(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnAusgabeGrafik()
{
	new Grafik;
}


void CMainFrame::OnUpdateAusgabeGrafik(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}
