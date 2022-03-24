#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include "../config.h"
#include "../Font.h"

BEGIN
einterface IComponent
{
	P(IComponent,int) X;
	P(IComponent,int) Y;
	P(IComponent,int) Width;
	P(IComponent,int) Height;
	P(IComponent,bool) Visible;
	P(IComponent,bool) Disabled;
	P(IComponent,bool) VScroll;
	P(IComponent,bool) HScroll;
	P(IComponent,IComponent*) Parent;
	void* Data;

	operator HWND()
	{return hwnd;}
	virtual void Create()
	{
		created=true;
		font.SetFont(hwnd);
	}
	virtual void Destroy()
	{
		created=false;
		DestroyWindow(hwnd);
	}
	virtual int Procedure(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
	{ return 0; }
	virtual void Move(int x,int y,int width,int height)
	{
		Assign(X,x);
		Assign(Y,y);
		Assign(Width,width);
		Assign(Height,height);
		MoveWindow(hwnd,x,y,width,height,true);
	}
	friend void SetParent(IComponent* child,IComponent* newParent)
	{
		Assign(child->Parent,newParent);
		if(child->created)
		{
			if(newParent==NULL)
				::SetParent(*child,NULL);
			else
			{
				::SetParent(*child,*newParent);
				long long style=child->style;
				if(child->Visible)style|=WS_VISIBLE;
				if(child->Disabled)style|=WS_DISABLED;
				SetWindowLongPtr(*child,GWL_STYLE,style|WS_CHILD);
			}
			
		}
	}
	~IComponent(){ Destroy(); }
	exec OnDestroy;
	protected:
		Font font;
		WNDPROC oldProc;
		virtual void initProperties()
		{
			Assign(Width,Property<int,IComponent>(this,
				Property<int,IComponent>::DefaultGet,
				[](IComponent* now,int* dest,int value)
				{
					*dest=value;
					if(now->created)
						MoveWindow(*now,now->X,now->Y,now->Width,now->Height,true);
				}
			));
			Assign(Height,Property<int,IComponent>(this,
				Property<int,IComponent>::DefaultGet,
				[](IComponent* now,int* dest,int value)
				{
					*dest=value;
					if(now->created)
						MoveWindow(*now,now->X,now->Y,now->Width,now->Height,true);
				}
			));
			Assign(X,Property<int,IComponent>(this,
				Property<int,IComponent>::DefaultGet,
				[](IComponent* now,int* dest,int value)
				{
					*dest=value;
					if(now->created)
						MoveWindow(*now,now->X,now->Y,now->Width,now->Height,true);
				}
			));
			Assign(Y,Property<int,IComponent>(this,
				Property<int,IComponent>::DefaultGet,
				[](IComponent* now,int* dest,int value)
				{
					*dest=value;
					if(now->created)
						MoveWindow(*now,now->X,now->Y,now->Width,now->Height,true);
				}
			));
			Assign(Visible,Property<bool,IComponent>(this,
				Property<bool,IComponent>::DefaultGet,
				[](IComponent* now,bool* dest,bool value)
				{
					*dest=value;
					if(now->created)
						ShowWindow(*now,value);
				}
			));
			Assign(VScroll,Property<bool,IComponent>(this,
				Property<bool,IComponent>::DefaultGet,
				[](IComponent* now,bool* dest,bool value)
				{
					*dest=value;
					if(now->created)
						if(*dest)SetWindowLongPtr(*now,GWL_STYLE,GetWindowLongPtr(*now,GWL_STYLE)|WS_VSCROLL);
						else SetWindowLongPtr(*now,GWL_STYLE,GetWindowLongPtr(*now,GWL_STYLE)&(~WS_VSCROLL));
				}
			));
			Assign(HScroll,Property<bool,IComponent>(this,
				Property<bool,IComponent>::DefaultGet,
				[](IComponent* now,bool* dest,bool value)
				{
					*dest=value;
					if(now->created)
						if(*dest)SetWindowLongPtr(*now,GWL_STYLE,GetWindowLongPtr(*now,GWL_STYLE)|WS_HSCROLL);
						else SetWindowLongPtr(*now,GWL_STYLE,GetWindowLongPtr(*now,GWL_STYLE)&(~WS_HSCROLL));
				}
			));
			Assign(Disabled,Property<bool,IComponent>(this,
				Property<bool,IComponent>::DefaultGet,
				[](IComponent* now,bool* dest,bool value)
				{
					*dest=value;
					if(now->created)
						EnableWindow(*now,!value);
				}
			));
			Assign(Parent,Property<IComponent*,IComponent>(this,
				Property<IComponent*,IComponent>::DefaultGet));
		}
		IComponent()
			:created(false),
			 OnDestroy([](void*){})
			{
				initProperties();
				X=0;
				Y=0;
				Width=0;
				Height=0;
				Visible=true;
				Disabled=false;
				VScroll=false;
				HScroll=false;
				SetParent(this,NULL);
			}
		bool created;          
		HWND hwnd;
		LONG_PTR style;
		static LRESULT CALLBACK StaticProcedure(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
		{
			IComponent* now;
			if (msg==WM_CREATE)
			{
				now=static_cast<IComponent*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
				SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)now);
			}
			else now=reinterpret_cast<IComponent*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
			if(now)return now->Procedure(hwnd,msg,wParam,lParam);
			return DefWindowProc(hwnd,msg,wParam,lParam);
		}
}
END
#endif