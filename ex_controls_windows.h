#ifndef EX_CONTROLS_WINDOW_H
#define EX_CONTROLS_WINDOW_H

#include "controls_windows.h"
#include <commctrl.h> // to use this you must add comctl32.lib

namespace icc{											// init common controls
	enum icc_init{
		animate_class		= ICC_ANIMATE_CLASS,		// Load animate control class. 
		bar_classes			= ICC_BAR_CLASSES,			// Load toolbar, status bar, trackbar, and ToolTip control classes. 
		cool_classes		= ICC_COOL_CLASSES,			// Load rebar control class. 
		date_classes		= ICC_DATE_CLASSES,			// Load date and time picker control class. 
		hotkey_class		= ICC_HOTKEY_CLASS,			// Load hot key control class. 
		internet_class		= ICC_INTERNET_CLASSES,		// Load IP address class. 
		link_class			= ICC_LINK_CLASS,			// Load a hyperlink control class. 
		listview_classes	= ICC_LISTVIEW_CLASSES,		// Load list-view and header control classes. 
		nativefntctl		= ICC_NATIVEFNTCTL_CLASS,	// Load a native font control class. 
		pagescroller_class	= ICC_PAGESCROLLER_CLASS,	// Load pager control class. 
		progress_class		= ICC_PROGRESS_CLASS,		// Load progress bar control class. 
		standard_classes	= ICC_STANDARD_CLASSES,		// Load one of the intrinsic User32 control classes. The user controls include button, edit, static, listbox, combobox, and scrollbar. 
		tab_classes			= ICC_TAB_CLASSES,			// Load tab and ToolTip control classes. 
		treeview_classes	= ICC_TREEVIEW_CLASSES,		// Load tree-view and ToolTip control classes. 
		updown_class		= ICC_UPDOWN_CLASS,			// Load up-down control class. 
		userex_classes		= ICC_USEREX_CLASSES,		// Load ComboBoxEx class. 
		wni95_classes		= ICC_WIN95_CLASSES			// Load animate control, header, hot key, list-view, progress bar, status bar, tab, ToolTip, toolbar, trackbar, tree-view, and up-down control classes. 
	};
}

BOOL initializeControls(int init_icc){
	INITCOMMONCONTROLSEX	iccex;
	iccex.dwICC				= init_icc;
	iccex.dwSize			= sizeof( INITCOMMONCONTROLSEX );
	return InitCommonControlsEx( &iccex );
}

#endif