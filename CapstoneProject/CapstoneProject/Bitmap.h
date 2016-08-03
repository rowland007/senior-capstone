/************************************************************************
Program:		CapstoneProject
Author:			Randall Rowland
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
2Aug16	Changed BOOL to bool and FALSE to false.
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
	bool Create(HDC hDC, LPTSTR szFilename);
	bool Create(HDC hDC, UINT uiResID, HINSTANCE hInstance);
	bool Create(HDC hDC, int iWidth, int iHeight, COLORREF crColor);
	void Draw(HDC hDC, int x, int y, bool bTrans = false, COLORREF crTransColor = RGB(255, 0, 255));
	int GetWidth() const;
	int GetHeight() const;
};