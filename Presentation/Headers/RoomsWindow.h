#ifndef ROOMSWINDOW_H
#define ROOMSWINDOW_H

#include "Visual.h"
#include "Headers/Controller.h"
#include "Interfaces/IActionable.h"

using namespace Visual;
using Service::Controller;
using Models::Room;

class RoomsWindow:public Visual::Window,public IActionable
{
	Container container;

	Label nameLabel;
	Edit nameEdit;
	Label maxClassesLabel;
	NumberEdit maxClassesEdit;
	Label typeLabel;

	RadioButtonGroup typeRadioButtonGroup;
	RadioButton typesRadioButtons[2];

	ListBox roomsListBox;

	Button addButton;
	Button changeButton;
	Button removeButton;

	public:
		RoomsWindow(Controller&);
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

		void roomsListBox_OnSelect();

		Room getRoom(uint=-1);
};

#endif