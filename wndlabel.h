#ifndef WNDLABEL_H
#define WNDLABEL_H

#include "controls_windows.h"

namespace ws{
	namespace label{
		enum lb_style{
			ss_bitmap			= SS_BITMAP,			// Specifies that a bitmap is to be displayed in the static control. The text is the name of a bitmap (not a filename) defined elsewhere in the resource file. The style ignores the nWidth and nHeight parameters; the control automatically sizes itself to accommodate the bitmap. 
			ss_blackframe		= SS_BLACKFRAME,		// Specifies a box with a frame drawn in the same color as the window frames. This color is black in the default color scheme. 
			ss_blackrect		= SS_BLACKRECT,			// Specifies a rectangle filled with the current window frame color. This color is black in the default color scheme. 
			ss_center			= SS_CENTER,			// Specifies a simple rectangle and centers the text in the rectangle. The text is formatted before it is displayed. Words that extend past the end of a line are automatically wrapped to the beginning of the next centered line. Words that are longer than the width of the control are truncated. 
			ss_centerimage		= SS_CENTERIMAGE,		// Specifies that a bitmap is centered in the static control that contains it. The control is not resized, so that a bitmap too large for the control will be clipped. If the static control contains a single line of text, the text is centered vertically in the client area of the control. 
														// Microsoft Windows XP: This style bit no longer results in unused portions of the control being filled with the color of the top left pixel of the bitmap or icon. Unused portions of the control will remain the background color.
			ss_editcontrol		= SS_EDITCONTROL,		// Windows 2000: Specifies that the static control duplicates the text-displaying characteristics of a multiline edit control. Specifically, the average character width is calculated in the same manner as with an edit control, and the function does not display a partially visible last line. 
			ss_endellipsis		= SS_ENDELLIPSIS,		// Microsoft Windows NT or later: If the end of a string does not fit in the rectangle, it is truncated and ellipses are added. If a word that is not at the end of the string goes beyond the limits of the rectangle, it is truncated without ellipses. Compare with SS_PATHELLIPSIS and SS_WORDELLIPSIS. 
			ss_enhmetafile		= SS_ENHMETAFILE,		// Specifies that an enhanced metafile is to be displayed in the static control. The text is the name of a metafile. An enhanced metafile static control has a fixed size; the metafile is scaled to fit the static control's client area. 
			ss_etchedframe		= SS_ETCHEDFRAME,		// Draws the frame of the static control using the EDGE_ETCHED edge style. For more information, see the DrawEdge function. 
			ss_etchedhorz		= SS_ETCHEDHORZ,		// Draws the top and bottom edges of the static control using the EDGE_ETCHED edge style. For more information, see the DrawEdge function. 
			ss_etchedvert		= SS_ETCHEDVERT,		// Draws the left and right edges of the static control using the EDGE_ETCHED edge style. For more information, see the DrawEdge function. 
			ss_grayframe		= SS_GRAYFRAME,			// Specifies a box with a frame drawn with the same color as the screen background (desktop). This color is gray in the default color scheme. 
			ss_grayrect			= SS_GRAYRECT,			// Specifies a rectangle filled with the current screen background color. This color is gray in the default color scheme. 
			ss_icon				= SS_ICON,				// Specifies an icon to be displayed in the dialog box. If the control is created as part of a dialog box, the text is the name of an icon (not a filename) defined elsewhere in the resource file. If the control is created via CreateWindow or a related function, the text is the name of an icon (not a filename) defined in the resource file associated with the module specified by the hInstance parameter to CreateWindow. 
														// The icon can be an animated cursor. 
														// The style ignores the CreateWindow parameters nWidth and nHeight; the control automatically sizes itself to accommodate the icon. As it uses the LoadIcon function, the SS_ICON style can load only icons of dimensions SM_CXICON and SM_CYICON. This restriction can be bypassed by using the SS_REALSIZEIMAGE style in addition to SS_ICON. 
														// If an icon cannot be loaded through LoadIcon, an attempt is made to load the specified resource as a cursor using LoadCursor. If that too fails, an attempt is made to load from the device driver using LoadImage.  
			ss_left				= SS_LEFT,				// Specifies a simple rectangle and left-aligns the text in the rectangle. The text is formatted before it is displayed. Words that extend past the end of a line are automatically wrapped to the beginning of the next left-aligned line. Words that are longer than the width of the control are truncated. 
			ss_leftnowordwrap	= SS_LEFTNOWORDWRAP,	// Specifies a simple rectangle and left-aligns the text in the rectangle. Tabs are expanded, but words are not wrapped. Text that extends past the end of a line is clipped. 
			ss_noprefix			= SS_NOPREFIX,			// Prevents interpretation of any ampersand (&) characters in the control's text as accelerator prefix characters. These are displayed with the ampersand removed and the next character in the string underlined. This static control style may be included with any of the defined static controls. You can combine SS_NOPREFIX with other styles. This can be useful when filenames or other strings that may contain an ampersand (&) must be displayed in a static control in a dialog box. 
			ss_notify			= SS_NOTIFY,			// Sends the parent window STN_CLICKED, STN_DBLCLK, STN_DISABLE, and STN_ENABLE notification messages when the user clicks or double-clicks the control. 
			ss_ownerdraw		= SS_OWNERDRAW,			// Specifies that the owner of the static control is responsible for drawing the control. The owner window receives a WM_DRAWITEM message whenever the control needs to be drawn. 
			ss_pathellipsis		= SS_PATHELLIPSIS,		// Windows NT or later: Replaces characters in the middle of the string with ellipses so that the result fits in the specified rectangle. If the string contains backslash (\) characters, SS_PATHELLIPSIS preserves as much as possible of the text after the last backslash. Compare with SS_ENDELLIPSIS and SS_WORDELLIPSIS. 
			ss_realsizecontrol	= SS_REALSIZECONTROL,	// Windows XP or later: Adjusts the bitmap to fit the size of the static control. For example, changing the locale can change the system font, and thus controls might be resized. If a static control had a bitmap, the bitmap would no longer fit the control. This style bit dictates automatic redimensioning of bitmaps to fit their controls. 
														// If SS_CENTERIMAGE is specified, the bitmap or icon is centered (and clipped if needed). If SS_CENTERIMAGE is not specified, the bitmap or icon is stretched or shrunk.
														// Note that the redimensioning in the two axes are independent, and the result may have a changed aspect ratio. 
														// Compare with SS_REALSIZEIMAGE.
			ss_realsizeimage	= SS_REALSIZEIMAGE,		// Specifies that the actual resource width is used and the icon is loaded using LoadImage. SS_REALSIZEIMAGE is always used in conjunction with SS_ICON. 
														// SS_REALSIZEIMAGE uses LoadImage, overriding the process normally followed under SS_ICON. It does not load cursors; if LoadImage fails, no further attempts to load are made. It uses the actual resource width. The static control is resized accordingly, but the icon remains aligned to the originally specified left and top edges of the control.
														// Note that if SS_CENTERIMAGE is also specified, the icon is centered within the control's space, which was specified using the CreateWindow parameters nWidth and nHeight.
														// Compare with SS_REALSIZECONTROL.
			ss_right			= SS_RIGHT,				// Specifies a simple rectangle and right-aligns the text in the rectangle. The text is formatted before it is displayed. Words that extend past the end of a line are automatically wrapped to the beginning of the next right-aligned line. Words that are longer than the width of the control are truncated. 
			ss_rightjust		= SS_RIGHTJUST,			// Specifies that the lower right corner of a static control with the SS_BITMAP or SS_ICON style is to remain fixed when the control is resized. Only the top and left sides are adjusted to accommodate a new bitmap or icon. 
			ss_simple			= SS_SIMPLE,			// Specifies a simple rectangle and displays a single line of left-aligned text in the rectangle. The text line cannot be shortened or altered in any way. Also, if the control is disabled, the control does not gray its text. 
			ss_sunken			= SS_SUNKEN,			// Draws a half-sunken border around a static control. 
			ss_typemask			= SS_TYPEMASK,			// Windows 2000: A composite style bit that results from using the OR operator on SS_* style bits. Can be used to mask out valid SS_* bits from a given bitmask. Note that this is out of date and does not correctly include all valid styles. Thus, you should not use this style. 
			ss_whiteframe		= SS_WHITEFRAME,		// Specifies a box with a frame drawn with the same color as the window background. This color is white in the default color scheme. 
			ss_whiterect		= SS_WHITERECT			// Specifies a rectangle filled with the current window background color. This color is white in the default color scheme. 
														// SS_WORDELLIPSIS Windows NT or later: Truncates any word that does not fit in the rectangle and adds ellipses. 
														// Compare with SS_ENDELLIPSIS and SS_PATHELLIPSIS.
 		};
	}
}

