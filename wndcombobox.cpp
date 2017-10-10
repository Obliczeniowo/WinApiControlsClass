#include "wndcombobox.h"

std::string WndComboBox::getSelectedText() const {
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

std::string WndComboBox::getEditText() const {
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