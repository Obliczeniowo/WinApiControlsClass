#include "wndlistbox.h"

void WndListBox::getSelectedItemsIndexArray(std::vector<int> &itemArray){
	int selected = getSelectedItemCount();
	if(selected > 0){
		int *indexes = new int[selected];

		if(LB_ERR != SendMessage(hWnd, LB_GETSELITEMS, selected, (LPARAM)indexes)){
			for(int* i = indexes; i < indexes + selected; i++){
				itemArray.push_back(*i);
			}
		}

		delete [] indexes;
	}
}

std::string WndListBox::getItemText(int index) const {
	std::string t;
	if(index > -1){
		int length = (int)SendMessage(hWnd, LB_GETTEXTLEN, index, NULL);
		char* text = new char[length + 1];
		SendMessage(hWnd, LB_GETTEXT, index, (LPARAM)text);
		t = text;
		delete [] text;
	}
	return t;
}