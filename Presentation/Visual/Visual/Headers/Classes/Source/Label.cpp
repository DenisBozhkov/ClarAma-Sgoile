#include "../Headers/Label.h"
void Visual::Label::initProperties()
{
	IComponent::initProperties();
	Assign(Alignment,Property<Align,Label>(this,
			Property<Align,Label>::DefaultGet,
			[](Label* now,Align* dest,Align value)
			{
				*dest=value;
				if(now->created)
					switch(*dest)
					{
						case Left:
							SetWindowLongPtr(*now,GWL_STYLE,(GetWindowLongPtr(*now,GWL_STYLE)&~(SS_LEFT|SS_CENTER|SS_RIGHT))|SS_LEFT);
							break;
						case Center:
							SetWindowLongPtr(*now,GWL_STYLE,(GetWindowLongPtr(*now,GWL_STYLE)&~(SS_LEFT|SS_CENTER|SS_RIGHT))|SS_CENTER);
							break;
						case Right:
							SetWindowLongPtr(*now,GWL_STYLE,(GetWindowLongPtr(*now,GWL_STYLE)&~(SS_LEFT|SS_CENTER|SS_RIGHT))|SS_RIGHT);
							break;
					}
			}
	));
	Assign(Text,Property<std::string,Label>(this,
			Property<std::string,Label>::DefaultGet,
			[](Label* now,std::string* dest,std::string value)
			{
				*dest=value;
				if(now->created)
					SetWindowText(*now,value.c_str());
			}
	));
}
void Visual::Label::Create()
{
	if(!created)
	{
		long long style=this->style;
		if(Visible)style|=WS_VISIBLE;
		if(Disabled)style|=WS_DISABLED;
		if(VScroll)style|=WS_VSCROLL;
		if(HScroll)style|=WS_HSCROLL;
		if((IComponent*)Parent!=NULL)style|=WS_CHILD;
		switch((Align)Alignment)
		{
			case Left:
				style|=SS_LEFT;
				break;
			case Center:
				style|=SS_CENTER;
				break;
			case Right:
				style|=SS_RIGHT;
				break;
		}

		hwnd=CreateWindowEx(
			0,
			"Static",
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
Visual::Label::Label()
	:IComponent()
{
	initProperties();
	style=0;
	Text="";
}