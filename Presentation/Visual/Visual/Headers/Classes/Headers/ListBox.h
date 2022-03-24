#ifndef LISTBOX_H
#define LISTBOX_H

#include "IContainer.h"
#include "IComponent.h"
#include "ISelectable.h"

BEGIN
eclass ListBox:public IComponent,public IContainer<const std::string>,public ISelectable<int,ListBox>
{
	public:
		virtual void AddOn(std::string*,int);
		virtual void Update(std::string*,int);
		virtual void SetSelection(int);
		virtual void SetItemData(void*,int);
		virtual void* GetItemData(int);
		virtual int GetIndex(std::string);

		virtual void Add(const std::string*);
		virtual const std::string* Remove(int);
		virtual void RemoveAndDelete(int);
		virtual const std::string* operator[](int);
		virtual void Clear();
		
		virtual void Create();
		virtual int Procedure(HWND,UINT,WPARAM,LPARAM);
		
		ListBox();
	protected:
		virtual void initProperties();
}
END

#endif