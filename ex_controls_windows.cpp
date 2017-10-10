#include "ex_controls_windows.h"

BOOL initializeControls(int init_icc){
	INITCOMMONCONTROLSEX	iccex;
	iccex.dwICC				= init_icc;
	iccex.dwSize			= sizeof(INITCOMMONCONTROLSEX);
	return InitCommonControlsEx(&iccex);
}