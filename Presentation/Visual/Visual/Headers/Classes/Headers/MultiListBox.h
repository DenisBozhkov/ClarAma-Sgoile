#ifndef MULTILISTBOX_H
#define MULTILISTBOX_H

#include "IContainer.h"
#include "IComponent.h"
#include "ISelectable.h"

BEGIN
eclass MultiListBox:public IComponent,public IContainer<const std::string>,public ISelectable<std::vector<int>,MultiListBox>
{
	public:
		void AddOn(std::string*,int);
		void Update(std::string*,int);
		void SetSelection(int,bool);
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
		
		MultiListBox();
	protected:
		virtual void initProperties();
}
END

#endif