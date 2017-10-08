#ifndef STANDARD_CONTROLS_H

#define STANDARD_CONTROLS_H

#include <windows.h>
#include <string>
#include <Commctrl.h>
#include <map>

namespace wndenum{
	enum imageType {
		bitmap		= IMAGE_BITMAP,
		cursor		= IMAGE_CURSOR,
		enhmetafile	= IMAGE_ENHMETAFILE,
		icon		= IMAGE_ICON
	};
}

namespace ws{
	namespace window{
		enum style{
			ws_border					= WS_BORDER,				// Creates a window that has a thin-line border.
			ws_caption					= WS_CAPTION,				// Creates a window that has a title bar (includes the WS_BORDER style).
			ws_child					= WS_CHILD,					// Creates a child window. A window with this style cannot have a menu bar. This style cannot be used with the WS_POPUP style.
			ws_clipchildren				= WS_CLIPCHILDREN,			// Excludes the area occupied by child windows when drawing occurs within the parent window. This style is used when creating the parent window.
			ws_clipsiblines				= WS_CLIPSIBLINGS,			// Clips child windows relative to each other; that is, when a particular child window receives a WM_PAINT message, the WS_CLIPSIBLINGS style clips all other overlapping child windows out of the region of the child window to be updated. If WS_CLIPSIBLINGS is not specified and child windows overlap, it is possible, when drawing within the client area of a child window, to draw within the client area of a neighboring child window.
			ws_disabled					= WS_DISABLED,				// Creates a window that is initially disabled. A disabled window cannot receive input from the user. To change this after a window has been created, use EnableWindow. 
			ws_dlgframe					= WS_DLGFRAME,				// Creates a window that has a border of a style typically used with dialog boxes. A window with this style cannot have a title bar.
			ws_group					= WS_GROUP,					// Specifies the first control of a group of controls. The group consists of this first control and all controls defined after it, up to the next control with the WS_GROUP style. The first control in each group usually has the WS_TABSTOP style so that the user can move from group to group. The user can subsequently change the keyboard focus from one control in the group to the next control in the group by using the direction keys.
																	// You can turn this style on and off to change dialog box navigation. To change this style after a window has been created, use SetWindowLong.
			ws_hscrollbar				= WS_HSCROLL,				// Creates a window that has a horizontal scroll bar.
			ws_maximize					= WS_MAXIMIZE,				// Creates a window that is initially maximized.
			ws_maximizebox				= WS_MAXIMIZEBOX,			// Creates a window that has a maximize button. Cannot be combined with the WS_EX_CONTEXTHELP style. The WS_SYSMENU style must also be specified. 
			ws_iminimize				= WS_MINIMIZE,				// Creates a window that is initially minimized. Same as the WS_ICONIC style.
			ws_minimizebox				= WS_MINIMIZEBOX,			// Creates a window that has a minimize button. Cannot be combined with the WS_EX_CONTEXTHELP style. The WS_SYSMENU style must also be specified. 
			ws_overlapped				= WS_OVERLAPPED,			// Creates an overlapped window. An overlapped window has a title bar and a border. Same as the WS_TILED style.
			ws_overlappedwindow			= WS_OVERLAPPEDWINDOW,		// Creates an overlapped window with the WS_OVERLAPPED, WS_CAPTION, WS_SYSMENU, WS_THICKFRAME, WS_MINIMIZEBOX, and WS_MAXIMIZEBOX styles. Same as the WS_TILEDWINDOW style. 
			ws_popup					= WS_POPUP,					// Creates a pop-up window. This style cannot be used with the WS_CHILD style.
			ws_popupwindow				= WS_POPUPWINDOW,			// Creates a pop-up window with WS_BORDER, WS_POPUP, and WS_SYSMENU styles. The WS_CAPTION and WS_POPUPWINDOW styles must be combined to make the window menu visible.
			ws_sizebox					= WS_SIZEBOX,				// Creates a window that has a sizing border. Same as the WS_THICKFRAME style.
			ws_sysmenu					= WS_SYSMENU,				// Creates a window that has a window menu on its title bar. The WS_CAPTION style must also be specified.
			ws_tabstop					= WS_TABSTOP,				// Specifies a control that can receive the keyboard focus when the user presses the TAB key. Pressing the TAB key changes the keyboard focus to the next control with the WS_TABSTOP style. 
																	// You can turn this style on and off to change dialog box navigation. To change this style after a window has been created, use SetWindowLong.
			ws_thickframe				= WS_THICKFRAME,			// Creates a window that has a sizing border. Same as the WS_SIZEBOX style.
			ws_visible					= WS_VISIBLE,				// Creates a window that is initially visible.
																	// This style can be turned on and off by using ShowWindow or SetWindowPos.
			ws_vscrollbar				= WS_VSCROLL				// Creates a window that has a vertical scroll bar.
		};
	}

