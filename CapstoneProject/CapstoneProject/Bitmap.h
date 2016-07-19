/************************************************************************
Program:		CapstoneProject
Author:			Michael Morrison
Class:			Bitmap
Instructor:		Dan Randall
Date:			18 July 2016
Description:	GameEngine hides all the Windows specific code so you can
				focus on the game code.  Code is used from the book:
				"Beginning Game Programming" by Michael Morrison.
				No need to reinvent the wheel.
Input:
Output:

Compilation instructions:
Usage:
Known bugs/missing features:

Modifications:
Date                Comment
----    ------------------------------------------------
************************************************************************/
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
	void Draw(HDC hDC, int x, int y);
	void Draw(HDC hDC, int x, int y, BOOL bTrans = FALSE, COLORREF crTransColor = RGB(255, 0, 255));
	int GetWidth() const
	{
		return m_iWidth;
	};
	int GetHeight() const
	{
		return m_iHeight;
	};
};