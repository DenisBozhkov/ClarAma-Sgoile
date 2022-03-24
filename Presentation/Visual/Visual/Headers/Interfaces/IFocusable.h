#ifndef VFOCUSABLE_H
#define VFOCUSABLE_H

#include "../config.h"

BEGIN
einterface IFocusable
{
	exec OnFocused;
	exec OnFocusKilled;
	
	virtual int Procedure(HWND,UINT,WPARAM,LPARAM)=0;
	
	protected:
		IFocusable()
			:OnFocused([](void*){}),
			OnFocusKilled([](void*){}){}
}
END
#endif