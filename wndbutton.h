#ifndef WNDBUTTON_H
#define WNDBUTTON_H

#include "controls_windows.h"

namespace ws{
	namespace button{
		enum bt_style{
			bs_3state			= BS_3STATE,			// Creates a button that is the same as a check box, except that the box can be grayed as well as checked or cleared. Use the grayed state to show that the state of the check box is not determined.
			bs_auto3state		= BS_AUTO3STATE,		// Creates a button that is the same as a three-state check box, except that the box changes its state when the user selects it. The state cycles through checked, indeterminate, and cleared.
			bs_autocheckbox		= BS_AUTOCHECKBOX,		// Creates a button that is the same as a check box, except that the check state automatically toggles between checked and cleared each time the user selects the check box.
			bs_autoradiobutton	= BS_AUTORADIOBUTTON,	// Creates a button that is the same as a radio button, except that when the user selects it, the system automatically sets the button's check state to checked and automatically sets the check state for all other buttons in the same group to cleared.
			bs_checkbox			= BS_CHECKBOX,			// Creates a small, empty check box with text. By default, the text is displayed to the right of the check box. To display the text to the left of the check box, combine this flag with the BS_LEFTTEXT style (or with the equivalent BS_RIGHTBUTTON style).
			bs_defpushbutton	= BS_DEFPUSHBUTTON,		// Creates a push button that behaves like a BS_PUSHBUTTON style button, but has a distinct appearance. If the button is in a dialog box, the user can select the button by pressing the ENTER key, even when the button does not have the input focus. This style is useful for enabling the user to quickly select the most likely (default) option.
			bs_groupbox			= BS_GROUPBOX,			// Creates a rectangle in which other controls can be grouped. Any text associated with this style is displayed in the rectangle's upper left corner.
			bs_lefttext			= BS_LEFTTEXT,			// Places text on the left side of the radio button or check box when combined with a radio button or check box style. Same as the BS_RIGHTBUTTON style.
			bs_ownerdraw		= BS_OWNERDRAW,			// Creates an owner-drawn button. The owner window receives a WM_DRAWITEM message when a visual aspect of the button has changed. Do not combine the BS_OWNERDRAW style with any other button styles.
			bs_pushbutton		= BS_PUSHBUTTON,		// Creates a push button that posts a WM_COMMAND message to the owner window when the user selects the button.
			bs_radiobutton		= BS_RADIOBUTTON,		// Creates a small circle with text. By default, the text is displayed to the right of the circle. To display the text to the left of the circle, combine this flag with the BS_LEFTTEXT style (or with the equivalent BS_RIGHTBUTTON style). Use radio buttons for groups of related, but mutually exclusive choices.
			bs_userbutton		= BS_USERBUTTON,		// Obsolete, but provided for compatibility with 16-bit versions of Windows. Applications should use BS_OWNERDRAW instead.
			bs_bitmap			= BS_BITMAP,			// Specifies that the button displays a bitmap. See the Remarks section for its interaction with BS_ICON.
			bs_bottom			= BS_BOTTOM,			// Places text at the bottom of the button rectangle.
			bs_center			= BS_CENTER,			// Centers text horizontally in the button rectangle.
			bs_icon				= BS_ICON,				// Specifies that the button displays an icon. See the Remarks section for its interaction with BS_BITMAP.
			bs_flat				= BS_FLAT,				// Specifies that the button is two-dimensional; it does not use the default shading to create a 3-D image. 
			bs_left				= BS_LEFT,				// Left-justifies the text in the button rectangle. However, if the button is a check box or radio button that does not have the BS_RIGHTBUTTON style, the text is left justified on the right side of the check box or radio button.
			bs_multiline		= BS_MULTILINE,			// Wraps the button text to multiple lines if the text string is too long to fit on a single line in the button rectangle.
			bs_notify			= BS_NOTIFY,			// Enables a button to send BN_KILLFOCUS and BN_SETFOCUS notification messages to its parent window. 
														// Note that buttons send the BN_CLICKED notification message regardless of whether it has this style. To get BN_DBLCLK notification messages, the button must have the BS_RADIOBUTTON or BS_OWNERDRAW style.
			bs_pushlike			= BS_PUSHLIKE,			// Makes a button (such as a check box, three-state check box, or radio button) look and act like a push button. The button looks raised when it isn't pushed or checked, and sunken when it is pushed or checked.
			bs_right			= BS_RIGHT,				// Right-justifies text in the button rectangle. However, if the button is a check box or radio button that does not have the BS_RIGHTBUTTON style, the text is right justified on the right side of the check box or radio button.
			bs_rightbutton		= BS_RIGHTBUTTON,		// Positions a radio button's circle or a check box's square on the right side of the button rectangle. Same as the BS_LEFTTEXT style.
			bs_text				= BS_TEXT,				// Specifies that the button displays text.
			bs_top				= BS_TOP,				// Places text at the top of the button rectangle.
			bs_typemask			= BS_TYPEMASK,			// Microsoft Windows 2000: A composite style bit that results from using the OR operator on BS_* style bits. It can be used to mask out valid BS_* bits from a given bitmask. Note that this is out of date and does not correctly include all valid styles. Thus, you should not use this style.
			bs_vcenter			= BS_VCENTER,			// Places text in the middle (vertically) of the button rectangle.
			bs_splitbutton		= BS_SPLITBUTTON,		// Microsoft Windows Vista and Version 6.00. Creates a split button. A split button has a drop down arrow.The following is a picture of a split button.
			bs_defsplitbutton	= BS_DEFSPLITBUTTON,	// Microsoft Windows Vista and Version 6.00. Creates a split button that behaves like a BS_PUSHBUTTON style button, but also has a distinctive appearance. If the split button is in a dialog box, the user can select the split button by pressing the ENTER key, even when the split button does not have the input focus. This style is useful for enabling the user to quickly select the most likely (default) option.
			bs_commandlink		= BS_COMMANDLINK,		// Microsoft Windows Vista and Version 6.00. Creates a command link button. The following is a picture of command link button.
			bs_defcommandlink	= BS_DEFCOMMANDLINK		// Microsoft Windows Vista and Version 6.00. Creates a command link button that behaves like a BS_PUSHBUTTON style button. If the button is in a dialog box, the user can select the command link button by pressing the ENTER key, even when the command link button does not have the input focus. This style is useful for enabling the user to quickly select the most likely (default) option.
		};
	}
}

