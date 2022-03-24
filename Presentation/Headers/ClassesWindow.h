#ifndef CLASSESWINDOW_H
#define CLASSESWINDOW_H

#include "Visual.h"
#include "Headers/Controller.h"
#include "Interfaces/IActionable.h"

using namespace Visual;
using Service::Controller;
using Models::Subject;
using Models::Teacher;
using Models::Room;

class ClassesWindow:public Visual::Window,public IActionable
{
	Container container;
	Label numberLabel;
	NumberEdit numberEdit;
	Label letterLabel;
	Edit letterEdit;
	Label startTurnLabel;
	ComboBox startTurnComboBox;
	Label formMasterLabel;
	ComboBox formMasterComboBox;
	ListBox classesListBox;
	Button addClassButton;
	Button changeClassButton;
	Button removeClassButton;

	NamedContainer classSubjectsNamedContainer;
	Label classesPerWeekLabel;
	Edit classesPerWeekEdit;
	Label subjectLabel;
	ComboBox subjectsComboBox;
	ListBox subjectsListBox;
	NamedContainer teachersNamedContainer;
	MultiListBox teachersListBox;
	NamedContainer roomsNamedContainer;
	MultiListBox roomsListBox;
	Button addClassSubjectButton;
	Button changeClassSubjectButton;
	Button removeClassSubjectButton;

	public:
		ClassesWindow(Controller&);
		virtual void Create();
		virtual void Destroy();

		void LoadExternal();
	protected:
		void InitComponents();
		void InitRelations();
		void InitConsts();
		void LoadData();
	private:
		void clearInputs();

		Class getClass(uint=-1);
};

#endif