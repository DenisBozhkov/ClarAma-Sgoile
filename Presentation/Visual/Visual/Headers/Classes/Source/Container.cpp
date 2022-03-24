#include "../Headers/Container.h"
void Visual::Container::Create()
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
		GetClassInfo(NULL,"Static",&wc);
		this->oldProc=wc.lpfnWndProc;
		if(!GetClassInfo(NULL,"StaticEx",&wc))
		{
			GetClassInfo(NULL,"Static",&wc);
			wc.lpszClassName="StaticEx";
			wc.lpfnWndProc=IComponent::StaticProcedure;
			RegisterClass(&wc);
		}
		
		this->hwnd=CreateWindowEx(
			WS_EX_CONTROLPARENT,
			"StaticEx",
			"",
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
void Visual::Container::Destroy()
{
	for(int i=0;i<elements.size();i++)
		elements[i]->Destroy();
	IComponent::Destroy();
}
int Visual::Container::Procedure(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	for(int i=0;i<elements.size();i++)
		if((HWND)*elements[i]!=NULL)
			elements[i]->Procedure(hwnd,msg,wParam,lParam);
	return oldProc(hwnd,msg,wParam,lParam); 
}
void Visual::Container::Add(Visual::IComponent* element)
{
	SetParent(element,this);
	elements.push_back(element);
	Assign(Size,Size+1);
	OnAdd(this);
}
Visual::IComponent* Visual::Container::Remove(int index)
{
	IComponent* removed=elements[index];
	SetParent(elements[index],NULL);
	elements.erase(elements.begin()+index);
	Assign(Size,Size-1);
	OnRemove(this);
	return removed;
}
void Visual::Container::RemoveAndDelete(int index)
{
	elements[index]->Destroy();
	Remove(index);
}
Visual::IComponent* Visual::Container::operator[](int index)
{
	OnChange(this);
	return elements[index];
}
Visual::Container::Container()
	:IComponent(),IContainer<IComponent>()
	{style=0;}