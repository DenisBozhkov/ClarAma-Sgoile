#ifndef RADIOBUTTONGROUP_H
#define RADIOBUTTONGROUP_H

#include "Container.h"
#include "RadioButton.h"

BEGIN
eclass RadioButtonGroup:public virtual Container
{
	public:
		Property<RadioButton*,RadioButtonGroup> Selected;

		int SelectedIndex(int);
		void ClearSelection();
		
		virtual void Add(RadioButton*);
		virtual RadioButton* Remove(int);
		virtual void RemoveAndDelete(int);
		virtual RadioButton* operator[](int);
		
		virtual void Create();
		virtual void Destroy();
		int Procedure(HWND,UINT,WPARAM,LPARAM);
		
		RadioButtonGroup();
	protected:
		void initProperties();
}
END

#endif