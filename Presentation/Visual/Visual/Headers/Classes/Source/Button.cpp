#include "../Headers/Button.h"
void Visual::Button::Create()
{
	if(!created)
	{
		long long style=this->style;
		if(Visible)style|=WS_VISIBLE;
		if(Disabled)style|=WS_DISABLED;
		if(VScroll)style|=WS_VSCROLL;
		if(HScroll)style|=WS_HSCROLL;
		if((IComponent*)Parent!=NULL)style|=WS_CHILD;
		
		hwnd=CreateWindowEx(
			0,
			"Button",
			((std::string)Text).c_str(),
			style,
			X,
			Y,
			Width,
			Height,
			((IComponent*)Parent!=NULL)?(HWND)*(IComponent*)Parent:NULL,
			NULL,
			NULL,
			this
		);
		IComponent::Create();
	}
}
int Visual::Button::Procedure(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg==WM_COMMAND&&(HWND)lParam==(HWND)*this)
		if(HIWORD(wParam)==BN_CLICKED)
			OnClick(this);
		else if(HIWORD(wParam)==BN_DOUBLECLICKED)
			OnDoubleClick(this);
	return 0;
}
Visual::Button::Button()
	:Label(),IClickable(){style=WS_TABSTOP|BS_NOTIFY|BS_VCENTER;}