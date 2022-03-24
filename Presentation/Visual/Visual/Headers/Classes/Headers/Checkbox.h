#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "Button.h"

BEGIN
eclass Checkbox:public Button
{
	public:
		P(Checkbox,bool) Checked;

		virtual void SetNoTriggerChecked(bool);

		virtual void Create();
		virtual int Procedure(HWND,UINT,WPARAM,LPARAM);
		Checkbox();
	protected:
		void initProperties();
}
END

#endif