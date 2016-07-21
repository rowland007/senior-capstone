/************************************************************************
Program:		CapstoneProject
Author:			Michael Morrison
Class:			Bitmap
Instructor:		Dan Randall
Date:			18 July 2016
Description:	Bitmap class loads information about a bitmap into memory
				also enables it to be drawn to the screen.
Input:
Output:

Compilation instructions:
Usage:
Known bugs/missing features:

Modifications:
Date                Comment
----    ------------------------------------------------
18Jul16	Made Get functions const
************************************************************************/
#pragma
#include <Windows.h>
class Bitmap
{
protected:
	//member variables
	HBITMAP		m_hBitmap;
	int			m_iWidth;
	int			m_iHeight;

	//Helper function
	void Free();

public:
	Bitmap();
	Bitmap(HDC hDC, LPTSTR szFilename);
	Bitmap(HDC hDC, UINT uiResID, HINSTANCE hInstance);
	Bitmap(HDC hDC, int iWidth, int iHeight, COLORREF crColor = RGB(0, 0, 0));
	virtual ~Bitmap();

	//General Methods
	BOOL Create(HDC hDC, LPTSTR szFilename);
	BOOL Create(HDC hDC, UINT uiResID, HINSTANCE hInstance);
	BOOL Create(HDC hDC, int iWidth, int iHeight, COLORREF crColor);
	void Draw(HDC hDC, int x, int y, BOOL bTrans = FALSE, COLORREF crTransColor = RGB(255, 0, 255));
	int GetWidth() const;
	int GetHeight() const;
};