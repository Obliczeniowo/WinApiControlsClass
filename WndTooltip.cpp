#include "wndtooltip.h"

WndTooltip::WndTooltip(LPCTSTR lpWindowName, HWND hWndParent, HINSTANCE hInstance){
	createWindow( lpWindowName, ws::window::ws_popup | ws::tooltip::tts_noprefix | ws::tooltip::tts_alwaystip, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hWndParent, NULL, hInstance, NULL);
	SetWindowPos( hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE );

	addTool(hWndParent, getParentWindow());
	setMaxWidth(200);
	addWmNotification(TTN_GETDISPINFO, new OnWmNotifyGetDispInfo(hWnd, lpWindowName));
}

void WndTooltip::createWindow(LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam){
	if(hWnd){
		DestroyWindow(hWnd);
	}

	hWnd = CreateWindowEx(ws::window_ex::ws_ex_topmost, TOOLTIPS_CLASS, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

void WndTooltip::addTool(HWND hWndParent, HWND hwndGl){
	TOOLINFO ti;
	ti.cbSize	= sizeof(TOOLINFO);
	ti.uFlags	= TTF_SUBCLASS | TTF_IDISHWND;
	ti.uId		= (UINT_PTR) hWndParent;
	ti.hwnd		= hwndGl;
	ti.hinst	= NULL;
	ti.lpszText	= LPSTR_TEXTCALLBACK;

	RECT rect;

	GetClientRect(hWndParent, &rect);

	ti.rect.left = rect.left;
	ti.rect.top = rect.top;
	ti.rect.right = rect.right;
	ti.rect.bottom = rect.bottom;

	SendMessage(hWnd, TTM_ADDTOOL, 0, (LPARAM) &ti);
}