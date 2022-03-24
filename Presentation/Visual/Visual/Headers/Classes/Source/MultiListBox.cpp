#include "../Headers/MultiListBox.h"
void Visual::MultiListBox::AddOn(std::string* item,int index)
{
	ListBox_InsertString(hwnd,index,item->c_str());
	elements.insert(elements.begin()+index,item);
	Assign(Size,Size+1);
}
void Visual::MultiListBox::Update(std::string* item,int index)
{
	void* save=GetItemData(index);
	Remove(index);
	AddOn(item,index);
	SetItemData(save,index);
}
void Visual::MultiListBox::SetSelection(int index,bool sel)
{
	ListBox_SetSel(hwnd,sel,index);
}
void Visual::MultiListBox::SetItemData(void* data,int index)
{
	ListBox_SetItemData(hwnd,index,data);
}
void* Visual::MultiListBox::GetItemData(int index)
{
	return (void*)ListBox_GetItemData(hwnd,index);
}
int Visual::MultiListBox::GetIndex(std::string item)
{
	return ListBox_FindStringExact(hwnd,-1,item.c_str());
}

void Visual::MultiListBox::Add(const std::string* item)
{
	ListBox_AddString(hwnd,item->c_str());
	elements.push_back(item);
	Assign(Size,Size+1);
}
const std::string* Visual::MultiListBox::Remove(int index)
{
	const std::string* deleted=elements[index];
	ListBox_DeleteString(hwnd,index);
	elements.erase(elements.begin()+index);
	Assign(Size,Size-1);
	return deleted;
}
void Visual::MultiListBox::RemoveAndDelete(int index)
{ Remove(index); }
const std::string* Visual::MultiListBox::operator[](int index)
{ return elements[index]; }
void Visual::MultiListBox::Clear()
{
	IContainer<const std::string>::Clear();
	SendMessage(hwnd,LB_RESETCONTENT,0,0);
	Assign(Size,0);
}

void Visual::MultiListBox::Create()
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
int Visual::MultiListBox::Procedure(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg==WM_COMMAND&&(HWND)lParam==(HWND)*this)
		if(HIWORD(wParam)==LBN_SELCHANGE)
			OnSelect(this);
	return 0;
}
Visual::MultiListBox::MultiListBox()
	:IComponent(),IContainer<const std::string>(),ISelectable()
{ 
	initProperties();
	VScroll=true;
	style=WS_BORDER|LBS_NOTIFY|LBS_MULTIPLESEL;
}

void Visual::MultiListBox::initProperties()
{
	Assign(Selection,Property<std::vector<int>,MultiListBox>(this,
		[](MultiListBox* now,std::vector<int>* dest)
		{
			static int buffer[256],size,i;
			*dest=std::vector<int>();
			size=ListBox_GetSelCount(*now);
			ListBox_GetSelItems(*now,256,buffer);
			for(i=0;i<size;i++)
				dest->push_back(buffer[i]);
			return *dest;
		},
		[](MultiListBox* now,std::vector<int>* dest,std::vector<int> value)
		{
			static int i,j,size;
			size=ListBox_GetCount(*now);
			if(value.size()==0)
			{
				for(i=0;i<size;i++)
					ListBox_SetSel(*now,i,false);
					return;
			}
			j=0;
			for(i=0;i<size;i++)
				if(j==value.size()||value[j]!=i)ListBox_SetSel(*now,i,false);
			    else
			    {
			     	ListBox_SetSel(*now,i,true);
			     	j++;
			    }
		}
	));
}