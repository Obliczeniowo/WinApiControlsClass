#include "controls_windows.h"

IControlWindow::~IControlWindow(){
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

std::string IControlWindow::getWindowText() const{
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

void IControlWindow::getWindowPos(POINT &p) const {
	RECT rect;
	GetWindowRect(hWnd, &rect);
	p.x = rect.left;
	p.y = rect.top;
}

void IControlWindow::getWindowSize(SIZE &wndSize) const {
	wndSize.cx = wndSize.cy = -1;
	RECT wndRect;
	GetWindowRect(hWnd, &wndRect);
	wndSize.cx = wndRect.right - wndRect.left;
	wndSize.cy = wndRect.bottom - wndRect.top;
}

std::string IControlWindow::getWindowClassName() const {
	char classname[255];
	GetClassName(hWnd, classname, 255);

	return std::string(classname);
}

bool IControlWindow::addNotification(int notify, INotificationCommand* nc) {
	if(notificationsMap.find(notify) != notificationsMap.end()){
		if(notificationsMap[notify]){
			delete notificationsMap[notify];
		}
	}
	notificationsMap[notify] = nc;
	return true;
}

bool IControlWindow::notify(HWND hwndCtl, int wID, int wNotifyCode){
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