#include "../Headers/ComboBox.h"
void Visual::ComboBox::AddOn(std::string* item,int index)
{
	ComboBox_InsertString(hwnd,index,item->c_str());
	elements.insert(elements.begin()+index,item);
	Assign(Size,Size+1);
}
void Visual::ComboBox::Update(std::string* item,int index)
{
	void* save=GetItemData(index);
	Remove(index);
	AddOn(item,index);
	SetItemData(save,index);
}
void Visual::ComboBox::SetSelection(int index)
{
	ComboBox_SetCurSel(hwnd,index);
}
void Visual::ComboBox::SetItemData(void* data,int index)
{
	ComboBox_SetItemData(hwnd,index,(LPARAM)data);
}
void* Visual::ComboBox::GetItemData(int index)
{
	return (void*)ComboBox_GetItemData(hwnd,index);
}
int Visual::ComboBox::GetIndex(std::string item)
{
	return ComboBox_FindStringExact(hwnd,-1,item.c_str());
}

void Visual::ComboBox::Add(const std::string* item)
{
	ComboBox_AddString(hwnd,item->c_str());
	elements.push_back(item);
	Assign(Size,Size+1);
}
const std::string* Visual::ComboBox::Remove(int index)
{
	const std::string* deleted=elements[index];
	ComboBox_DeleteString(hwnd,index);
	elements.erase(elements.begin()+index);
	Assign(Size,Size-1);
	return deleted;
}
void Visual::ComboBox::RemoveAndDelete(int index)
{ Remove(index); }
const std::string* Visual::ComboBox::operator[](int index)
{ return elements[index]; }
void Visual::ComboBox::Clear()
{
	IContainer<const std::string>::Clear();
	SendMessage(hwnd,CB_RESETCONTENT,0,0);
	Assign(Size,0);
}

void Visual::ComboBox::Create()
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
			WC_COMBOBOX,
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
int Visual::ComboBox::Procedure(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg==WM_COMMAND&&(HWND)lParam==(HWND)*this)
		if(HIWORD(wParam)==CBN_SELCHANGE)
			if(Selection!=-1)OnSelect(this);
			else OnUnselect(this);
	return 0;
}
Visual::ComboBox::ComboBox()
	:IComponent(),IContainer<const std::string>(),ISelectable()
{
	initProperties();
	VScroll=true;
	style=WS_TABSTOP|WS_BORDER|CBS_DROPDOWNLIST|CBS_DISABLENOSCROLL;
	Assign(Selection,-1);
}

void Visual::ComboBox::initProperties()
{
	Assign(Selection,Property<int,ComboBox>(this,
		[](ComboBox* now,int* dest)
		{ return *dest=ComboBox_GetCurSel(*now); },
		[](ComboBox* now,int* dest,int value)
		{
			*dest=value;
			SendMessage(*now,CB_SETCURSEL,value,0);
		}
	));
}