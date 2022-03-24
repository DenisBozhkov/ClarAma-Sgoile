#ifndef GLOBALWINDOW_H
#define GLOBALWINDOW_H

#include "Visual.h"
#include "Headers/ClassesWindow.h"
#include "Headers/RoomsWindow.h"
#include "Headers/SubjectGroupsWindow.h"
#include "Headers/SubjectsWindow.h"
#include "Headers/TeachersWindow.h"
#include "Interfaces/IActionable.h"

using namespace Visual;

class GlobalWindow:public Visual::Window,public IActionable
{
	RoomsWindow* roomsWindow;
	SubjectGroupsWindow* subjectGroupsWindow;
	SubjectsWindow* subjectsWindow;
	TeachersWindow* teachersWindow;

	Container container;

	Button roomsButton;
	Button subjectGroupsButton;
	Button teachersButton;
	Button subjectsButton;
	Button classesButton;
	Button multiClassSubjectsButton;

	public:
		GlobalWindow(Controller &controller);
		~GlobalWindow();
		void Create();
	protected:
		void InitComponents();
		void InitConsts();
		void InitRelations();
		void LoadData();
	private:
		void roomsButton_OnClick();
		void subjectGroupsButton_OnClick();
		void subjectsButton_OnClick();
		void teachersButton_OnClick();
};

#endif