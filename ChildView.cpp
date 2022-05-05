
// ChildView.cpp: Implementierung der CChildView-Klasse
//

#include "pch.h"
#include "framework.h"
#include "Computergrafik_Aufgabe_1.h"
#include "ChildView.h"
#include "Vector2.h"
#include "Vector3.h"
#include <chrono>
#include <thread>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <random>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_AUFGABE1_DIAGONALE, &CChildView::OnAufgabe1Diagonale)
	ON_COMMAND(ID_AUFGABE1_JULIAMENGE, &CChildView::OnAufgabe1Juliamenge)
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_AUFGABE1_MANDELBROT, &CChildView::OnAufgabe1Mandelbrot)
	ON_COMMAND(ID_AUFGABE3_QUADRAT, &CChildView::OnAufgabe3Quadrat)
	ON_COMMAND(ID_AUFGABE3_ROTIEREN, &CChildView::OnAufgabe3Rotieren)
	ON_COMMAND(ID_AUFGABE3_W32779, &CChildView::OnAufgabe3Wuerfel)
	ON_COMMAND(ID_AUFGABE5_OPENGL, &CChildView::OnAufgabe5Opengl)
END_MESSAGE_MAP()



// CChildView-Meldungshandler

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // Gerätekontext zum Zeichnen
	
	// TODO: Fügen Sie hier Ihren Meldungshandlercode ein.
	
	// Rufen Sie nicht CWnd::OnPaint() zum Zeichnen von Nachrichten auf
}


int size = 700;
double zoomfaktor = 2;
double valuesize = 1.6;
int mandelbrot = 0; //wenn mandelbrot, dann 1 (für zoom)

void CChildView::OnAufgabe1Diagonale()
{
	CRect rc, rp;
	GetClientRect(&rc);
	GetParent()->GetWindowRect(rp);

	int diffx = rp.Width() - rc.Width();
	int diffy = rp.Height() - rc.Height();

	GetParent()->SetWindowPos(NULL, 50, 50, size+diffx, size+diffy, SWP_SHOWWINDOW);

	UpdateWindow();

	CDC* pDC = GetDC();
	for (int i = 0; i < size; i++) {
		pDC->SetPixel(i, i, RGB(0, 0, 0));
	}
}


void CChildView::OnAufgabe1Juliamenge()
{
	mandelbrot = 0;
	CRect rc, rp;
	GetClientRect(&rc);
	GetParent()->GetWindowRect(rp);

	int diffx = rp.Width() - rc.Width();
	int diffy = rp.Height() - rc.Height();

	GetParent()->SetWindowPos(NULL, 50, 50, size + diffx, size + diffy, SWP_SHOWWINDOW);
	UpdateWindow();
	xdmin = -valuesize, xddelta = zoomfaktor * valuesize;
	ydmin = -valuesize, yddelta = zoomfaktor * valuesize;
	JuliaMalen();
}

	void CChildView::JuliaMalen() {
		CDC* pDC = GetDC();
		int xp, xpmin = 0, xpdelta = size;
		int yp, ypmin = 0, ypdelta = size;
		double xd; 
		double yd;
		
	for (xp = 0; xp < size; xp++) {
		for (yp = 0; yp < size; yp++) {
			xd = xdmin + xp * xddelta / xpdelta;
			yd = ydmin + yp * yddelta / ypdelta;
			
			double a_old = xd;
			double b_old = yd;
			double a_new, b_new, ab2;
			int n;
			for (n = 1; n < 255; n++) {
				a_new = a_old * a_old - b_old * b_old - 0.75;
				b_new = 2 * a_old * b_old + 0.06;
				a_old = a_new;
				b_old = b_new;
				ab2 = a_old * a_old + b_old * b_old;
				if (ab2 > 4) {
					break;
				}
			}
			if (ab2 > 4) {
				pDC->SetPixel(xp, yp, RGB(n, (int)ab2, n));
			}
			else {
				pDC->SetPixel(xp, yp, RGB(0, 0, 0));
			}
		}
	}
}