	namespace window_ex{
		enum ex_style{
			ws_ex_acceptfiles			= WS_EX_ACCEPTFILES,		// Specifies that a window created with this style accepts drag-drop files.
			ws_ex_appwindow				= WS_EX_APPWINDOW,			// Forces a top-level window onto the taskbar when the window is visible. 
			ws_ex_clientedge			= WS_EX_CLIENTEDGE,			// Specifies that a window has a border with a sunken edge.
			ws_ex_composited			= WS_EX_COMPOSITED,			// Windows XP: Paints all descendants of a window in bottom-to-top painting order using double-buffering. For more information, see Remarks. This cannot be used if the window has a class style of either CS_OWNDC or CS_CLASSDC. 
			ws_ex_contexthelp			= WS_EX_CONTEXTHELP,		// Includes a question mark in the title bar of the window. When the user clicks the question mark, the cursor changes to a question mark with a pointer. If the user then clicks a child window, the child receives a WM_HELP message. The child window should pass the message to the parent window procedure, which should call the WinHelp function using the HELP_WM_HELP command. The Help application displays a pop-up window that typically contains help for the child window.
																	// WS_EX_CONTEXTHELP cannot be used with the WS_MAXIMIZEBOX or WS_MINIMIZEBOX styles.
			ws_ex_controlparent			= WS_EX_CONTROLPARENT,		// The window itself contains child windows that should take part in dialog box navigation. If this style is specified, the dialog manager recurses into children of this window when performing navigation operations such as handling the TAB key, an arrow key, or a keyboard mnemonic.
			ws_ex_dlgmodalframe			= WS_EX_DLGMODALFRAME,		// Creates a window that has a double border; the window can, optionally, be created with a title bar by specifying the WS_CAPTION style in the dwStyle parameter.
			ws_ex_layed					= WS_EX_LAYERED,			// Windows 2000/XP: Creates a layered window. Note that this cannot be used for child windows. Also, this cannot be used if the window has a class style of either CS_OWNDC or CS_CLASSDC. 
			ws_ex_layoutrtl				= WS_EX_LAYOUTRTL,			// Arabic and Hebrew versions of Windows 98/Me, Windows 2000/XP: Creates a window whose horizontal origin is on the right edge. Increasing horizontal values advance to the left. 
			ws_ex_left					= WS_EX_LEFT,				// Creates a window that has generic left-aligned properties. This is the default.
			ws_ex_leftscrollbar			= WS_EX_LEFTSCROLLBAR,		// If the shell language is Hebrew, Arabic, or another language that supports reading order alignment, the vertical scroll bar (if present) is to the left of the client area. For other languages, the style is ignored.
			ws_ex_ltrreading			= WS_EX_LTRREADING,			// The window text is displayed using left-to-right reading-order properties. This is the default.
			ws_ex_mdichild				= WS_EX_MDICHILD,			// Creates a multiple-document interface (MDI) child window.
			ws_ex_noactive				= WS_EX_NOACTIVATE,			// Windows 2000/XP: A top-level window created with this style does not become the foreground window when the user clicks it. The system does not bring this window to the foreground when the user minimizes or closes the foreground window. 
																	//	To activate the window, use the SetActiveWindow or SetForegroundWindow function.
																	// The window does not appear on the taskbar by default. To force the window to appear on the taskbar, use the WS_EX_APPWINDOW style.
			ws_ex_noinheritlayout		= WS_EX_NOINHERITLAYOUT,	// Windows 2000/XP: A window created with this style does not pass its window layout to its child windows.
			ws_ex_noparentnotify		= WS_EX_NOPARENTNOTIFY,		// Specifies that a child window created with this style does not send the WM_PARENTNOTIFY message to its parent window when it is created or destroyed.
			ws_ex_overlappedwindow		= WS_EX_OVERLAPPEDWINDOW,	// Combines the WS_EX_CLIENTEDGE and WS_EX_WINDOWEDGE styles.
			ws_ex_palettewindow			= WS_EX_PALETTEWINDOW,		// Combines the WS_EX_WINDOWEDGE, WS_EX_TOOLWINDOW, and WS_EX_TOPMOST styles.
			ws_ex_right					= WS_EX_RIGHT,				// The window has generic "right-aligned" properties. This depends on the window class. This style has an effect only if the shell language is Hebrew, Arabic, or another language that supports reading-order alignment; otherwise, the style is ignored.
																	// Using the WS_EX_RIGHT style for static or edit controls has the same effect as using the SS_RIGHT or ES_RIGHT style, respectively. Using this style with button controls has the same effect as using BS_RIGHT and BS_RIGHTBUTTON styles. 
			ws_ex_rightscrollbar		= WS_EX_RIGHTSCROLLBAR,		// Vertical scroll bar (if present) is to the right of the client area. This is the default.
			ws_ex_rtlreading			= WS_EX_RTLREADING,			// If the shell language is Hebrew, Arabic, or another language that supports reading-order alignment, the window text is displayed using right-to-left reading-order properties. For other languages, the style is ignored.
			ws_ex_staticedge			= WS_EX_STATICEDGE,			// Creates a window with a three-dimensional border style intended to be used for items that do not accept user input.
			ws_ex_toolwindow			= WS_EX_TOOLWINDOW,			// Creates a tool window; that is, a window intended to be used as a floating toolbar. A tool window has a title bar that is shorter than a normal title bar, and the window title is drawn using a smaller font. A tool window does not appear in the taskbar or in the dialog that appears when the user presses ALT+TAB. If a tool window has a system menu, its icon is not displayed on the title bar. However, you can display the system menu by right-clicking or by typing ALT+SPACE. 
			ws_ex_topmost				= WS_EX_TOPMOST,			// Specifies that a window created with this style should be placed above all non-topmost windows and should stay above them, even when the window is deactivated. To add or remove this style, use the SetWindowPos function.
			ws_ex_transparent			= WS_EX_TRANSPARENT,		// Specifies that a window created with this style should not be painted until siblings beneath the window (that were created by the same thread) have been painted. The window appears transparent because the bits of underlying sibling windows have already been painted.
																	// To achieve transparency without these restrictions, use the SetWindowRgn function.
			ws_ex_windowedge			= WS_EX_WINDOWEDGE			// Specifies that a window has a border with a raised edge.
		};
	}
}

