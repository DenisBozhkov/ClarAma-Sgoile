#ifndef CONTAINER_H
#define CONTAINER_H

#include "../../Interfaces/IComponent.h"
#include "../../Interfaces/IContainer.h"

BEGIN
eclass Container:public IComponent,public IContainer<IComponent>
{
	public:
		virtual void Create();
		virtual void Destroy();
		virtual int Procedure(HWND,UINT,WPARAM,LPARAM);
		
		virtual void Add(IComponent*);
		virtual IComponent* Remove(int);
		virtual void RemoveAndDelete(int);
		virtual IComponent* operator[](int);
		
		Container();
}
END

#endif