void CChildView::OnAufgabe1Mandelbrot()
{
	mandelbrot = 1;
	CRect rc, rp;
	GetClientRect(&rc);
	GetParent()->GetWindowRect(rp);

	int diffx = rp.Width() - rc.Width();
	int diffy = rp.Height() - rc.Height();

	GetParent()->SetWindowPos(NULL, 50, 50, size + diffx, size + diffy, SWP_SHOWWINDOW);
	UpdateWindow();
	xdmin = -2.0, xddelta = 2.5;
	ydmin = -1.25, yddelta = 2.5;
	MandelbrotMalen();
}

void CChildView::MandelbrotMalen() {
	CDC* pDC = GetDC();
	int xp, xpmin = 0, xpdelta = size;
	int yp, ypmin = 0, ypdelta = size;
	double xd;
	double yd;

	for (xp = 0; xp < size; xp++) {
		for (yp = 0; yp < size; yp++) {
			xd = xdmin + xp * xddelta / xpdelta;
			yd = ydmin + yp * yddelta / ypdelta;

			double a_old = xd;
			double b_old = yd;
			double a_new, b_new, ab2;
			int n;
			for (n = 1; n < 255; n++) {
				a_new = a_old * a_old - b_old * b_old + xd;
				b_new = 2 * a_old * b_old + yd;
				a_old = a_new;
				b_old = b_new;
				ab2 = a_old * a_old + b_old * b_old;
				if (ab2 > 4) {
					break;
				}
			}
			if (ab2 > 4) {
				pDC->SetPixel(xp, yp, RGB(n, (int)ab2, n));
			}
			else {
				pDC->SetPixel(xp, yp, RGB(0, 0, 0));
			}
		}
	}
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	double xd = xdmin + point.x * xddelta / size;
	double yd = ydmin + point.y * yddelta / size;

	xddelta = xddelta * 2;
	yddelta = yddelta * 2;

	xdmin = xd - xddelta / 2;
	ydmin = yd - yddelta / 2;
	if (mandelbrot) {
		MandelbrotMalen();
	}
	else {
		JuliaMalen();
	}

	CWnd::OnRButtonUp(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	double xd = xdmin + point.x * xddelta / size;
	double yd = ydmin + point.y * yddelta / size;

	xddelta = xddelta / 2;
	yddelta = yddelta / 2;

	xdmin = xd - xddelta / 2;
	ydmin = yd - yddelta / 2;

	if (mandelbrot) {
		MandelbrotMalen();
	}
	else {
		JuliaMalen();
	}

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnAufgabe3Quadrat()
{
	Vector2 Quadrat[4];
	Quadrat[0] = Vector2(50, 50);
	Quadrat[1] = Vector2(150, 50);
	Quadrat[2] = Vector2(150, 150);
	Quadrat[3] = Vector2(50, 150);

	CDC* pDC = GetDC();

	pDC->MoveTo(Quadrat[3].vek[0], Quadrat[3].vek[1]);
	for (int ii = 0; ii < 4; ii++) {
		pDC->LineTo(Quadrat[ii].vek[0], Quadrat[ii].vek[1]);
	}

	Matrix2 TransMat;
	TransMat.setTrans(-100, -100);
	for (int ii = 0; ii < 4; ii++) {
		Quadrat[ii] = TransMat * Quadrat[ii];
	}

	Matrix2 RotMat;
	RotMat.setRot(10);

	for (int ii = 0; ii < 4; ii++) {
		Quadrat[ii] = RotMat * Quadrat[ii];
	}

	Matrix2 TransMatR;
	TransMatR.setTrans(100, 100);

	for (int ii = 0; ii < 4; ii++) {
		Quadrat[ii] = TransMatR * Quadrat[ii];
	}
	pDC->MoveTo(Quadrat[3].vek[0], Quadrat[3].vek[1]);
	for (int ii = 0; ii < 4; ii++) {
		pDC->LineTo(Quadrat[ii].vek[0], Quadrat[ii].vek[1]);
	}
}


void CChildView::OnAufgabe3Rotieren()
{
	CRect rc;
	GetClientRect(&rc);

	int winx = rc.Width() / 2;
	int winy = rc.Height() / 2;

	int size = 200;

	Vector2 Quadrat[4];
	Quadrat[0] = Vector2(winx - size, winy - size);
	Quadrat[1] = Vector2(winx + size, winy - size);
	Quadrat[2] = Vector2(winx + size, winy + size);
	Quadrat[3] = Vector2(winx - size, winy + size);

	CDC* pDC = GetDC();

	for (int i = 0; i < 500; i++) {
		pDC->FillSolidRect(0, 0, winx * 2, winy * 2, RGB(255, 255, 255));
		Matrix2 TransMat;
		TransMat.setTrans(-winx, -winy);
		for (int ii = 0; ii < 4; ii++) {
			Quadrat[ii] = TransMat * Quadrat[ii];
		}

		Matrix2 RotMat;
		RotMat.setRot(0.01);

		for (int ii = 0; ii < 4; ii++) {
			Quadrat[ii] = RotMat * Quadrat[ii];
		}

		Matrix2 TransMatR;
		TransMatR.setTrans(winx, winy);

		for (int ii = 0; ii < 4; ii++) {
			Quadrat[ii] = TransMatR * Quadrat[ii];
		}
		pDC->MoveTo(Quadrat[3].vek[0], Quadrat[3].vek[1]);
		for (int ii = 0; ii < 4; ii++) {
			pDC->LineTo(Quadrat[ii].vek[0], Quadrat[ii].vek[1]);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}


void CChildView::OnAufgabe3Wuerfel()
{
	CRect rc;
	GetClientRect(&rc);

	int winx = rc.Width() / 2;
	int winy = rc.Height() / 2;

	int size = 100;
	int ms = 1;
	int diff = 0;
	double verschiebex = winx-(size*1);
	double verschiebey = winy-(size*1);

	Vector3 Wuerfel[8];
	Wuerfel[0] = Vector3(winx - size, winy - size, 0);
	Wuerfel[1] = Vector3(winx + size, winy - size, 0);
	Wuerfel[2] = Vector3(winx + size, winy + size, 0);
	Wuerfel[3] = Vector3(winx - size, winy + size, 0);
	Wuerfel[4] = Vector3(winx - size + diff, winy - size + diff, size * 2);
	Wuerfel[5] = Vector3(winx + size + diff, winy - size + diff, size * 2);
	Wuerfel[6] = Vector3(winx + size + diff, winy + size + diff, size * 2);
	Wuerfel[7] = Vector3(winx - size + diff, winy + size + diff, size * 2);

	CDC* pDC = GetDC();
	double ax = 0.01, ay = 0.01, az = 0.01, x, y, z, rx, ry, rz;
	for (int i = 0; i < 100000; i++) {
		for (int aa = 0; aa < 8; aa++) {
			for (int ii = 0; ii < 8; ii++) {
				Wuerfel[ii].setX(Wuerfel[ii].getX() - verschiebex);
				Wuerfel[ii].setY(Wuerfel[ii].getY() - verschiebey);
			}
			//rotX
			x = Wuerfel[aa].getX();
			y = Wuerfel[aa].getY();
			z = Wuerfel[aa].getZ();
			rx = x;
			ry = (y * cos(ax)) - (z * sin(ax));
			rz = (y * sin(ax)) + (z * cos(ax));
			Wuerfel[aa].setX(rx);
			Wuerfel[aa].setY(ry);
			Wuerfel[aa].setZ(rz);
			x = rx;
			y = ry;
			z = rz;
			
			//rotY
			x = Wuerfel[aa].getX();
			y = Wuerfel[aa].getY();
			z = Wuerfel[aa].getZ();
			rx = (z * sin(ay)) + (x * cos(ay));
			ry = y;
			rz = (z * cos(ay)) - (x * sin(ay));
			Wuerfel[aa].setX(rx);
			Wuerfel[aa].setY(ry);
			Wuerfel[aa].setZ(rz);
			x = rx;
			y = ry;
			z = rz;
			
			//rotZ
			x = Wuerfel[aa].getX();
			y = Wuerfel[aa].getY();
			z = Wuerfel[aa].getZ();
			rx = (x * cos(az)) - (y * sin(az));
			ry = (x * sin(az)) + (y * cos(az));
			rz = z;
			Wuerfel[aa].setX(rx);
			Wuerfel[aa].setY(ry);
			Wuerfel[aa].setZ(rz);
			x = rx;
			y = ry;
			z = rz;
			for (int ii = 0; ii < 8; ii++) {
				Wuerfel[ii].setX(Wuerfel[ii].getX() + verschiebex);
				Wuerfel[ii].setY(Wuerfel[ii].getY() + verschiebey);
			}
			
		}
		//draw
		pDC->FillSolidRect(0, 0, winx * 2, winy * 2, RGB(255, 255, 255));
		pDC->MoveTo(Wuerfel[3].vek[0], Wuerfel[3].vek[1]);
		for (int ii = 0; ii < 4; ii++)	pDC->LineTo(Wuerfel[ii].vek[0], Wuerfel[ii].vek[1]);
		pDC->MoveTo(Wuerfel[7].vek[0], Wuerfel[7].vek[1]);
		for (int ii = 4; ii < 8; ii++) pDC->LineTo(Wuerfel[ii].vek[0], Wuerfel[ii].vek[1]);
		for (int ii = 0; ii < 4; ii++) {
			pDC->MoveTo(Wuerfel[ii].vek[0], Wuerfel[ii].vek[1]);
			pDC->LineTo(Wuerfel[ii + 4].vek[0], Wuerfel[ii + 4].vek[1]);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
		//end draw
	}

}

void CChildView::OnAufgabe5Opengl()
{
	CRect rc;
	GetClientRect(&rc);
	GLInit(900, 900, 1);
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 1.5, 6);
	gluLookAt(1.0, 1.0, 3.0, //Augpunkt
		0.0, 0.0, 0.0, //Zielpunkt
		0.0, 1.0, 0.0);//Up-Vektor
	glEnable(GL_DEPTH_TEST);

	for (int i = 0; ; i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		Achsenkreuz(1.6);
		glRotated(i*2, 1.0, 0.0, 0.0);
		glRotated(i*1.5, 0.0, 1.0, 0.0);
		glRotated(i, 1.0, 0.0, 1.0);
		Bunter_Einheitswuerfel();

		double minicubespeed = 1.4;
		
		
		glLoadIdentity();
		glScaled(0.5, 0.5, 0.5);
		glRotated(i * 2, 1.0, 0.0, 0.0);
		glRotated(i * 1.5, 0.0, 1.0, 0.0);
		glRotated(i, 1.0, 0.0, 1.0);
		glTranslated(1.5, 0, 0);
		glRotated(i*minicubespeed, 1.0, 0, 0);
		Bunter_Einheitswuerfel();

		glLoadIdentity();
		glScaled(0.5, 0.5, 0.5);
		glRotated(i * 2, 1.0, 0.0, 0.0);
		glRotated(i * 1.5, 0.0, 1.0, 0.0);
		glRotated(i, 1.0, 0.0, 1.0);
		glTranslated(-1.5, 0, 0);
		glRotated(i * minicubespeed, -1.0, 0, 0);
		Bunter_Einheitswuerfel();

		glLoadIdentity();
		glScaled(0.5, 0.5, 0.5);
		glRotated(i * 2, 1.0, 0.0, 0.0);
		glRotated(i * 1.5, 0.0, 1.0, 0.0);
		glRotated(i, 1.0, 0.0, 1.0);
		glTranslated(0, 1.5, 0);
		glRotated(i * minicubespeed, 0, 1.0, 0);
		Bunter_Einheitswuerfel();

		glLoadIdentity();
		glScaled(0.5, 0.5, 0.5);
		glRotated(i * 2, 1.0, 0.0, 0.0);
		glRotated(i * 1.5, 0.0, 1.0, 0.0);
		glRotated(i, 1.0, 0.0, 1.0);
		glTranslated(0, -1.5, 0);
		glRotated(i * minicubespeed, 0, -1.0, 0);
		Bunter_Einheitswuerfel();

		glLoadIdentity();
		glScaled(0.5, 0.5, 0.5);
		glRotated(i * 2, 1.0, 0.0, 0.0);
		glRotated(i * 1.5, 0.0, 1.0, 0.0);
		glRotated(i, 1.0, 0.0, 1.0);
		glTranslated(0, 0, 1.5);
		glRotated(i * minicubespeed, 0, 0, 1.0);
		Bunter_Einheitswuerfel();

		glLoadIdentity();
		glScaled(0.5, 0.5, 0.5);
		glRotated(i * 2, 1.0, 0.0, 0.0);
		glRotated(i * 1.5, 0.0, 1.0, 0.0);
		glRotated(i, 1.0, 0.0, 1.0);
		glTranslated(0, 0, -1.5);
		glRotated(i * minicubespeed, 0, 0, -1.0);
		Bunter_Einheitswuerfel();

		SwapBuffers(wglGetCurrentDC());

		if (GetAsyncKeyState(VK_ESCAPE))
			break;
	}
	GLInit(700, 700, 0);
}

// Achtung!!!
// Funktionsdefinitionen auch in Header-Datei übernehmen

void CChildView::GLInit(int Breite, int Hoehe, int Modus)
{
	static HDC         hdc;
	static HGLRC       hglrc;
	int         iPixelFormat;
	HWND hwnd = GetSafeHwnd();


	static PIXELFORMATDESCRIPTOR pfd =	//pfd legt das Aussehen der Szene fest
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,						//Versionsnummer
		PFD_DRAW_TO_WINDOW |	//pfd muss Windows unterstützen
		PFD_SUPPORT_OPENGL |	//pfd muss OpenGL unterstützen
		PFD_DOUBLEBUFFER ,		//Doppelpuffer wird unterstützt
		PFD_TYPE_RGBA,			//RGBA-Farbformat auswählen
		32,						//Bit-Farbtiefe
		0, 0, 0, 0, 0, 0,		//Farbbits werden ignoriert
		0,						//kein Alphapuffer
		0,						//Schiebebit ignoriert
		0,						//kein Ansammlungspuffer
		0, 0, 0, 0,				//Ansammlungsbits werden ignoriert
		16,						//16bit Z-Puffer (Tiefenpuffer)
		16,						//Masken-Puffer
		0,						//keinen Hilfs-Puffer
		PFD_MAIN_PLANE,			//Festlegung der Zeichenebene (Hauptebene)
		0,						//reserviert
		0, 0, 0					//Ebenenmasken werden ignoriert 
	};
	CDC* pDC = GetDC();
	CRect gesamt, client;
	GetWindowRect(&gesamt);
	GetClientRect(&client);
	int diff_x = gesamt.Width() - client.Width();
	int diff_y = gesamt.Height() - client.Height();
	int m_height = Hoehe;
	int m_width = Breite;

	switch (Modus)
	{
	case 1:  // Modus 1 -> Initialisierung

		// ---------- Fenstergröße
		GetParent()->SetWindowPos(&wndTop,
			50, 50, m_height + diff_x, m_width + diff_y, 0);
		//		GetParent()->ShowWindow(SW_NORMAL);
		GetParent()->RedrawWindow();
		// ------ Device Context
		hdc = pDC->GetSafeHdc();

		// ------ Pixelformat einstellen (OpenGL-fähig)
		iPixelFormat = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, iPixelFormat, &pfd);

		// ----  Rendering-Context erstellen und zuweisen
		hglrc = wglCreateContext(hdc);
		if (hglrc == NULL) { SetWindowText(CString("Fehler beim RC !")); Sleep(2000); }
		wglMakeCurrent(hdc, hglrc);
		break;

	case 0:  // Modus 0 -> Beenden
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hglrc);

		ReleaseDC(pDC);
		break;
	}
	return;

}
/*
float randa = (float)(rand()) / ((float)(RAND_MAX));
float randb = (float)(rand()) / ((float)(RAND_MAX));
float randc = (float)(rand()) / ((float)(RAND_MAX));*/
float randa = 0;
float randb = 1;
float randc = 0;

void CChildView::Bunter_Einheitswuerfel()
{
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);          // grün bei z = -0.5
	glNormal3f(0, 0, -1);
	glVertex3f(-0.5, -0.5, -0.5);

	glVertex3f(-0.5, 0.5, -0.5);

	glVertex3f(0.5, 0.5, -0.5);

	glVertex3f(0.5, -0.5, -0.5);

	glColor3f(1, 0, 0);        // rot bei z = 0.5
	glNormal3f(0, 0, 1);
	glVertex3f(-0.5, -0.5, 0.5);

	glVertex3f(0.5, -0.5, 0.5);

	glVertex3f(0.5, 0.5, 0.5);

	glVertex3f(-0.5, 0.5, 0.5);

	glColor3f(1, 0.75, 0.25);  // orange bei y = -0.5
	glNormal3f(0, -1, 0);
	glVertex3f(-0.5, -0.5, -0.5);

	glVertex3f(0.5, -0.5, -0.5);

	glVertex3f(0.5, -0.5, 0.5);

	glVertex3f(-0.5, -0.5, 0.5);

	glColor3f(0, 0, 1);          // blau bei y = 0.5
	glNormal3f(0, 1, 0);
	glVertex3f(-0.5, 0.5, -0.5);

	glVertex3f(-0.5, 0.5, 0.5);

	glVertex3f(0.5, 0.5, 0.5);

	glVertex3f(0.5, 0.5, -0.5);

	glColor3f(1, 0, 1);          // lila bei x =  0.5
	glNormal3f(-1, 0, 0);
	glVertex3f(-0.5, -0.5, -0.5);

	glVertex3f(-0.5, -0.5, 0.5);

	glVertex3f(-0.5, 0.5, 0.5);

	glVertex3f(-0.5, 0.5, -0.5);

	glColor3f(1, 1, 0);          // gelb bei x = -0.5
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, -0.5, -0.5);

	glVertex3f(0.5, 0.5, -0.5);

	glVertex3f(0.5, 0.5, 0.5);

	glVertex3f(0.5, -0.5, 0.5);
	glEnd();
}

void CChildView::Achsenkreuz(float l)
{
	GLfloat Pfeil = (float)0.05;

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(-l, 0, 0);  // Achsen
	glVertex3f(l, 0, 0);

	glVertex3f(0, -l, 0);
	glVertex3f(0, l, 0);

	glVertex3f(0, 0, -l);
	glVertex3f(0, 0, l);

	glVertex3f(l, 0, 0);  // Pfeile
	glVertex3f(l - Pfeil, Pfeil, 0);

	glVertex3f(l, 0, 0);
	glVertex3f(l - Pfeil, -Pfeil, 0);

	glVertex3f(0, l, 0);  // Pfeile
	glVertex3f(0, l - Pfeil, Pfeil);

	glVertex3f(0, l, 0);
	glVertex3f(0, l - Pfeil, -Pfeil);

	glVertex3f(0, 0, l);  // Pfeile
	glVertex3f(Pfeil, 0, l - Pfeil);

	glVertex3f(0, 0, l);
	glVertex3f(-Pfeil, 0, l - Pfeil);
	glEnd();
}
