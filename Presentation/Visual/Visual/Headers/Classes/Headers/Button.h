#ifndef BUTTON_H
#define BUTTON_H

#include "Label.h"
#include "../../Interfaces/IClickable.h"

BEGIN
eclass Button:public Label,public IClickable
{
	public:
		virtual void Create() override;
		virtual int Procedure(HWND,UINT,WPARAM,LPARAM) override;
		Button();
}
END

#endif