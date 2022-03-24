#include "../Headers/RadioButtonGroup.h"
int Visual::RadioButtonGroup::SelectedIndex(int index)
{

	if(index==-1)
	{
		for(int i=0;i<elements.size();i++)
			if(((RadioButton*)elements[i])->Checked)
				return i;
		return -1;
	}
	for(int i=0;i<elements.size();i++)
		if(((RadioButton*)elements[i])->Checked)
			if(i==index)return index;
			else ((RadioButton*)elements[i])->Checked=false;
	((RadioButton*)elements[index])->Checked=true;
	return index;
}
void Visual::RadioButtonGroup::ClearSelection()
{
	for(int i=0;i<elements.size();i++)
		if(((RadioButton*)elements[i])->Checked)
		{
			((RadioButton*)elements[i])->Checked=false;
			break;
		}
}
void Visual::RadioButtonGroup::Add(RadioButton* item)
{
	if(elements.size()==0)
		SetWindowLongPtr(*item,GWL_STYLE,GetWindowLongPtr(*item,GWL_STYLE)|WS_GROUP);
	Container::Add(item);
}
Visual::RadioButton* Visual::RadioButtonGroup::Remove(int index)
{
	if(index==0&&elements.size()>1)
		SetWindowLongPtr(*elements[index+1],GWL_STYLE,GetWindowLongPtr(*elements[index+1],GWL_STYLE)|WS_GROUP);
	return (RadioButton*)Container::Remove(index);
}
void Visual::RadioButtonGroup::RemoveAndDelete(int index)
{
	elements[index]->Destroy();
	Remove(index);
}
Visual::RadioButton* Visual::RadioButtonGroup::operator[](int index)
{ return (RadioButton*)elements[index]; }
void Visual::RadioButtonGroup::Create()
{ Container::Create(); }
void Visual::RadioButtonGroup::Destroy()
{ Container::Destroy(); }
int Visual::RadioButtonGroup::Procedure(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{ return Container::Procedure(hwnd,msg,wParam,lParam); }
Visual::RadioButtonGroup::RadioButtonGroup()
	:Container()
{ initProperties(); }
void Visual::RadioButtonGroup::initProperties()
{
	Container::initProperties();
	Assign(Selected,Property<RadioButton*,RadioButtonGroup>(this,
		[](RadioButtonGroup* now,RadioButton** dest)
		{
			for(int i=0;i<now->Size;i++)
				if((*now)[i]->Checked)
					return *dest=(*now)[i];
			return *dest=(RadioButton*)NULL;
		}
	));
}