class INotificationCommand {
public:
	virtual void notify() = 0;
	virtual ~INotificationCommand(){}
};

class IControlWindow;

typedef void (*notificationFuPtr)(IControlWindow*, LPVOID);

class IControlWindow{
protected:
	HWND hWnd;
	bool destroy;
	std::map<int, INotificationCommand*> notificationsMap;
public:
	IControlWindow() : hWnd(NULL), destroy(true){};
	virtual void createWindow(LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) = 0;

	virtual ~IControlWindow(){
		if(hWnd && destroy){
			DestroyWindow(hWnd);
			hWnd = NULL;
		}

		if(!notificationsMap.empty()){
			for(std::map<int, INotificationCommand*>::iterator i = notificationsMap.begin(); i != notificationsMap.end(); i++){
				if(i->second){
					delete i->second;
				}
			}
		}
	};

	operator HWND(){
		return hWnd;
	}

	std::string getWindowText() const{
		std::string wndText;
		if(hWnd){
			int length = GetWindowTextLength(hWnd);
			if(length > 0){
				char *text = new char[length + 1];

				GetWindowText(hWnd, text, length + 1);

				wndText += text;

				delete text;
			}
		}

		return wndText;
	}

	void setWindowText(std::string windowText){
		SetWindowText(hWnd, windowText.c_str());
	}

