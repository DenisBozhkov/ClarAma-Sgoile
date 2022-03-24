#ifndef SUBJECTGROUPSWINDOW_H
#define SUBJECTGROUPSWINDOW_H

#include "Visual.h"
#include "Headers/Controller.h"
#include "Interfaces/IActionable.h"

using namespace Visual;
using Service::Controller;
using Models::SubjectGroup;

class SubjectGroupsWindow:public Visual::Window,public IActionable
{
	Container container;

	Label nameLabel;
	Edit nameEdit;
	Label maxClassesPerDayLabel;
	NumberEdit maxClassesPerDayEdit;
	Checkbox everyDayCheckBox;
	ListBox subjectGroupsListBox;

	Button addButton;
	Button changeButton;
	Button removeButton;

	public:
		SubjectGroupsWindow(Controller&);
		virtual void Create();
		virtual void Destroy();
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

		void subjectGroupsListBox_OnSelect();

		SubjectGroup getSubjectGroup(uint=-1);
};

#endif