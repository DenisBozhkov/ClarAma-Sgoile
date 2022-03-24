#include "Headers/GlobalWindow.h"
#include<cstdio>
using Service::Controller;
using Visual::Window;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Controller controller;
	Window* rw=new GlobalWindow(controller);
	rw->X=CW_USEDEFAULT;
	rw->Y=CW_USEDEFAULT;
	rw->Width=550;
	rw->Height=11*MARGIN+5*EDITSIZE+6*TEXTSIZE+EXTRA;
	rw->Name="globalWindow";
	rw->Create();
	rw->Loop();
	rw->Destroy();
	delete rw;
	return 0;
}