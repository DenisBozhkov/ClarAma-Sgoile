#ifndef TEACHERSWINDOW_H
#define TEACHERSWINDOW_H

#include "Visual.h"
#include "Headers/Controller.h"
#include "Interfaces/IActionable.h"
#include "GridCheckbox.h"

using namespace Visual;
using Service::Controller;
using Models::Teacher;


class TeachersWindow:public Window,public IActionable
{
	Container container;
	Label numberLabel;
	Edit numberEdit;
	Label nameLabel;
	Edit nameEdit;
	NamedContainer isFreeNamedContainer;

	vector<Label> daysLabels;
	vector<Label> hoursLabels;

	vector<int> uncheckedDays;
	vector<int> uncheckedHours;

	vector<GridCheckbox> daysCheckboxes;
	vector<GridCheckbox> hoursCheckboxes;

	vector<vector<GridCheckbox>> isFreeCheckboxes;
	ListBox teachersListBox;

	Button addButton;
	Button changeButton;
	Button removeButton;

	public:
		TeachersWindow(Controller&);
		virtual void Create();
		virtual void Destroy();
	protected:
		void InitComponents();
		void InitRelations();
		void InitConsts();
		void LoadData();
	private:
		void calculateXY(IComponent&,int,int);

		void clearInputs();
		void enableButtons();

		void addButton_OnClick();
		void changeButton_OnClick();
		void removeButton_OnClick();

		void teachersListBox_OnSelect();

		void daysCheckboxes_OnClick(void*);
		void hoursCheckboxes_OnClick(void*);
		void isFreeCheckboxes_OnClick(void*);

		Teacher getTeacher(uint=-1);
};

#endif