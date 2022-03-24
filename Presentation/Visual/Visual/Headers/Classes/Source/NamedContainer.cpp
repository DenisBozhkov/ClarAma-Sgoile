#include "../Headers/NamedContainer.h"
void Visual::NamedContainer::Create()
{
	if(!created)
	{
		long long style=this->style;
		if(Visible)style|=WS_VISIBLE;
		if(Disabled)style|=WS_DISABLED;
		if(VScroll)style|=WS_VSCROLL;
		if(HScroll)style|=WS_HSCROLL;
		if((IComponent*)Parent!=NULL)style|=WS_CHILD;
		
		WNDCLASS wc;
		GetClassInfo(NULL,"Button",&wc);
		this->oldProc=wc.lpfnWndProc;
		if(!GetClassInfo(NULL,"ButtonEx",&wc))
		{
			GetClassInfo(NULL,"Button",&wc);
			wc.lpszClassName="ButtonEx";
			wc.lpfnWndProc=IComponent::StaticProcedure;
			RegisterClass(&wc);
		}
		
		hwnd=CreateWindowEx(
			WS_EX_CONTROLPARENT,
			"ButtonEx",
			Name->c_str(),
			style,
			X,Y,Width,Height,
			((IComponent*)Parent!=NULL)?(HWND)*(IComponent*)Parent:NULL,
			NULL,
			NULL,
			this
		);
		IComponent::Create();
		for(int i=0;i<elements.size();i++)
			elements[i]->Create();
	}
}
int Visual::NamedContainer::Procedure(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{ return Container::Procedure(hwnd,msg,wParam,lParam);  }
Visual::NamedContainer::NamedContainer()
	:Container()
	{
		initProperties();
		style=BS_GROUPBOX;
		Name="";
	}
void Visual::NamedContainer::initProperties()
{
	
	Container::initProperties();
	Assign(Name,Property<std::string,NamedContainer>(this,
			Property<std::string,NamedContainer>::DefaultGet,
			[](NamedContainer* now,std::string* dest,std::string value)
			{
				*dest=value;
				if(now->created)
					SetWindowText(*now,value.c_str());
			}
	));
}