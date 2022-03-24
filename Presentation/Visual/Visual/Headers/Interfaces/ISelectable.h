#ifndef VSELECTABLE_H
#define VSELECTABLE_H

#include "../config.h"

BEGIN
template<class T,class B> einterface ISelectable
{
	Property<T,B> Selection;
	
	exec OnSelect;
	exec OnUnselect;
	
	virtual int Procedure(HWND,UINT,WPARAM,LPARAM)=0;
	
	protected:
		virtual void initProperties()=0;
		ISelectable()
			:OnSelect([](void*){}),
			OnUnselect([](void*){})
			{}
}
END
#endif