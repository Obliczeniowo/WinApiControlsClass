#ifndef WNDEDIT_H
#define WNDEDIT_H

#include "controls_windows.h"

namespace ws{
	namespace edit{
		enum ed_style{
			es_autohscroll		= ES_AUTOHSCROLL,		// Automatically scrolls text to the right by 10 characters when the user types a character at the end of the line. When the user presses the ENTER key, the control scrolls all text back to position zero.
			es_autovscroll		= ES_AUTOVSCROLL,		// Automatically scrolls text up one page when the user presses the ENTER key on the last line.
			es_center			= ES_CENTER,			// Windows 98/Me, Windows 2000/XP: Centers text in a single-line or multiline edit control.
														// Windows 95, Windows NT 4.0 and earlier: Centers text in a multiline edit control.
			es_left				= ES_LEFT,				// Aligns text with the left margin.
			es_lowercase		= ES_LOWERCASE,			// Converts all characters to lowercase as they are typed into the edit control.
														// To change this style after the control has been created, use SetWindowLong.
			es_multiline		= ES_MULTILINE,			// Designates a multiline edit control. The default is single-line edit control. 
														// When the multiline edit control is in a dialog box, the default response to pressing the ENTER key is to activate the default button. To use the ENTER key as a carriage return, use the ES_WANTRETURN style.
														// When the multiline edit control is not in a dialog box and the ES_AUTOVSCROLL style is specified, the edit control shows as many lines as possible and scrolls vertically when the user presses the ENTER key. If you do not specify ES_AUTOVSCROLL, the edit control shows as many lines as possible and beeps if the user presses the ENTER key when no more lines can be displayed.
														// If you specify the ES_AUTOHSCROLL style, the multiline edit control automatically scrolls horizontally when the caret goes past the right edge of the control. To start a new line, the user must press the ENTER key. If you do not specify ES_AUTOHSCROLL, the control automatically wraps words to the beginning of the next line when necessary. A new line is also started if the user presses the ENTER key. The window size determines the position of the Wordwrap. If the window size changes, the Wordwrapping position changes and the text is redisplayed.
														// Multiline edit controls can have scroll bars. An edit control with scroll bars processes its own scroll bar messages. Note that edit controls without scroll bars scroll as described in the previous paragraphs and process any scroll messages sent by the parent window.
			es_nohidesel		= ES_NOHIDESEL,			// Negates the default behavior for an edit control. The default behavior hides the selection when the control loses the input focus and inverts the selection when the control receives the input focus. If you specify ES_NOHIDESEL, the selected text is inverted, even if the control does not have the focus.
			es_number			= ES_NUMBER,			// Allows only digits to be entered into the edit control. Note that, even with this set, it is still possible to paste non-digits into the edit control.
														// To change this style after the control has been created, use SetWindowLong.
			es_oemconvert		= ES_OEMCONVERT,		// Converts text entered in the edit control. The text is converted from the Windows character set to the OEM character set and then back to the Windows character set. This ensures proper character conversion when the application calls the CharToOem function to convert a Windows string in the edit control to OEM characters. This style is most useful for edit controls that contain file names that will be used on file systems that do not support Unicode. 
														// To change this style after the control has been created, use SetWindowLong. 
			es_password			= ES_PASSWORD,			// Displays an asterisk (*) for each character typed into the edit control. This style is valid only for single-line edit controls. 
														// Windows XP: If the edit control is from user32.dll, the default password character is an asterisk. However, if the edit control is from comctl32.dll version 6, the default character is a black circle. 
														// To change the characters that is displayed, or set or clear this style, use the EM_SETPASSWORDCHAR message. 
														// Note  Comctl32.dll version 6 is not redistributable but it is included in Microsoft Windows XP or later. To use Comctl32.dll version 6, specify it in a manifest. For more information on manifests, see Enabling Visual Styles.
			es_readonly			= ES_READONLY,			// Prevents the user from typing or editing text in the edit control.
														// To change this style after the control has been created, use the EM_SETREADONLY message. 
			es_right			= ES_RIGHT,				// Windows 98/Me, Windows 2000/XP: Right-aligns text in a single-line or multiline edit control. Windows 95, Windows NT 4.0 and earlier: Right aligns text in a multiline edit control.
			es_uppercase		= ES_UPPERCASE,			// Converts all characters to uppercase as they are typed into the edit control. 
														// To change this style after the control has been created, use SetWindowLong.
			es_wantreturn		= ES_WANTRETURN			// Specifies that a carriage return be inserted when the user presses the ENTER key while entering text into a multiline edit control in a dialog box. If you do not specify this style, pressing the ENTER key has the same effect as pressing the dialog box's default push button. This style has no effect on a single-line edit control. 
														// To change this style after the control has been created, use SetWindowLong.
		};
	}
}

