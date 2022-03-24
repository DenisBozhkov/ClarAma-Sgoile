#ifndef COMBOBOX_H
#define COMBOBOX_H

#include "IContainer.h"
#include "IComponent.h"
#include "ISelectable.h"

BEGIN
eclass ComboBox:public IComponent,public IContainer<const std::string>,public ISelectable<int,ComboBox>
{
	public:
		virtual void AddOn(std::string*,int);
		virtual void Update(std::string*,int);
		void SetSelection(int);
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

		ComboBox();
	protected:
		virtual void initProperties();
}
END

#endif