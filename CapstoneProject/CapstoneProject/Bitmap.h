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

/*! \brief Takes a bitmap and turns it into a Bitmap object that will be drawn to the screen.
 *
 *  There are four different types of constructors used to create a Bitmap object. You can draw the bitmap with or without transparency.
 *  Also allows only a part of a Bitmap to be drawn. This can be use full if you have 'frames' that could allow animation or if you want
 *  to just use a tilesheet for several images.
 */
class Bitmap
{
protected:
	HBITMAP		m_hBitmap; ///< The handle to the bitmap and its copy of image bits
	int			m_iWidth; ///< The width in pixels of the bitmap
	int			m_iHeight; ///< The height in pixels of the bitmpa

	/// A helper fuction that deletes the Bitmap object and releases the handle from memory
	void Free();

public:
    /// Empty contructor that sets width and height to 0, and handle to NULL.
	Bitmap();
    
    /// Constructor that 
    /// @param hDC The handle to the screen context device
    /// @param szFileName The file of the bitmap the Bitmap object will be created from
	Bitmap(HDC, LPTSTR);
    
    /// Constructor that
    /// @param hDC The handle to the screen context device
    /// @param uiResID The ID of the bitmap from the resource file
    /// @param hInstance
	Bitmap(HDC, UINT, HINSTANCE);
    
    /// Constructor that
    /// @param hDC The handle to the screen context device
    /// @param iWidth
    /// @param iHeight
    /// @param crColor
	Bitmap(HDC, int, int, COLORREF crColor = RGB(0, 0, 0));
    
    /// A destructor that calls the Free() helper fuction to delete the object.
	virtual ~Bitmap();

	/// Used to update the object with bitmap info if empty constructor was used.
    /// @param hDC The handle to the screen context device
    /// @param szFileName The file of the bitmap the Bitmap object will be created from
	bool Create(HDC, LPTSTR);
    
    /// Used to update the object with bitmap info if empty constructor was used.
    /// @param hDC The handle to the screen context device
    /// @param uiResID The ID of the bitmap from the resource file
    /// @param hInstance 
	bool Create(HDC, UINT, HINSTANCE);
    
    /// Used to update the object with bitmap info if empty constructor was used.
    /// @param hDC The handle to the screen context device
    /// @param iWidth
    /// @param iHeight
    /// @param crColor
	bool Create(HDC, int, int, COLORREF);
    
    /// Draws the bitmap to the screen
    /// @param hDC The handle to the screen context the bitmap will be drawn on 
    /// @param X The X coordinate of the screen where to start drawing the bitmap
    /// @param Y The Y coordinate of the screen where to start drawing the bitmap
    /// @param bTrans If true, the bitmap has transparency. Default is no transparency
    /// @param crTransColor The color that will not be drawn to the screen to give transparency
	void Draw(HDC, int, int, bool bTrans = false, COLORREF crTransColor = RGB(255, 0, 255));
    
    /// Returns the width of the bitmap
	int GetWidth() const;
    
    /// Returns the height of the bitmap
	int GetHeight() const;
    
    /// Only draws part of a bitmap to the screen.  Can be used for tilesheets or animation frames.
    /// @param hDC The handle to the screen context the bitmap will be drawn on 
    /// @param X The X coordinate of the screen where to start drawing the bitmap
    /// @param Y The Y coordinate of the screen where to start drawing the bitmap
    /// @param xPart The X pixel of the bitmap to start drawing
    /// @param yPart The Y pixel of the bitmap to start drawing
    /// @param wPart The width in pixels used to draw from xPart
    /// @param hPart The height in pixels used to draw from yPart
    /// @param bTrans If true, the bitmap has transparency. Default is no transparency
    /// @param crTransColor The color that will not be drawn to the screen to give transparency 
	void DrawPart(HDC, int, int, int, int, int, int, BOOL, COLORREF);
};