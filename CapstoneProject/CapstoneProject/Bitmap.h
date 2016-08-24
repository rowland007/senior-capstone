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
21Aug16	Added DrawPart fuction to handle frames for Sprites
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
	Bitmap(HDC, LPTSTR);
	Bitmap(HDC, UINT, HINSTANCE);
	Bitmap(HDC, int, int, COLORREF crColor = RGB(0, 0, 0));
	virtual ~Bitmap();

	//General Methods
	bool Create(HDC, LPTSTR);
	bool Create(HDC, UINT, HINSTANCE);
	bool Create(HDC, int, int, COLORREF);
	void Draw(HDC, int, int, bool bTrans = false, COLORREF crTransColor = RGB(255, 0, 255));
	int GetWidth() const;
	int GetHeight() const;
	void DrawPart(HDC, int, int, int, int, int, int, BOOL, COLORREF);
};