	void setWindowText(LPCSTR windowText){
		SetWindowText(hWnd, windowText);
	}

	void getWindowPos(POINT &p) const {
		RECT rect;
		GetWindowRect(hWnd, &rect);
		p.x = rect.left;
		p.y = rect.top;
	}

	void setWindowPos(int x, int y){
		SetWindowPos(hWnd, NULL, x, y, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	}

	void getWindowSize(SIZE &wndSize) const {
		wndSize.cx = wndSize.cy = -1;
		RECT wndRect;
		GetWindowRect(hWnd, &wndRect);
		wndSize.cx = wndRect.right - wndRect.left;
		wndSize.cy = wndRect.bottom - wndRect.top;
	}

	void setWindowSize(UINT width, UINT height){
		SetWindowPos(hWnd, NULL, 0, 0, width, height, SWP_NOMOVE|SWP_NOZORDER);
	}

	void hideWindow(){
		LONG style = (LONG) GetWindowLongPtr(hWnd, GWL_STYLE) ^ WS_VISIBLE;
		SetWindowLongPtr(hWnd, GWL_STYLE, style);
	}

	void showWindow(){
		LONG style = (LONG) GetWindowLongPtr(hWnd, GWL_STYLE) | WS_VISIBLE;
		SetWindowLong(hWnd, GWL_STYLE, style);
	}

	inline HINSTANCE getHinstance() const {
		return (HINSTANCE) GetWindowLongPtr(hWnd, GWL_HINSTANCE);
	}

	inline HWND getParentWindow() const {
		return (HWND) GetWindowLongPtr(hWnd, GWL_HWNDPARENT);
	}

	inline UINT getWindowId() const {
		return (UINT)GetWindowLongPtr(hWnd, GWL_ID);
	}

	inline LONG getWindowStyleEx() const {
		return (LONG) GetWindowLongPtr(hWnd, GWL_EXSTYLE);
	}

	inline LONG getWindowStyle() const {
		return (LONG) GetWindowLongPtr(hWnd, GWL_STYLE);
	}

	inline void setWindowStyle(LONG style){
		SetWindowLongPtr(hWnd, GWL_STYLE, style);
	}

	inline void setWindowStyleEx(LONG styleEx){
		SetWindowLongPtr(hWnd, GWL_EXSTYLE, styleEx);
	}

	inline void setWindowStyle(bool add, LONG style){
		LONG cstyle = (LONG)GetWindowLongPtr(hWnd, GWL_STYLE);
		add ? SetWindowLongPtr(hWnd, GWL_STYLE, cstyle | style) : SetWindowLongPtr(hWnd, GWL_STYLE, (cstyle & style) ? cstyle ^ style : cstyle);
	}

	inline HCURSOR setWindowCursor(HCURSOR hCursor){
		return (HCURSOR) SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG_PTR) hCursor);
	}

	inline HICON setWindowIcon(HICON hIcon){
		return (HICON) SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG_PTR) hIcon);
	}

	inline HCURSOR getWindowCursor(){
		return (HCURSOR) GetClassLongPtr(hWnd, GCLP_HCURSOR);
	}

	inline HICON getWindowIcon(){
		return (HICON) GetClassLongPtr(hWnd, GCLP_HICON);
	}

	inline WNDPROC getWndProc(){
		return (WNDPROC) GetWindowLongPtr(hWnd, GWLP_WNDPROC);
	}

	inline void setWndProc(WNDPROC wndproc){
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)wndproc);
	}

	std::string getWindowClassName(){
		char classname[255];
		GetClassName(hWnd, classname, 255);

		return std::string(classname);
	}

	HBRUSH getWindowBrush(){
		return (HBRUSH) GetClassLongPtr(hWnd, GCLP_HBRBACKGROUND);
	}

	HBRUSH setWindowBrush(HBRUSH hBrush){
		return (HBRUSH) SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR) hBrush);
	}

	enum exWindowStyle{
		acceptfiles			= WS_EX_ACCEPTFILES,
		appwindow			= WS_EX_APPWINDOW,
		clientedge			= WS_EX_CLIENTEDGE,
		composited			= WS_EX_COMPOSITED,
		contexthelp			= WS_EX_CONTEXTHELP,
		controlparent		= WS_EX_CONTROLPARENT,
		dlgmodalframe		= WS_EX_DLGMODALFRAME,
		layed				= WS_EX_LAYERED,
		layoutrtl			= WS_EX_LAYOUTRTL,
		left				= WS_EX_LEFT,
		leftscrollbar		= WS_EX_LEFTSCROLLBAR,
		ltrreading			= WS_EX_LTRREADING,
		mdichild			= WS_EX_MDICHILD,
		noactivate			= WS_EX_NOACTIVATE,
		noinheritlayout		= WS_EX_NOINHERITLAYOUT,
		noparentnotify		= WS_EX_NOPARENTNOTIFY,
		overlappedwindow	= WS_EX_OVERLAPPEDWINDOW,
		palettewindow		= WS_EX_PALETTEWINDOW,
		right				= WS_EX_RIGHT,
		rightscrollbar		= WS_EX_RIGHTSCROLLBAR,
		rtlreading			= WS_EX_RTLREADING,
		staticedge			= WS_EX_STATICEDGE,
		toolwindow			= WS_EX_TOOLWINDOW,
		topmost				= WS_EX_TOPMOST,
		transparent			= WS_EX_TRANSPARENT,
		windowedge			= WS_EX_WINDOWEDGE
	};

	inline void setWindowStyleEx(exWindowStyle styleEx){
		SetWindowLongPtr(hWnd, GWL_EXSTYLE, styleEx);
	}

	inline void setFont(HFONT font){
		SendMessage(hWnd, WM_SETFONT, (WPARAM)font, TRUE);
	}

	inline HWND setFocus(){
		return SetFocus(hWnd);
	}

	inline BOOL enableWindow(BOOL enable){
		return EnableWindow(hWnd, enable);
	}

	inline BOOL isWindowEnabled() const {
		return IsWindowEnabled(hWnd);
	}

	inline BOOL isWindowVisible() const {
		return IsWindowVisible(hWnd);
	}

	bool addNotification(int notify, INotificationCommand* nc) {
		notificationsMap[notify] = nc;
		return true;
	}

	bool notify(HWND hwndCtl, int wID, int wNotifyCode){
		if(hwndCtl == hWnd){
			std::map<int, INotificationCommand*>::iterator notifyFu = notificationsMap.find(wNotifyCode);
			if(notifyFu != notificationsMap.end()){
				if(notifyFu->second){
					notifyFu->second->notify();
				}
			}
			return true;
		}
		return false;
	}

	void sendNotificationCommand(int notify){
		SendMessage(GetParent(hWnd), WM_COMMAND, MAKEWPARAM((UINT)getWindowId(), notify), (LPARAM)hWnd);
	}
};

#endif