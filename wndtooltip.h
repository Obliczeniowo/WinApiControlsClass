#ifndef WNDTOOLTIP_H
#define WNDTOOLTIP_H

#include "ex_controls_windows.h"

namespace ws{
	namespace tooltip{
		enum tt_style{
			tts_alwaystip		= TTS_ALWAYSTIP,		// Indicates that the tooltip control appears when the cursor is on a tool, even if the tooltip control's owner window is inactive. Without this style, the tooltip appears only when the tool's owner window is active.
			tts_ballon			= TTS_BALLOON,			// Version 5.80. Indicates that the tooltip control has the appearance of a cartoon "balloon," with rounded corners and a stem pointing to the item. 
			tts_close			= TTS_CLOSE,			// Displays a Close button on the tooltip. Valid only when the tooltip has the TTS_BALLOON style and a title; see TTM_SETTITLE.
			tts_noanimate		= TTS_NOANIMATE,		// Version 5.80. Disables sliding tooltip animation on Windows 98 and Windows 2000 systems. This style is ignored on earlier systems.
			tts_nofade			= TTS_NOFADE,			// Version 5.80. Disables fading tooltip animation. 
			tts_noprefix		= TTS_NOPREFIX,			// Prevents the system from stripping ampersand characters from a string or terminating a string at a tab character. Without this style, the system automatically strips ampersand characters and terminates a string at the first tab character. This allows an application to use the same string as both a menu item and as text in a tooltip control.
			tts_usevisalstyle	= TTS_USEVISUALSTYLE	//  Uses themed hyperlinks. The theme will define the styles for any links in the tooltip. This style always requires TTF_PARSELINKS to be set. 
 		};
	}
}

class WndTooltip : public IControlWindow, public IWmNotify {
	
	class OnWmNotifyGetDispInfo : public IWmNotificationCommand{
	public:
		HWND from;
		char* toolTipText;

		OnWmNotifyGetDispInfo(HWND from, const char* toolTipText) : from(from){
			this->toolTipText = new char[strlen(toolTipText) + 1];
			strcpy(this->toolTipText, toolTipText);
		}

		virtual void notify(LPARAM lParam){
			LPNMTTDISPINFO lpnmtdi =(LPNMTTDISPINFO)lParam;

			lpnmtdi->lpszText	= toolTipText;
			lpnmtdi->hinst		= NULL;
			lpnmtdi->uFlags		= TTF_DI_SETITEM;
		}

		virtual ~OnWmNotifyGetDispInfo(){
			if(toolTipText)
				delete toolTipText;
		}
	};
public:
	WndTooltip(LPCTSTR lpWindowName, HWND hWndParent, HWND hwndGl, HINSTANCE hInstance){
		createWindow( lpWindowName, ws::window::ws_popup | ws::tooltip::tts_noprefix | ws::tooltip::tts_alwaystip, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hWndParent, NULL, hInstance, NULL);
		SetWindowPos( hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE );

		addTool(lpWindowName, hWndParent, hwndGl);
		setMaxWidth(200);
		addWmNotification(TTN_GETDISPINFO, new OnWmNotifyGetDispInfo(hWnd, lpWindowName));
	}
	
	virtual void createWindow(LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam){
		if(hWnd){
			DestroyWindow(hWnd);
		}

		hWnd = CreateWindowEx(ws::window_ex::ws_ex_topmost, TOOLTIPS_CLASS, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}

	virtual bool wmNotify(LPARAM lParam){
		return IWmNotify::wmNotify(lParam, hWnd);
	}

	void addTool(std::string tooltiptext, HWND hWndParent, HWND hwndGl){
		TOOLINFO ti;
		ti.cbSize	= sizeof(TOOLINFO);
		ti.uFlags	= TTF_SUBCLASS | TTF_IDISHWND;
		ti.uId		= (UINT_PTR) hWndParent;
		ti.hwnd		= hwndGl;
		ti.hinst	= NULL;
		ti.lpszText	= LPSTR_TEXTCALLBACK;//(LPSTR) tooltiptext.c_str();

		RECT rect;

		GetClientRect(hWndParent, &rect);

		ti.rect.left = rect.left;
		ti.rect.top = rect.top;
		ti.rect.right = rect.right;
		ti.rect.bottom = rect.bottom;

		SendMessage(hWnd, TTM_ADDTOOL, 0, (LPARAM) &ti);
	}

	inline void setBallonTooltip(bool ballon){
		setWindowStyle(ballon, ws::tooltip::tts_ballon);
	}

	inline void setTextColor(COLORREF color){
		SendMessage(hWnd, TTM_SETTIPTEXTCOLOR, (WPARAM)color, 0);
	}

	inline void setBackgroundColor(COLORREF color){
		SendMessage(hWnd, TTM_SETTIPBKCOLOR, (WPARAM)color, 0);
	}

	inline void setMaxWidth(int width){
		SendMessage(hWnd, TTM_SETMAXTIPWIDTH, 0, width);
	}

	inline void setTitle(std::string title){
		SendMessage(hWnd, TTM_SETTITLE, 1,(LPARAM) title.c_str());
	}
};

#endif