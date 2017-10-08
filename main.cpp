#include <windows.h>

#include "all_basic_controls.h"

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

class OnComboBoxSelChanged : public INotificationCommand{
public:
	WndEdit*		edit;
	WndComboBox*	combobox;

	OnComboBoxSelChanged(WndEdit* edit, WndComboBox* combobox) : edit(edit), combobox(combobox){}

	virtual void notify(){
		edit->setWindowText(combobox->getSelectedText());
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
		MessageBox(label->getParentWindow(), label->getWindowText().c_str(), "Label (STATIC) control clicked", MB_OK);
	}
};

class OnButtonClicked : public INotificationCommand{
public:
	WndButton*	button;
	WndEdit*	edit;

	OnButtonClicked(WndButton* button, WndEdit* edit) : button(button), edit(edit) {}

	virtual void notify(){
		if(button->toggleButtonState() == WndButton::checkState::checked ){
			edit->setWindowText("Button checked");
		}else{
			edit->setWindowText("Button unchecked");
		}
	}
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	static HFONT			font;

	static WndEdit*			myEdit;
	static WndScrollBar*	myScrollBar;
	static WndListBox*		myListBox;
	static WndLabel*		myLabel;
	static WndComboBox*		myComboBox;
	static WndButton*		myButton;
	switch(msg){
		case WM_CREATE:
			{
				NONCLIENTMETRICS ncm;
				ncm.cbSize=sizeof(ncm);
				SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
				font = CreateFontIndirect(&ncm.lfStatusFont);

				myEdit = new WndEdit(				// Create WndEdit control object
						"some edit stuff",			// text to set in edit control
						ws::window::ws_child		// control styles: as child window
						| ws::window::ws_visible	// as visible window
						| ws::window::ws_hscrollbar	// as window with horizontal scroll bar
						| ws::window::ws_vscrollbar	// as window with vertical scroll bar
						| ws::edit::es_autohscroll	// as edit control with auto horizontal scroll
						| ws::edit::es_autovscroll	// as edit control with auto vertical scroll
						| ws::edit::es_multiline,	// as multiline edit control
						100,						// x - position
						0,							// y - position
						100,						// width
						50,							// height
						hWnd,						// handle to parent window
						(HMENU) 5000,				// in this case id of control
						hInst,						// handle to application instance
						NULL						// pointer to some extra data stuff (in this cas NULL means no extra data stuff)
					);
				// set myEdit object control font
				myEdit->setFont(font);

				myScrollBar = new WndScrollBar(			// create WndScrollBar object of control ScrollBar
						ws::window::ws_child|			// Style of control: as child
						ws::window::ws_visible|			// as visible
						ws::scrollbar::sbs_horizontal,	// as hotizontal scroll bar
						100,							// x - position
						50,								// y - position
						100,							// width
						20,								// height
						hWnd,							// parent window handle
						(HMENU) 5001,					// in this case it is a id of control
						hInst,							// handle to application instance
						NULL							// pointer to some extra data stuff (in this cas NULL means no extra data stuff)
					);

				SCROLLINFO si;	// structure describe setting of scroll bar control

				si.cbSize		= sizeof(SCROLLINFO);	// this parameter must be set
				si.fMask		= SIF_ALL;				// flag describing whitch of struct field will be used
				si.nMax			= 110;					// maximum value + nPage - 1
				si.nMin			= 0;					// minimum value
				si.nPage		= 11;					// page scrolling size
				si.nPos			= 0;					// current scroll bar pos
				si.nTrackPos	= 0;					// current track pos

				myScrollBar->setScrollInfo(&si, false); // set settings of scrollbar
				myScrollBar->setThumbtract(true); // this means that when user move control slider then value of nPos Scroll Bar is changed
				// add some notification command for myScrollBar object control
				myScrollBar->addNotification(WndScrollBar::notifications::wmscroll, new OnScrollChanged(myEdit, myScrollBar));
				
				myListBox = new WndListBox(		// create WndListBox window object
					ws::window::ws_hscrollbar|	// with styla: hotizontal scrollbar
					ws::window::ws_vscrollbar|	// vertical scrollbar
					ws::window::ws_child|		// as child window
					ws::window::ws_visible|		// as visible widnow
					ws::listbox::lbs_notify|	// with sending notification code
					ws::listbox::lbs_hasstrings,// with string data item
					100,						// x-position
					70,							// y-position
					100,						// control width
					100,						// control height
					hWnd,						// parent window handle
					(HMENU) 5002,				// in this case it is an window ID
					hInst,						// application instance handle
					NULL						// pointer to some extra data (in this case NULL - means no extra data)
				);

				// add items to list box
				myListBox->addTextItem("Polska");
				myListBox->addTextItem("Czechy");
				myListBox->addTextItem("S³owacja");
				myListBox->addTextItem("Litwa");
				myListBox->addTextItem("£otwa");
				myListBox->addTextItem("Estonia");
				myListBox->addTextItem("Wêgry");
				myListBox->addTextItem("Stany Zjednoczone Ameryki");
				// set myListBox font
				myListBox->setFont(font);
				// add some notifications stuff
				myListBox->addNotification(WndListBox::notifications::selchange, new OnListBoxSelChanged(myEdit, myListBox)); // notification command for selchange notify
				myListBox->addNotification(WndListBox::notifications::doubleclick, new OnListBoxDblClick(myEdit, myListBox)); // notification command for doubleclick notify

				myLabel = new WndLabel(				// create WndLabel object of Static control
							"Label",				// text to write in window
							ws::window::ws_child|	// window style: as child
							ws::window::ws_visible|	// as visible
							ws::label::ss_notify,	// with sending notifications to parent window
							100,					// x - position
							170,					// y - position
							100,					// width
							20,						// height
							hWnd,					// parent window handle
							(HMENU) 5003,			// in this case id of cotrol
							hInst,					// handle to application instance
							NULL					// pointer to some extra data (in this case NULL - means no extra data)
						);
				// set myLabel font
				myLabel->setFont(font);
				// add notification command object to myLabel control
				myLabel->addNotification(WndLabel::notifications::clicked, new OnLabelClick(myLabel));

				myComboBox = new WndComboBox(			// create WndComboBox class object of combobox control
						ws::window::ws_child|			// with style: as child
						ws::window::ws_visible|			// as visible
						ws::window::ws_vscrollbar|		// with vertical scrollbar
						ws::combobox::cbs_hasstrings|	// with string data for stored items
						ws::combobox::cbs_dropdown,		// with drop down list
						100,							// x - position
						190,							// y - position
						100,							// width
						100,							// height (including drop down list height)
						hWnd,							// handle to parent window
						(HMENU) 5004,					// in this case control id
						hInst,							// application instance handle
						NULL							// pointer to some extra data (in this case NULL - means no extra data)
					);

				// add items to combo box
				myComboBox->addTextItem("Polska");
				myComboBox->addTextItem("Czechy");
				myComboBox->addTextItem("S³owacja");
				myComboBox->addTextItem("Litwa");
				myComboBox->addTextItem("£otwa");
				myComboBox->addTextItem("Estonia");
				myComboBox->addTextItem("Wêgry");
				myComboBox->addTextItem("Stany Zjednoczone Ameryki");

				myComboBox->setFont(font);

				myComboBox->addNotification(WndComboBox::notifications::selchange, new OnComboBoxSelChanged(myEdit, myComboBox));

				myButton = new WndButton(
						"Kliknij",
						ws::window::ws_child|
						ws::window::ws_visible|
						ws::button::bs_notify,
						100,
						214,
						100,
						20,
						hWnd,
						(HMENU) 5004,
						hInst,
						NULL
					);

				myButton->setFont(font);

				myButton->setCheckBoxStyle(true);

				myButton->addNotification(WndButton::notifications::clicked, new OnButtonClicked(myButton, myEdit));
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

				if(myListBox->notify(ctrl, id, nc)) // doing notification stuff for myListBox control object
					break;
				if(myLabel->notify(ctrl, id, nc)) // doing notification stuff for myLabel control object
					break;
				if(myComboBox->notify(ctrl, id, nc)) // doing notification stuff for myComboBox control object
					break;
				if(myButton->notify(ctrl, id, nc))
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
				if(myComboBox)
					delete myComboBox;
				if(myScrollBar)
					delete myScrollBar;
				if(myButton)
					delete myButton;
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