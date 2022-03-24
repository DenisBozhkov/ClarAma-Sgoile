#ifndef SUBJECTSWINDOW_H
#define SUBJECTSWINDOW_H

#include "Visual.h"
#include "Headers/Controller.h"
#include "Interfaces/IActionable.h"

using namespace Visual;
using Service::Controller;
using Models::Subject;
using Models::SubjectGroup;

class SubjectsWindow:public Visual::Window,public IActionable
{
	Container container;

	Label nameLabel;
	Edit nameEdit;
	Label maxClassesPerDayLabel;
	NumberEdit maxClassesPerDayEdit;
	Label typeLabel;

	RadioButtonGroup typeRadioButtonGroup;
	RadioButton typesRadioButtons[3];

	MultiListBox subjectGroupsListBox;
	ListBox subjectsListBox;

	Button addButton;
	Button changeButton;
	Button removeButton;

	public:
		SubjectsWindow(Controller&);
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
		void enableButtons();

		void addButton_OnClick();
		void changeButton_OnClick();
		void removeButton_OnClick();

		void subjectsListBox_OnSelect();

		Subject getSubject(uint=-1);
};

#endif