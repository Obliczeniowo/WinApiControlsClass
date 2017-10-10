#include "controls_windows.h"

bool IWmNotify::wmNotify(LPARAM lParam, HWND hWnd){
	LPNMHDR lpnmhdr = LPNMHDR(lParam);
	if(lpnmhdr->hwndFrom != hWnd){
		return false;
	}

	std::map<int, IWmNotificationCommand*>::iterator wmcommand = wmNotifications.find(lpnmhdr->code);
	if(wmcommand != wmNotifications.end()){
		wmcommand->second->notify(lParam);
	}

	return true;
}

void IWmNotify::addWmNotification(int wmNotifyCommand, IWmNotificationCommand* inc){
	std::map<int, IWmNotificationCommand*>::iterator wmcommand = wmNotifications.find(wmNotifyCommand);
	if(wmcommand != wmNotifications.end()){
		if(wmcommand->second)
			delete wmcommand->second;
	}
	wmNotifications[wmNotifyCommand] = inc;
}

IWmNotify::~IWmNotify(){
	for(std::map<int, IWmNotificationCommand*>::iterator command = wmNotifications.begin(); command != wmNotifications.end(); command ++){
		if(command->second)
			delete command->second;
	}
}