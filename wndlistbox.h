#ifndef WNDLISTBOX_H
#define WNDLISTBOX_H

#include "controls_windows.h"
#include <vector>

namespace ws{
	namespace listbox{
		enum lb_style{
			lbs_combobox			= LBS_COMBOBOX,			// Notifies a list box that it is part of a combo box. This allows coordination between the two controls so that they present a unified user interface (UI). The combo box itself must set this style. If the style is set by anything but the combo box, the list box will regard itself incorrectly as a child of a combo box and a failure will result.
			lbs_disablenoscroll		= LBS_DISABLENOSCROLL,	// Shows a disabled vertical scroll bar for the list box when the box does not contain enough items to scroll. If you do not specify this style, the scroll bar is hidden when the list box does not contain enough items.
			lbs_extendedsel			= LBS_EXTENDEDSEL,		// Allows multiple items to be selected by using the SHIFT key and the mouse or special key combinations.
			lbs_hasstrings			= LBS_HASSTRINGS,		// Specifies that a list box contains items consisting of strings. The list box maintains the memory and addresses for the strings so that the application can use the LB_GETTEXT message to retrieve the text for a particular item. By default, all list boxes except owner-drawn list boxes have this style. You can create an owner-drawn list box either with or without this style.
			lbs_multicolumn			= LBS_MULTICOLUMN,		// Specifies a multi-columnn list box that is scrolled horizontally. The LB_SETCOLUMNWIDTH message sets the width of the columns.
			lbs_multiplesel			= LBS_MULTIPLESEL,		// Turns string selection on or off each time the user clicks or double-clicks a string in the list box. The user can select any number of strings.
			lbs_nodata				= LBS_NODATA,			// Specifies a no-data list box. Specify this style when the count of items in the list box will exceed one thousand. A no-data list box must also have the LBS_OWNERDRAWFIXED style, but must not have the LBS_SORT or LBS_HASSTRINGS style. 
															// A no-data list box resembles an owner-drawn list box except that it contains no string or bitmap data for an item. Commands to add, insert, or delete an item always ignore any specified item data; requests to find a string within the list box always fail. The system sends the WM_DRAWITEM message to the owner window when an item must be drawn. The itemID member of the DRAWITEMSTRUCT structure passed with the WM_DRAWITEM message specifies the line number of the item to be drawn. A no-data list box does not send a WM_DELETEITEM message.
			lbs_nointegralheight	= LBS_NOINTEGRALHEIGHT,	// Specifies that the size of the list box is exactly the size specified by the application when it created the list box. Normally, the system sizes a list box so that the list box does not display partial items.
			lbs_noredraw			= LBS_NOREDRAW,			// Specifies that the list box's appearance is not updated when changes are made.
															// To change the redraw state of the control, use the WM_SETREDRAW message.
			lbs_nosel				= LBS_NOSEL,			// Specifies that the list box contains items that can be viewed but not selected. 
			lbs_notify				= LBS_NOTIFY,			// Notifies the parent window with an input message whenever the user clicks or double-clicks a string in the list box.
			lbs_ownerdrawfixed		= LBS_OWNERDRAWFIXED,	// Specifies that the owner of the list box is responsible for drawing its contents and that the items in the list box are the same height. The owner window receives a WM_MEASUREITEM message when the list box is created and a WM_DRAWITEM message when a visual aspect of the list box has changed.
			lbs_ownerdrawvariable	= LBS_OWNERDRAWVARIABLE,// Specifies that the owner of the list box is responsible for drawing its contents and that the items in the list box are variable in height. The owner window receives a WM_MEASUREITEM message for each item in the combo box when the combo box is created and a WM_DRAWITEM message when a visual aspect of the combo box has changed.
			lbs_sort				= LBS_SORT,				// Sorts strings in the list box alphabetically.
			lbs_standard			= LBS_STANDARD,			// Sorts strings in the list box alphabetically. The parent window receives an input message whenever the user clicks or double-clicks a string. The list box has borders on all sides.
			lbs_usetabstops			= LBS_USETABSTOPS,		// Enables a list box to recognize and expand tab characters when drawing its strings. You can use the LB_SETTABSTOPS message to specify tab stop positions. The default tab positions are 32 dialog template units apart. Dialog template units are the device-independent units used in dialog box templates. To convert measurements from dialog template units to screen units (pixels), use the MapDialogRect function.
			lbs_wantkeyboardinput	= LBS_WANTKEYBOARDINPUT // Specifies that the owner of the list box receives WM_VKEYTOITEM messages whenever the user presses a key and the list box has the input focus. This enables an application to perform special processing on the keyboard input.
		};
	}
}

class WndListBox : public IControlWindow{
public:

	enum notifications{
		doubleclick	= LBN_DBLCLK,
		errspace	= LBN_ERRSPACE,
		killfocus	= LBN_KILLFOCUS,
		selcancel	= LBN_SELCANCEL,
		selchange	= LBN_SELCHANGE,
		setfocus	= LBN_SETFOCUS
	};

	WndListBox(DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam){
		createWindow( "", dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}
	
	virtual void createWindow(LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam){
		if(hWnd){
			DestroyWindow(hWnd);
		}

		hWnd = CreateWindowEx(NULL, "LISTBOX", lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}

	inline void addTextItem(std::string text){
		SendMessage(hWnd, LB_ADDSTRING, NULL, (LPARAM)text.c_str());
	}

	inline void deleteItem(int index){
		SendMessage(hWnd, LB_DELETESTRING, index, NULL);
	}

	inline LONG getItemCount() const {
		return SendMessage(hWnd, LB_GETCOUNT, NULL, NULL);
	}

	inline LONG getSelectedItemCount() const {
		return SendMessage(hWnd, LB_GETSELCOUNT, NULL, NULL);
	}
	// Gets the index of the first visible item in a list box. Initially the item with index 0 is at the top of the list box, but if the list box contents have been scrolled another item may be at the top. 
	inline LONG getTopIndex() const {
		return SendMessage(hWnd, LB_GETTOPINDEX, NULL, NULL);
	}

	inline LONG setTopIndex(int index){
		return SendMessage(hWnd, LB_SETTOPINDEX, index, NULL);
	}

	void getSelectedItemsIndexArray(std::vector<int> &itemArray);

	inline LONG getCurrentSelectedIndex() const {
		return SendMessage(hWnd, LB_GETCURSEL, NULL, NULL);
	}

	inline LONG setCurrentSelectedIndex(int index) {
		return SendMessage(hWnd, LB_SETCURSEL, index, NULL);
	}

	inline LONG setSelection(int index, bool select_undelect) {
		return SendMessage(hWnd, LB_SETSEL, select_undelect, index);
	}

	inline LRESULT getItemData(int index) const {
		return SendMessage(hWnd, LB_GETITEMDATA, index, NULL);
	}

	std::string getItemText(int index) const;

	inline LONG addDir(std::string path, UINT attributes){
		return SendMessage(hWnd, LB_DIR, attributes, (LPARAM) path.c_str());
	}

	inline void clearList(){
		SendMessage(hWnd, LB_RESETCONTENT, NULL, NULL);
	}

	inline LONG selectString(std::string text, int beginIndex){ // dzia³a tylko w trybie zaznaczenia pojedynczych rekordów listy
		return SendMessage(hWnd, LB_SELECTSTRING, beginIndex, (LPARAM)text.c_str());
	}

	inline LONG selectItemRange(int begin, int end, bool select_unselect){
		return SendMessage(hWnd, LB_SELITEMRANGE, select_unselect, MAKELPARAM(begin, end));
	}
};

#endif WNDLISTBOX_H