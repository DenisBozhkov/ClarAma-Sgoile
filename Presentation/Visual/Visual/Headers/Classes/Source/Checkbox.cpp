#include "../Headers/Checkbox.h"
void Visual::Checkbox::initProperties()
{
	Assign(Checked,Property<bool,Checkbox>(this,
		[](Checkbox* now,bool* dest)
		{
			if(now->created)
				*dest=(SendMessage(*now,BM_GETCHECK,0,0)==BST_CHECKED);
			return *dest;
		},
		[](Checkbox* now,bool* dest,bool value)
		{
			*dest=value;
			if(now->created)
				SendMessage(*now,BM_SETCHECK,(value)?BST_CHECKED:BST_UNCHECKED,0);
			now->OnClick(now);
		}
	));
}
void Visual::Checkbox::SetNoTriggerChecked(bool checked)
{
	SendMessage(hwnd,BM_SETCHECK,(checked)?BST_CHECKED:BST_UNCHECKED,0);
}
void Visual::Checkbox::Create()
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
		if(Checked)
			SendMessage(hwnd,BM_SETCHECK,BST_CHECKED,0);
		IComponent::Create();
	}
}
int Visual::Checkbox::Procedure(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg==WM_COMMAND&&(HWND)lParam==(HWND)*this)
	{
		if(HIWORD(wParam)==BN_CLICKED)
			OnClick(this);
	}
	return 0;
}
Visual::Checkbox::Checkbox()
	:Button()
	{
		initProperties();
		style=WS_TABSTOP|BS_NOTIFY|BS_AUTOCHECKBOX;
		Checked=false;
	}