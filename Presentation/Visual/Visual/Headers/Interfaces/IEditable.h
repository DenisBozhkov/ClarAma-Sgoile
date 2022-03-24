#ifndef VEDITABLE_H
#define VEDITABLE_H

#include "../config.h"

BEGIN
einterface IEditable
{
	exec OnEdit;
	
	virtual int Procedure(HWND,UINT,WPARAM,LPARAM)=0;
	
	protected:
		IEditable()
			:OnEdit([](void*){}){}
}
END
#endif