
// Computergrafik_Aufgabe_1.h: Hauptheaderdatei für die Computergrafik_Aufgabe_1-Anwendung
//
#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"       // Hauptsymbole


// CComputergrafikAufgabe1App:
// Siehe Computergrafik_Aufgabe_1.cpp für die Implementierung dieser Klasse
//

class CComputergrafikAufgabe1App : public CWinApp
{
public:
	CComputergrafikAufgabe1App() noexcept;


// Überschreibungen
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementierung

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CComputergrafikAufgabe1App theApp;
