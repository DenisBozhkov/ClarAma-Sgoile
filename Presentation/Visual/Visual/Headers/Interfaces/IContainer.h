#ifndef VCONTAINER_H
#define VCONTAINER_H

#include "../config.h"

BEGIN
template<class vType,class cType=std::vector<vType*>> einterface IContainer
{
	exec OnAdd;
	exec OnChange;
	exec OnRemove;
	
	virtual void Add(vType*)=0;
	virtual vType* Remove(int)=0;
	virtual void RemoveAndDelete(int)=0;
	virtual vType* operator[](int)=0;

	virtual void Clear()
	{ elements=cType(); }
	
	P(IContainer,int) Size;
	
	virtual int Procedure(HWND,UINT,WPARAM,LPARAM)=0;
	
	protected:
		cType elements;
		IContainer()
			:OnAdd([](void*){}),
			OnChange([](void*){}),
			OnRemove([](void*){})
			{
				Assign(Size,Property<int,IContainer>(this,Property<int,IContainer>::DefaultGet));
				Assign(Size,0);
			}
}
END
#endif