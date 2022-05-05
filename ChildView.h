
// ChildView.h: Schnittstelle der CChildView-Klasse
//


#pragma once
#include <gl/GL.h>
#include <gl/GLU.h>


// CChildView-Fenster

class CChildView : public CWnd
{
// Konstruktion
public:
	CChildView();
	double xdmin;
	double xddelta;
	double ydmin;
	double yddelta;
	void JuliaMalen();
	void MandelbrotMalen();
	void GLInit(int Breite, int Hoehe, int Modus);
	void Achsenkreuz(float l);
	void Bunter_Einheitswuerfel();

// Attribute
public:

// Vorgänge
public:

// Überschreibungen
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementierung
public:
	virtual ~CChildView();

	// Generierte Funktionen für die Meldungstabellen
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAufgabe1Diagonale();
	afx_msg void OnAufgabe1Juliamenge();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnAufgabe1Mandelbrot();
	afx_msg void OnAufgabe3Quadrat();
	afx_msg void OnAufgabe3Rotieren();
	afx_msg void OnAufgabe3Wuerfel();
	afx_msg void OnAufgabe5Opengl();
};

