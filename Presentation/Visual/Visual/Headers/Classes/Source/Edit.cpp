#include "../Headers/Edit.h"
void Visual::Edit::Create()
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
			"Edit",
			Text->c_str(),
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
int Visual::Edit::Procedure(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg==WM_COMMAND&&(HWND)lParam==(HWND)*this&&HIWORD(wParam)==EN_CHANGE)
	{
		char buff[256];
		GetWindowText((HWND)(*this),buff,256);
		Assign(this->Text,std::string(buff));
		OnEdit(this);
	}
	return 0;
}
Visual::Edit::Edit()
	:Label(),IEditable(){style=WS_TABSTOP|WS_BORDER|ES_AUTOHSCROLL;}