#ifndef NOTIFICATIONS_COMMAND_CLASSES_H
#define NOTIFICATIONS_COMMAND_CLASSES_H

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
	WndTooltip*	tooltip;

	OnButtonClicked(WndButton* button, WndTooltip* tooltip) : button(button), tooltip(tooltip) {}

	virtual void notify(){
		MessageBox(button->getParentWindow(), "Klikn¹³eœ przycisk", "CLICKED", MB_OK);
		tooltip->addWmNotification(TTN_GETDISPINFO, new OnWmNotifyGetDispInfo(*tooltip, "Klikn¹³eœ, no nareszcie!"));
		tooltip->setTitle("Kwikn¹³eœ!!!");
	}
};

class OnCheckBoxButtonClicked : public INotificationCommand{
public:
	WndButton*	button;
	WndEdit*	edit;

	OnCheckBoxButtonClicked(WndButton* button, WndEdit* edit) : button(button), edit(edit) {}

	virtual void notify(){
		if(button->toggleButtonState() == WndButton::checkState::checked ){
			edit->setWindowText("Check box button checked");
		}else{
			edit->setWindowText("Check box button unchecked");
		}
	}
};

class OnRadioButtonClicked : public INotificationCommand{
public:
	WndButton*	button;
	WndEdit*	edit;

	OnRadioButtonClicked(WndButton* button, WndEdit* edit) : button(button), edit(edit) {}

	virtual void notify(){
		if(button->toggleButtonState() == WndButton::checkState::checked ){
			edit->setWindowText("Radio button checked");
		}else{
			edit->setWindowText("Radio button unchecked");
		}
	}
};

#endif