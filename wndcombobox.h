#ifndef WNDCOMBOBOX_H
#define WNDCOMBOBOX_H

#include "controls_windows.h"

namespace ws{
	namespace combobox{
		enum cb_style{
			cbs_autohscroll			= CBS_AUTOHSCROLL,			// Automatically scrolls the text in an edit control to the right when the user types a character at the end of the line. If this style is not set, only text that fits within the rectangular boundary is allowed.
			cbs_disablenoscroll		= CBS_DISABLENOSCROLL,		// Shows a disabled vertical scroll bar in the list box when the box does not contain enough items to scroll. Without this style, the scroll bar is hidden when the list box does not contain enough items.
			cbs_dropdown			= CBS_DROPDOWN,				// Similar to CBS_SIMPLE, except that the list box is not displayed unless the user selects an icon next to the edit control.
			cbs_dropdownlist		= CBS_DROPDOWNLIST,			// Similar to CBS_DROPDOWN, except that the edit control is replaced by a static text item that displays the current selection in the list box.
			cbs_hasstrings			= CBS_HASSTRINGS,			// Specifies that an owner-drawn combo box contains items consisting of strings. The combo box maintains the memory and address for the strings so the application can use the CB_GETLBTEXT message to retrieve the text for a particular item.
																// For accessibility issues, see Exposing Owner-Drawn Combo Box Items
			cbs_lowercase			= CBS_LOWERCASE,			// Converts to lowercase all text in both the selection field and the list. 
			cbs_nointegralheight	= CBS_NOINTEGRALHEIGHT,		// Specifies that the size of the combo box is exactly the size specified by the application when it created the combo box. Normally, the system sizes a combo box so that it does not display partial items.
			cbs_oemconvert			= CBS_OEMCONVERT,			// Converts text entered in the combo box edit control from the Windows character set to the OEM character set and then back to the Windows character set. This ensures proper character conversion when the application calls the CharToOem function to convert a Windows string in the combo box to OEM characters. This style is most useful for combo boxes that contain file names and applies only to combo boxes created with the CBS_SIMPLE or CBS_DROPDOWN style.
			cbs_ownerdrawfixed		= CBS_OWNERDRAWFIXED,		// Specifies that the owner of the list box is responsible for drawing its contents and that the items in the list box are all the same height. The owner window receives a WM_MEASUREITEM message when the combo box is created and a WM_DRAWITEM message when a visual aspect of the combo box has changed.
			cbs_ownerdrawvariable	= CBS_OWNERDRAWVARIABLE,	// Specifies that the owner of the list box is responsible for drawing its contents and that the items in the list box are variable in height. The owner window receives a WM_MEASUREITEM message for each item in the combo box when you create the combo box and a WM_DRAWITEM message when a visual aspect of the combo box has changed.
			cbs_simple				= CBS_SIMPLE,				// Displays the list box at all times. The current selection in the list box is displayed in the edit control.
			cbs_sort				= CBS_SORT,					// Automatically sorts strings added to the list box.
			cbs_uppercase			= CBS_UPPERCASE				// Converts to uppercase all text in both the selection field and the list.
		};
	}
}

class WndComboBox : public IControlWindow {
public:
	enum notifications {
		closeup			= CBN_CLOSEUP,
		doubleclick		= CBN_DBLCLK,
		dropdown		= CBN_DROPDOWN,
		editchange		= CBN_EDITCHANGE,
		editupdate		= CBN_EDITUPDATE,
		errspace		= CBN_ERRSPACE,
		killfocus		= CBN_KILLFOCUS,
		selchange		= CBN_SELCHANGE,
		selendcancel	= CBN_SELENDCANCEL,
		selwndok		= CBN_SELENDOK,
		setfocus		= CBN_SETFOCUS
	};

	WndComboBox(DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam){
		createWindow( "", dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}
	
	virtual void createWindow(LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam){
		if(hWnd){
			DestroyWindow(hWnd);
		}

		hWnd = CreateWindowEx(NULL, "COMBOBOX", lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}

	inline void addTextItem(std::string text){
		SendMessage(hWnd, CB_ADDSTRING, NULL, (LPARAM)text.c_str());
	}

	inline void deleteItem(int index){
		SendMessage(hWnd, CB_DELETESTRING, index, NULL);
	}

	inline LONG getCurrentSelectedIndex() const {
		return SendMessage(hWnd, CB_GETCURSEL, NULL, NULL);
	}

	inline LONG getCount() const {
		return SendMessage(hWnd, CB_GETCOUNT, NULL, NULL);
	}

	std::string getSelectedText() const {
		std::string text;
		LONG index = getCurrentSelectedIndex();
		if(index > -1){
			int length = SendMessage(hWnd, CB_GETLBTEXTLEN, index, NULL);
			char* t = new char[length + 1];

			SendMessage(hWnd, CB_GETLBTEXT, index, (LPARAM) t);
			text = t;

			delete [] t;
		}
		return text;
	}

	std::string getEditText() const {
		COMBOBOXINFO cbInfo;
		cbInfo.cbSize = sizeof(COMBOBOXINFO);

		std::string edittext;

		if(SendMessage(hWnd, CB_GETCOMBOBOXINFO, NULL, (LPARAM) &cbInfo)){
			int length = GetWindowTextLength(cbInfo.hwndItem);
			if(length > 0){
				char* text = new char[length + 1];
				GetWindowText(cbInfo.hwndItem, text, length + 1);
				edittext = text;
				delete [] text;
			}
		}
		return edittext;
	}

	// An application sends a CB_SETEDITSEL message to select characters in the edit control of a combo box. 
	// Works only on combobox without CBS_DROPDOWNLIST style
	inline BOOL setEditSelection(int begin, int end){
		return SendMessage(hWnd, CB_SETEDITSEL, NULL, MAKELPARAM(begin, end));
	}

	inline LONG setCurrentSelection(int index){
		return SendMessage(hWnd, CB_SETCURSEL, index, NULL);
	}

	inline void clear(){
		SendMessage(hWnd, CB_RESETCONTENT, NULL, NULL);
	}
};

#endif