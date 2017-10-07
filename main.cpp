#include <windows.h>

#include "wndbutton.h"
#include "wndedit.h"
#include "wndscrollbar.h"
#include "wndlabel.h"
#include "wndcombobox.h"
#include "wndlistbox.h"

HINSTANCE hInst;

class OnScrollChanged : public INotificationCommand {
public:
	WndEdit*		edit;
	WndScrollBar*	scrollbar;

	OnScrollChanged(WndEdit* edit, WndScrollBar* scrollbar) : edit(edit), scrollbar(scrollbar){}

	virtual void notify(){
		char cPos[50];
		ltoa(scrollbar->getScrollPos(), cPos, 10);
		edit->setWindowText(cPos);
	}
};

class OnListBoxSelChanged : public INotificationCommand{
public:
	WndEdit*	edit;
	WndListBox*	listbox;

	OnListBoxSelChanged(WndEdit* edit, WndListBox* listbox) : edit(edit), listbox(listbox){}

	virtual void notify(){
		edit->setWindowText(listbox->getItemText(listbox->getCurrentSelectedIndex()));
	}
};

class OnListBoxDblClick : public INotificationCommand{
public:
	WndEdit*	edit;
	WndListBox*	listbox;

	OnListBoxDblClick(WndEdit* edit, WndListBox* listbox) : edit(edit), listbox(listbox){}

	virtual void notify(){
		
		MessageBox(listbox->getParentWindow(), listbox->getItemText(listbox->getCurrentSelectedIndex()).c_str(), "CLICKED", MB_OK);
	}
};

class OnLabelClick : public INotificationCommand{
public:
	WndLabel* label;

	OnLabelClick(WndLabel* label) : label(label){}

	virtual void notify(){
		MessageBox(label->getParentWindow(), label->getWindowText().c_str(), "CLICKED", MB_OK);
	}
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	static HFONT			font;

	static WndEdit*			myEdit;
	static WndScrollBar*	myScrollBar;
	static WndListBox*		myListBox;
	static WndLabel*		myLabel;
	switch(msg){
		case WM_CREATE:
			{
				NONCLIENTMETRICS ncm;
				ncm.cbSize=sizeof(ncm);
				SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
				font = CreateFontIndirect(&ncm.lfStatusFont);

				myEdit = new WndEdit(
						"some edit stuff",
						ws::window::ws_child 
						| ws::window::ws_visible 
						| ws::window::ws_hscrollbar
						| ws::window::ws_vscrollbar
						| ws::edit::es_autohscroll 
						| ws::edit::es_autovscroll 
						| ws::edit::es_multiline,
						100,
						0,
						100,
						50,
						hWnd,
						(HMENU) 5000,
						hInst,
						NULL
					);

				myEdit->setFont(font);

				myScrollBar = new WndScrollBar(
						ws::window::ws_child|
						ws::window::ws_visible|
						ws::scrollbar::sbs_horizontal,
						100,
						50,
						100,
						20,
						hWnd,
						(HMENU) 5001,
						hInst,
						NULL
					);

				SCROLLINFO si;

				si.cbSize		= sizeof(SCROLLINFO);
				si.fMask		= SIF_ALL;
				si.nMax			= 110;
				si.nMin			= 0;
				si.nPage		= 11;
				si.nPos			= 0;
				si.nTrackPos	= 0;

				myScrollBar->setScrollInfo(&si, false);
				myScrollBar->setThumbtract(true);

				myScrollBar->addNotification(WndScrollBar::notifications::wmscroll, new OnScrollChanged(myEdit, myScrollBar));
				
				myListBox = new WndListBox(
					ws::window::ws_hscrollbar|
					ws::window::ws_vscrollbar|
					ws::window::ws_child|
					ws::window::ws_visible|
					ws::listbox::lbs_notify|
					ws::listbox::lbs_hasstrings,
					100,
					70,
					100,
					100,
					hWnd,
					(HMENU) 5002,
					hInst,
					NULL
				);

				myListBox->addTextItem("Polska");
				myListBox->addTextItem("Czechy");
				myListBox->addTextItem("S³owacja");
				myListBox->addTextItem("Litwa");
				myListBox->addTextItem("£otwa");
				myListBox->addTextItem("Estonia");
				myListBox->addTextItem("Wêgry");
				myListBox->addTextItem("Stany Zjednoczone Ameryki");

				myListBox->setFont(font);

				myListBox->addNotification(WndListBox::notifications::selchange, new OnListBoxSelChanged(myEdit, myListBox));
				myListBox->addNotification(WndListBox::notifications::doubleclick, new OnListBoxDblClick(myEdit, myListBox));

				myLabel = new WndLabel(
							"Label",
							ws::window::ws_child|
							ws::window::ws_visible|
							ws::label::ss_notify,
							100,
							170,
							100,
							20,
							hWnd,
							(HMENU) 5003,
							hInst,
							NULL
						);

				myLabel->setFont(font);

				myLabel->addNotification(WndLabel::notifications::clicked, new OnLabelClick(myLabel));
			}
			break;
		case WM_HSCROLL:
			{
				int pos = HIWORD(wParam);
				int id	= LOWORD(wParam);
				HWND ctrl = HWND(lParam);

				if(myScrollBar->wmScrollNotify(ctrl, pos, id))
					break;
			}
			break;
		case WM_COMMAND:
			{
				UINT nc = HIWORD(wParam);
				UINT id = LOWORD(wParam);
				HWND ctrl = (HWND) lParam;

				if(myListBox->notify(ctrl, id, nc))
					break;
				if(myLabel->notify(ctrl, id, nc))
					break;
			}
			break;
		case WM_DESTROY:
			{
				PostQuitMessage(0);

				if(myEdit)
					delete myEdit;
				if(myListBox)
					delete myListBox;
				if(myLabel)
					delete myLabel;
			}
			break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nShowCmd){
	hInst = hInstance;

	WNDCLASS wnd;

	wnd.cbClsExtra		= 0;
	wnd.cbWndExtra		= 0;
	wnd.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wnd.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wnd.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wnd.hInstance		= hInstance;
	wnd.lpfnWndProc		= WndProc;
	wnd.lpszClassName	= "MainWindow";
	wnd.lpszMenuName	= NULL;
	wnd.style			= CS_VREDRAW|CS_HREDRAW;

	if(!RegisterClass(&wnd)){
		MessageBox(NULL, "Something wrong with WNDCLASS declaration of MainWindow", "ERROR", MB_OK);
		return 0;
	}

	HWND hWnd = CreateWindow("MainWindow", "Main Window - controls object example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);

	MSG msg;

	while(GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}