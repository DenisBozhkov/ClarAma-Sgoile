#include "../Headers/ListBox.h"
void Visual::ListBox::AddOn(std::string* item,int index)
{
	ListBox_InsertString(hwnd,index,item->c_str());
	elements.insert(elements.begin()+index,item);
	Assign(Size,Size+1);
}
void Visual::ListBox::Update(std::string* item,int index)
{
	void* save=GetItemData(index);
	Remove(index);
	AddOn(item,index);
	SetItemData(save,index);
}
void Visual::ListBox::SetSelection(int index)
{
	ListBox_SetCurSel(hwnd,index);
}
void Visual::ListBox::SetItemData(void* data,int index)
{
	ListBox_SetItemData(hwnd,index,data);
}
void* Visual::ListBox::GetItemData(int index)
{
	return (void*)ListBox_GetItemData(hwnd,index);
}
int Visual::ListBox::GetIndex(std::string item)
{
	return ListBox_FindStringExact(hwnd,-1,item.c_str());
}

void Visual::ListBox::Add(const std::string* item)
{
	ListBox_AddString(hwnd,item->c_str());
	elements.push_back(item);
	Assign(Size,Size+1);
}
const std::string* Visual::ListBox::Remove(int index)
{
	const std::string* deleted=elements[index];
	ListBox_DeleteString(hwnd,index);
	elements.erase(elements.begin()+index);
	Assign(Size,Size-1);
	return deleted;
}
void Visual::ListBox::RemoveAndDelete(int index)
{ Remove(index); }
const std::string* Visual::ListBox::operator[](int index)
{ return elements[index]; }
void Visual::ListBox::Clear()
{
	IContainer<const std::string>::Clear();
	SendMessage(hwnd,LB_RESETCONTENT,0,0);
	Assign(Size,0);
}

void Visual::ListBox::Create()
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
			"ListBox",
			"",
			style,
			X,Y,Width,Height,
			((IComponent*)Parent!=NULL)?(HWND)*(IComponent*)Parent:NULL,
			NULL,
			NULL,
			this
		);
		IComponent::Create();
	}
}
int Visual::ListBox::Procedure(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg==WM_COMMAND&&(HWND)lParam==(HWND)*this)
		if(HIWORD(wParam)==LBN_SELCHANGE)
			if(Selection!=-1)OnSelect(this);
			else OnUnselect(this);
	return 0;
}
Visual::ListBox::ListBox()
	:IComponent(),IContainer<const std::string>(),ISelectable()
{ 
	initProperties();
	style=WS_BORDER|LBS_NOTIFY;
	VScroll=true;
	Assign(Selection,-1);
}

void Visual::ListBox::initProperties()
{
	Assign(Selection,Property<int,ListBox>(this,
		[](ListBox* now,int* dest)
		{ return *dest=ListBox_GetCurSel(*now); },
		[](ListBox* now,int* dest,int value)
		{
			*dest=value;
			ListBox_SetCurSel(*now,value);
		}
	));
}