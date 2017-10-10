#include "wndtooltip.h"

OnWmNotifyGetDispInfo::OnWmNotifyGetDispInfo(HWND from, const char* toolTipText) : from(from){
	this->toolTipText = new char[strlen(toolTipText) + 1];
	strcpy(this->toolTipText, toolTipText);
}

void OnWmNotifyGetDispInfo::notify(LPARAM lParam){
	LPNMTTDISPINFO lpnmtdi =(LPNMTTDISPINFO)lParam;

	lpnmtdi->lpszText	= toolTipText;
	lpnmtdi->hinst		= NULL;
	lpnmtdi->uFlags		= 0;//TTF_DI_SETITEM;
}

OnWmNotifyGetDispInfo::~OnWmNotifyGetDispInfo(){
	if(toolTipText)
		delete toolTipText;
}