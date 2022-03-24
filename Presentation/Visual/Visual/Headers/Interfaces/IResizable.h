#ifndef IRESIZABLE_H
#define IRESIZABLE_H

#include "../config.h"

BEGIN
einterface IResizable
{
	exec OnResize;

	virtual int Procedure(HWND,UINT,WPARAM,LPARAM)=0;

	protected:
		IResizable()
			:OnResize([](void*){}){}
}
END
#endif