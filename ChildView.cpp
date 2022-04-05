
// ChildView.cpp: Implementierung der CChildView-Klasse
//

#include "pch.h"
#include "framework.h"
#include "Computergrafik_Aufgabe_1.h"
#include "ChildView.h"

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