class WndButton : public IControlWindow{
public:
	enum notifications{
		dropdown		= BCN_DROPDOWN,
		hotitemchange	= BCN_HOTITEMCHANGE,
		clicked			= BN_CLICKED,
		doubleblclick	= BN_DOUBLECLICKED,
		disable			= BN_DISABLE,
		hilite			= BN_HILITE,
		killfocus		= BN_KILLFOCUS,
		paint			= BN_PAINT,
		pushed			= BN_PUSHED,
		setfocus		= BN_SETFOCUS,
		unhilite		= BN_UNHILITE,
		unpushed		= BN_UNPUSHED,
		customdraw		= NM_CUSTOMDRAW
	};

	WndButton(LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam){
		createWindow( lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}
	
	virtual void createWindow(LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam){
		if(hWnd){
			DestroyWindow(hWnd);
		}

		hWnd = CreateWindowEx(NULL, "BUTTON", lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}

	inline void setImageFromResource(UINT id){
		SendMessage(hWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(getHinstance(), MAKEINTRESOURCE(id)));
	}

	inline void click(){
		SendMessage(hWnd, BM_CLICK, NULL, NULL);
	}

	enum checkState{
		none = 0,
		checked = BST_CHECKED,
		indeterminate = BST_INDETERMINATE,
		unchecked = BST_UNCHECKED
	};

	inline checkState getCheck(){
		return checkState(SendMessage(hWnd, BM_GETCHECK, NULL, NULL));
	}

	inline checkState setCheck(checkState state){
		SendMessage(hWnd, BM_SETCHECK, state, NULL);
		return state;
	}

	inline void setCheckBoxStyle(bool checkBox){
		if(checkBox){
			setWindowStyle(false, BS_RADIOBUTTON);
			setWindowStyle(false, BS_PUSHBUTTON);
		}
		setWindowStyle(checkBox, BS_CHECKBOX);
	}

	inline void setRadioButtonStyle(bool radioButton){
		if(radioButton){
			setWindowStyle(false, BS_CHECKBOX);
			setWindowStyle(false, BS_PUSHBUTTON);
		}
		setWindowStyle(radioButton, BS_RADIOBUTTON);
	}

	inline void setPushButtonStyle(bool pushButton){
		if(pushButton){
			setWindowStyle(false, BS_RADIOBUTTON);
			setWindowStyle(false, BS_CHECKBOX);
		}
		setWindowStyle(pushButton, BS_PUSHBUTTON);
	}

	inline checkState toggleButtonState(){
		return getCheck() == checkState::checked ? setCheck(checkState::unchecked) : setCheck(checkState::checked);
	}

	void setTextToLeft(){
		setWindowStyle(false, BS_CENTER);
		setWindowStyle(false, BS_RIGHT);
		setWindowStyle(true, BS_LEFT);
	}

	void setTextToRight(){
		setWindowStyle(false, BS_CENTER);
		setWindowStyle(true, BS_RIGHT);
		setWindowStyle(false, BS_LEFT);
	}

	void setTextToCenter(){
		setWindowStyle(true, BS_CENTER);
		setWindowStyle(false, BS_RIGHT);
		setWindowStyle(false, BS_LEFT);
	}
};

#endif