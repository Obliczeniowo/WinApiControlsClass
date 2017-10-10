#include "wndscrollbar.h"

bool WndScrollBar::wmScrollNotify(HWND hWnd, int pos, int scrollingRequest){
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