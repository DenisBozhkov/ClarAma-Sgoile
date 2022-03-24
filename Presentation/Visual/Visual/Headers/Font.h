#ifndef FONT_H
#define FONT_H

#include "config.h"

eclass Font
{
	HFONT font;
	public:
		void SetFont(HWND hwnd)
		{
			font=CreateFontW(-MulDiv(12,GetDeviceCaps(GetDC(hwnd),LOGPIXELSY),72),0,0,0,FW_NORMAL,false,false,false,RUSSIAN_CHARSET,0,0,0,0,L"Times New Roman");
			SendMessage(hwnd,WM_SETFONT,WPARAM(font),true);
		}
};

#endif