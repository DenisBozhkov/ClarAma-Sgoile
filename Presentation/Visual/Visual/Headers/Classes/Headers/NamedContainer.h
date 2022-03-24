#ifndef NAMEDCONTAINER_H
#define NAMEDCONTAINER_H

#include "Container.h"

BEGIN
eclass NamedContainer:public Container
{
	public:
		Property<std::string,NamedContainer> Name;
		virtual void Create();
		virtual int Procedure(HWND,UINT,WPARAM,LPARAM);
		NamedContainer();
	private:
		virtual void initProperties();
}
END

#endif