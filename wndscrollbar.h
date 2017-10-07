#ifndef WNDSCROLLBAR_H
#define WNDSCROLLBAR_H

#include "controls_windows.h"

namespace ws{
	namespace scrollbar{
		enum sb_style{
			sbs_bottomalign				= SBS_BOTTOMALIGN,				// Used with the SBS_HORZ style. The bottom edge of the scroll bar is aligned with the bottom edge of the rectangle specified in the Create member function. The scroll bar has the default height for system scroll bars.
			sbs_horizontal				= SBS_HORZ,						// Designates a horizontal scroll bar. If neither the SBS_BOTTOMALIGN nor SBS_TOPALIGN style is specified, the scroll bar has the height, width, and position given in the Create member function.
			sbs_leftalign				= SBS_LEFTALIGN,				// Used with the SBS_VERT style. The left edge of the scroll bar is aligned with the left edge of the rectangle specified in the Create member function. The scroll bar has the default width for system scroll bars.
			sbs_rightalign				= SBS_RIGHTALIGN,				// Used with the SBS_VERT style. The right edge of the scroll bar is aligned with the right edge of the rectangle specified in the Create member function. The scroll bar has the default width for system scroll bars.
			sbs_sizebox					= SBS_SIZEBOX,					// Designates a size box. If neither the SBS_SIZEBOXBOTTOMRIGHTALIGN nor SBS_SIZEBOXTOPLEFTALIGN style is specified, the size box has the height, width, and position given in the Create member function.
			sbs_sizeboxbottomrightalign	= SBS_SIZEBOXBOTTOMRIGHTALIGN,	// Used with the SBS_SIZEBOX style. The lower-right corner of the size box is aligned with the lower-right corner of the rectangle specified in the Create member function. The size box has the default size for system size boxes.
			sbs_sizeboxtopleftalign		= SBS_SIZEBOXTOPLEFTALIGN,		// Used with the SBS_SIZEBOX style. The upper-left corner of the size box is aligned with the upper-left corner of the rectangle specified in the Create member function. The size box has the default size for system size boxes.
			sbs_sizegrip				= SBS_SIZEGRIP,					// Same as SBS_SIZEBOX, but with a raised edge.
			sbs_topalign				= SBS_TOPALIGN,					// Used with the SBS_HORZ style. The top edge of the scroll bar is aligned with the top edge of the rectangle specified in the Create member function. The scroll bar has the default height for system scroll bars.
			sbs_vertical				= SBS_VERT						// Designates a vertical scroll bar. If neither the SBS_RIGHTALIGN nor SBS_LEFTALIGN style is specified, the scroll bar has the height, width, and position given in the Create member function.
		};
	}
}

class WndScrollBar : public IControlWindow{
protected:
	bool thumbtract;
public:

	enum notifications{
		wmscroll
	};

	WndScrollBar(DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) : thumbtract(false){
		createWindow( "", dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}
	
	virtual void createWindow(LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam){
		if(hWnd){
			DestroyWindow(hWnd);
		}

		hWnd = CreateWindowEx(NULL, "SCROLLBAR", lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}

	inline bool setThumbtract(bool thumbtract){
		return this->thumbtract = thumbtract;
	}

	inline bool getThumbtract() const {
		return thumbtract;
	}

	inline BOOL getScrollInfo(LPSCROLLINFO lpsi) const {
		return GetScrollInfo(hWnd, SB_CTL, lpsi);
	}

	inline int setScrollInfo(LPSCROLLINFO lpsi, BOOL fRedraw){
		return SetScrollInfo(hWnd, SB_CTL, lpsi, fRedraw);
	}

	inline int getScrollPos() const {
		return GetScrollPos(hWnd, SB_CTL);
	}

	inline int setScrollPos(int nPos, BOOL redraw){
		return SetScrollPos(hWnd, SB_CTL, nPos, redraw);
	}

	inline BOOL getScrollRange(LPINT lpMinPos, LPINT lpMaxPos) const {
		return GetScrollRange(hWnd, SB_CTL, lpMinPos, lpMaxPos);
	}

	inline BOOL setScrollRange(int nMinPos, int nMaxPos, BOOL redraw){
		return SetScrollRange(hWnd, SB_CTL, nMinPos, nMaxPos, redraw);
	}

	bool wmScrollNotify(HWND hWnd, int pos, int scrollingRequest){
		if(hWnd != this->hWnd)
			return false;
		SCROLLINFO si;
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_PAGE|SIF_POS|SIF_RANGE|SIF_TRACKPOS;

		getScrollInfo(&si);

		int pBefore = si.nPos;

		switch(scrollingRequest){
			case SB_BOTTOM:
				break;
			case SB_ENDSCROLL:
				break;
			case SB_LINEDOWN:
				si.nPos = min(si.nMax, max(si.nMin, si.nPos + 1));
				break;
			case SB_LINEUP:
				si.nPos = min(si.nMax, max(si.nMin, si.nPos - 1));
				break;
			case SB_PAGEDOWN:
				si.nPos = min(si.nMax, max(si.nMin, si.nPos + si.nPage));
				break;
			case SB_PAGEUP:
				si.nPos = min(si.nMax, max(si.nMin, si.nPos - si.nPage));
				break;
			case SB_THUMBPOSITION:
				if(!thumbtract)
					si.nPos = si.nTrackPos;
				break;
			case SB_THUMBTRACK:
				if(thumbtract)
					si.nPos = si.nTrackPos;
				break;
			case SB_TOP:
				break;
		}

		si.fMask = SIF_POS;

		setScrollInfo(&si, true);

		std::map<int, INotificationCommand*>::iterator wmnotify = notificationsMap.find(notifications::wmscroll);

		if(pBefore != si.nPos && wmnotify != notificationsMap.end() && wmnotify->second != NULL){
			wmnotify->second->notify();
		}

		return true;
	}
};

#endif