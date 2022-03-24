#ifndef WINDOW_H
#define WINDOW_H

#include "NamedContainer.h"
#include "IResizable.h"

BEGIN
eclass Window:public NamedContainer,public IResizable
{
	WNDCLASSEX wc;
	LPSTR iconId;
	HMENU menuId;
	public:
		virtual void Create();
		virtual int Procedure(HWND,UINT,WPARAM,LPARAM);
		void Loop();
		Window(bool=false,bool=true,bool=true,LPSTR=IDI_APPLICATION,HMENU={0});
}
END

#endif