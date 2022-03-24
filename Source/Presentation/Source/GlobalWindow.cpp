#include "Headers/GlobalWindow.h"
GlobalWindow::GlobalWindow(Controller &controller)
	:IActionable(controller),Window(true,true,true)
{
	roomsWindow=nullptr;
	subjectGroupsWindow=nullptr;
	subjectsWindow=nullptr;
	teachersWindow=nullptr;
}
GlobalWindow::~GlobalWindow()
{
	if(roomsWindow!=nullptr)
		delete roomsWindow;
	if(subjectGroupsWindow!=nullptr)
		delete subjectGroupsWindow;
	if(subjectsWindow!=nullptr)
		delete subjectsWindow;
	if(teachersWindow!=nullptr)
		delete teachersWindow;
	controller.SaveAll();
}
void GlobalWindow::Create()
{
	InitConsts();
	InitRelations();
	Window::Create();
	InitComponents();
	LoadData();

}
void GlobalWindow::InitComponents()
{
	container.X=0;
	container.Y=0;
	container.Width=Width;
	container.Height=Height;

	roomsButton.X=MARGIN;
	roomsButton.Y=MARGIN;
	roomsButton.Width=100;
	roomsButton.Height=EDITSIZE;

	subjectGroupsButton.X=MARGIN;
	subjectGroupsButton.Y=roomsButton.Y+EDITSIZE+MARGIN;
	subjectGroupsButton.Width=100;
	subjectGroupsButton.Height=EDITSIZE;

	subjectsButton.X=MARGIN;
	subjectsButton.Y=subjectGroupsButton.Y+EDITSIZE+MARGIN;
	subjectsButton.Width=100;
	subjectsButton.Height=EDITSIZE;

	teachersButton.X=MARGIN;
	teachersButton.Y=subjectsButton.Y+EDITSIZE+MARGIN;
	teachersButton.Width=100;
	teachersButton.Height=EDITSIZE;
}
void GlobalWindow::InitConsts()
{
	roomsButton.Text="roomsWindow";
	roomsButton.OnClick=[this](void*){this->roomsButton_OnClick();};

	subjectGroupsButton.Text="subjectGroupsButton";
	subjectGroupsButton.OnClick=[this](void*){this->subjectGroupsButton_OnClick();};

	subjectsButton.Text="subjectsButton";
	subjectsButton.OnClick=[this](void*){this->subjectsButton_OnClick();};

	teachersButton.Text="teachersButton";
	teachersButton.OnClick=[this](void*){this->teachersButton_OnClick();};
}
void GlobalWindow::InitRelations()
{
	Add(&container);

	container.Add(&roomsButton);
	container.Add(&subjectGroupsButton);
	container.Add(&subjectsButton);
	container.Add(&teachersButton);
}
void GlobalWindow::LoadData()
{
}
void GlobalWindow::roomsButton_OnClick()
{
	if(roomsWindow!=nullptr)
		delete roomsWindow;

	roomsWindow=new RoomsWindow(controller);
	roomsWindow->X=CW_USEDEFAULT;
	roomsWindow->Y=CW_USEDEFAULT;
	roomsWindow->Width=400;
	roomsWindow->Height=11*MARGIN+5*(EDITSIZE+TEXTSIZE)+EXTRA;
	roomsWindow->Name="roomsWindow";
	roomsWindow->OnDestroy=[this](void*)
	{
		this->roomsButton.Disabled=false;
		this->roomsWindow->Destroy();
	};
	Add(roomsWindow);
	roomsWindow->Create();

	roomsButton.Disabled=true;
}
void GlobalWindow::subjectGroupsButton_OnClick()
{
	if(subjectGroupsWindow!=nullptr)
		delete subjectGroupsWindow;

	subjectGroupsWindow=new SubjectGroupsWindow(controller);
	subjectGroupsWindow->X=CW_USEDEFAULT;
	subjectGroupsWindow->Y=CW_USEDEFAULT;
	subjectGroupsWindow->Width=450;
	subjectGroupsWindow->Height=9*MARGIN+5*EDITSIZE+3*TEXTSIZE+EXTRA;
	subjectGroupsWindow->Name="subjectGroupsWindow";
	subjectGroupsWindow->OnDestroy=[this](void*)
	{
		this->subjectGroupsButton.Disabled=false;
		this->subjectGroupsWindow->Destroy();
	};
	subjectGroupsWindow->OnLoad=[this](void*)
	{
		if(this->subjectsWindow!=nullptr)
			this->subjectsWindow->LoadExternal();
	};
	Add(subjectGroupsWindow);
	subjectGroupsWindow->Create();

	subjectGroupsButton.Disabled=true;
}
void GlobalWindow::subjectsButton_OnClick()
{
	if(subjectsWindow!=nullptr)
		delete subjectsWindow;

	subjectsWindow=new SubjectsWindow(controller);
	subjectsWindow->X=CW_USEDEFAULT;
	subjectsWindow->Y=CW_USEDEFAULT;
	subjectsWindow->Width=550;
	subjectsWindow->Height=11*MARGIN+5*EDITSIZE+6*TEXTSIZE+EXTRA;
	subjectsWindow->Name="subjectsWindow";
	subjectsWindow->OnDestroy=[this](void*)
	{
		this->subjectsButton.Disabled=false;
		this->subjectsWindow->Destroy();
	};
	Add(subjectsWindow);
	subjectsWindow->Create();

	subjectsButton.Disabled=true;
}
void GlobalWindow::teachersButton_OnClick()
{
	if(teachersWindow!=nullptr)
		delete teachersWindow;

	teachersWindow=new TeachersWindow(controller);
	teachersWindow->X=CW_USEDEFAULT;
	teachersWindow->Y=CW_USEDEFAULT;
	teachersWindow->Width=2*(2*MARGIN+(controller.MainData->DaysCount+2)*(TEXTSIZE+MARGIN))+3*MARGIN;
	teachersWindow->Height=12*MARGIN+5*EDITSIZE+2*TEXTSIZE+EXTRA+(controller.MainData->HoursPerTurn+2)*(MARGIN+TEXTSIZE);
	teachersWindow->Name="teachersWindow";
	teachersWindow->OnDestroy=[this](void*)
	{
		this->teachersButton.Disabled=false;
		this->teachersWindow->Destroy();
	};
	Add(teachersWindow);
	teachersWindow->Create();

	teachersButton.Disabled=true;
}