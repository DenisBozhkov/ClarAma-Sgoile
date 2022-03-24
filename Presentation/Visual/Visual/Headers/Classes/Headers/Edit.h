#ifndef EDIT_H
#define EDIT_H

#include "../../Interfaces/IEditable.h"
#include "Label.h"

BEGIN
eclass Edit:public Label,public IEditable
{
	public:
		virtual void Create();
		virtual int Procedure(HWND,UINT,WPARAM,LPARAM);
		Edit();
}
END

#endif