class WndEdit : public IControlWindow{
public:
	enum notifications{
		align_ltr_ec	= EN_ALIGN_LTR_EC,
		align_rtl_ec	= EN_ALIGN_RTL_EC,
		change			= EN_CHANGE,
		errspace		= EN_ERRSPACE,
		hscroll			= EN_HSCROLL,
		killfocus		= EN_KILLFOCUS,
		maxtext			= EN_MAXTEXT,
		setfocus		= EN_SETFOCUS,
		update			= EN_UPDATE,
		vscroll			= EN_VSCROLL
		//ctlcoloredit	= WM_CTLCOLOREDIT
	};
public:
	WndEdit(LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam){
		createWindow( lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}

	void createWindow(LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam){
		if(hWnd){
			DestroyWindow(hWnd);
		}

		hWnd = CreateWindowEx(NULL, "EDIT", lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	};

	std::string getSelectedText() const {
		std::string text = getWindowText();

		DWORD begin = 0;
		DWORD end = 0;

		if(SendMessage(hWnd, EM_GETSEL, (WPARAM)&begin, (LPARAM) &end) != -1){
			if(begin != end)
				return text.substr(begin,end + 1);
		}
		return std::string("");
	}

	inline void setSelectedText(LONG begin, LONG end){
		SendMessage(hWnd, EM_SETSEL, (WPARAM) begin, (LPARAM) end);
	}

	inline void replaceSelectedText(std::string text){
		SendMessage(hWnd, EM_REPLACESEL, TRUE, (LPARAM)text.c_str());
	}

	inline void setLimitText(int limit){
		SendMessage(hWnd, EM_SETLIMITTEXT, (WPARAM) limit, NULL);
	}

	inline int getLimitText() const{
		return (int) SendMessage(hWnd, EM_GETLIMITTEXT, NULL, NULL);
	}

	inline void setPasswordChar(char character){
		SendMessage(hWnd, EM_SETPASSWORDCHAR, (WPARAM)character, NULL);
	}

	inline char getPasswordChar() const {
		return SendMessage(hWnd, EM_GETPASSWORDCHAR, NULL, NULL);
	}

	void setNumeric(bool numeric){
		setWindowStyle(numeric, ES_NUMBER);
	}

	bool isNumericOnly() const {
		return GetWindowLong(hWnd, GWL_STYLE) & ES_NUMBER;
	}

	void setNoHideSelection(bool noHideSelection){
		setWindowStyle(noHideSelection,  ES_NOHIDESEL);
	}

	void setLowerCase(bool lowerCase){
		setWindowStyle(lowerCase, ES_LOWERCASE);
	}

	void setUpperCase(bool upperCase){
		if(upperCase)
			setLowerCase(false);
		setWindowStyle(upperCase, ES_UPPERCASE);
	}

	void setTextToLeft(){
		setWindowStyle(false, ES_CENTER);
		setWindowStyle(false, ES_RIGHT);
		setWindowStyle(true, ES_LEFT);
	}

	void setTextToRight(){
		setWindowStyle(false, ES_CENTER);
		setWindowStyle(true, ES_RIGHT);
		setWindowStyle(false, ES_LEFT);
	}

	void setTextToCenter(){
		setWindowStyle(true, ES_CENTER);
		setWindowStyle(false, ES_RIGHT);
		setWindowStyle(false, ES_LEFT);
	}
};

#endif