class WndLabel : public IControlWindow {
protected:
	WndLabel(HWND hWnd){
		this->hWnd = hWnd;
		destroy = false;
	}
public:
	enum notifications {
		clicked		= STN_CLICKED,
		doubleclick	= STN_DBLCLK,
		disable		= STN_DISABLE,
		enable		= STN_ENABLE
	};

	WndLabel(LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam){
		createWindow( lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}
	
	virtual void createWindow(LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam){
		if(hWnd){
			DestroyWindow(hWnd);
		}

		hWnd = CreateWindowEx(NULL, "STATIC", lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}

	inline HICON getIcon() const {
		return (HICON) SendMessage(hWnd, STM_GETICON, NULL, NULL);
	}

	inline HANDLE getImage(wndenum::imageType type) const {
		return (HANDLE) SendMessage(hWnd, STM_GETIMAGE, type, NULL);
	}

	inline HICON setIcon(HICON icon){
		return (HICON) SendMessage(hWnd, STM_SETICON, (WPARAM) icon, NULL);
	}

	inline HANDLE setImage(wndenum::imageType type, HANDLE imageHandle){
		return (HANDLE) SendMessage(hWnd, STM_SETIMAGE, (WPARAM) type, (LPARAM) imageHandle);
	}

	static WndLabel* fromWndHandle(HWND hWnd){
		char classname[255];
		GetClassName(hWnd, classname, 255);
		if(!strcmp(strlwr(classname), strlwr("static"))){
			return new WndLabel(hWnd);
		}
		return NULL;
	}
};

#endif