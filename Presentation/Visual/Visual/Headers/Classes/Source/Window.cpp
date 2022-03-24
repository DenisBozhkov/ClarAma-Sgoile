#include "../Headers/Window.h"
void Visual::Window::Create()
{
	if(!created)
	{
		memset(&wc,0,sizeof(wc));
		wc.cbSize=sizeof(WNDCLASSEX);
		wc.lpfnWndProc=StaticProcedure;
		wc.hInstance=NULL;
		wc.hCursor=LoadCursor(NULL,IDC_ARROW);
		wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
		wc.lpszClassName="Window";
		wc.hIcon=LoadIcon(NULL,iconId);
		wc.hIconSm=LoadIcon(NULL,iconId);
		RegisterClassEx(&wc);
		
		long long style=this->style;
		if(Visible)style|=WS_VISIBLE;
		if(Disabled)style|=WS_DISABLED;
		if(VScroll)style|=WS_VSCROLL;
		if(HScroll)style|=WS_HSCROLL;
		this->hwnd=CreateWindowEx(
			WS_EX_CONTROLPARENT,
			"Window",
			((std::string)Name).c_str(),
			style,
			X,Y,Width,Height,
			((IComponent*)Parent!=nullptr)?(HWND)*(IComponent*)Parent:NULL,
			menuId,
			NULL,
			this
		);

		RECT rect;
		GetWindowRect(hwnd,&rect);
		Assign(X,(int)rect.left);
		Assign(Y,(int)rect.top);
		IComponent::Create();
		for(int i=0;i<elements.size();i++)
			elements[i]->Create();
	}
}
int Visual::Window::Procedure(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg==WM_DESTROY)
	{
		OnDestroy(this);
		if((IComponent*)Parent==nullptr)
			PostQuitMessage(0);
		return 0;
	}
	if(msg==WM_SIZE)
	{
		Assign(Width,(int)LOWORD(lParam));
		Assign(Height,(int)HIWORD(lParam));
		OnResize(this);
		return 0;
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}
void Visual::Window::Loop()
{
	static MSG Msg;
	while(GetMessage(&Msg,NULL,0,0)>0)
		if(!IsDialogMessage(hwnd,&Msg))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
}
Visual::Window::Window(bool maximize,bool maxable,bool resize,LPSTR iconId,HMENU menuId)
	:NamedContainer(),IResizable(),iconId(iconId),menuId(menuId)
{
	style=WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU;
	if(maxable)style|=(WS_MINIMIZEBOX|WS_MAXIMIZEBOX);
	if(maximize)style|=WS_MAXIMIZE;
	if(resize)style|=WS_SIZEBOX;
	InitCommonControls();
}