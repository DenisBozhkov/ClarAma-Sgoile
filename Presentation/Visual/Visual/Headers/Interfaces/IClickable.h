#ifndef VCLICKABLE_H
#define VCLICKABLE_H

#include "../config.h"

BEGIN
einterface IClickable
{
	exec OnClick;
	exec OnDoubleClick;
	
	virtual int Procedure(HWND,UINT,WPARAM,LPARAM)=0;
	
	protected:
		IClickable()
			:OnClick([](void*){}),
			OnDoubleClick([](void*){}){}
}
END
#endif