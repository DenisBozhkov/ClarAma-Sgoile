#include "Headers/ClassesWindow.h"
ClassesWindow::ClassesWindow(Controller &controller)
	:IActionable(controller),Window(false,false,false){ }

void ClassesWindow::Create()
{
	InitRelations();
	Window::Create();
	InitComponents();
	InitConsts();
	LoadData();
	LoadExternal();
}

void ClassesWindow::Destroy()
{
	controller.Classes->Save();
	Window::Destroy();
}

void ClassesWindow::InitConsts()
{
	numberLabel.Text="numberLabel";
	letterLabel.Text="letterLabel";
	startTurnLabel.Text="startTurnLabel";
	formMasterLabel.Text="formMasterLabel";
	addClassButton.Text="addClassButton";
	changeClassButton.Text="changeClassButton";
	removeClassButton.Text="removeClassButton";

	startTurnComboBox.Add(new string("First"));
	startTurnComboBox.Add(new string("Second"));

	addClassButton.Disabled=true;
	changeClassButton.Disabled=true;
	removeClassButton.Disabled=true;
//
//	subjectsListBox.HScroll=true;
//	subjectsListBox.VScroll=true;
//
//	subjectGroupsListBox.HScroll=true;
//	subjectGroupsListBox.VScroll=true;
//
//	nameEdit.OnEdit=[this](void*){this->enableButtons();};
//	maxClassesPerDayEdit.OnEdit=[this](void*){this->enableButtons();};
//
//	subjectsListBox.OnSelect=[this](void*){this->subjectsListBox_OnSelect();};
//
//	addButton.OnClick=[this](void*){this->addButton_OnClick();};
//	changeButton.OnClick=[this](void*){this->changeButton_OnClick();};
//	removeButton.OnClick=[this](void*){this->removeButton_OnClick();};

}
void ClassesWindow::InitComponents()
{
	container.X=0;
	container.Y=0;
	container.Width=Width;
	container.Height=Height;

	removeClassButton.Width=(container.Width-4*MARGIN)/3;
	removeClassButton.Height=EDITSIZE;
	removeClassButton.X=MARGIN;
	removeClassButton.Y=container.Height-removeClassButton.Height-MARGIN;

	changeClassButton.Width=removeClassButton.Width;
	changeClassButton.Height=removeClassButton.Height;
	changeClassButton.X=removeClassButton.X;
	changeClassButton.Y=removeClassButton.Y-changeClassButton.Height-MARGIN;

	addClassButton.Width=changeClassButton.Width;
	addClassButton.Height=changeClassButton.Height;
	addClassButton.X=changeClassButton.X;
	addClassButton.Y=changeClassButton.Y-addClassButton.Height-MARGIN;

	formMasterComboBox.Width=addClassButton.Width;
	formMasterComboBox.Height=addClassButton.Height;
	formMasterComboBox.X=addClassButton.X;
	formMasterComboBox.Y=addClassButton.Y-addClassButton.Height-MARGIN;

	formMasterLabel.Width=addClassButton.Width;
	formMasterLabel.Height=addClassButton.Height;
	formMasterLabel.X=formMasterComboBox.X;
	formMasterLabel.Y=formMasterComboBox.Y-formMasterLabel.Height-MARGIN;

	startTurnComboBox.Width=formMasterLabel.Width;
	startTurnComboBox.Height=3*formMasterLabel.Height;
	startTurnComboBox.X=formMasterLabel.X;
	startTurnComboBox.Y=formMasterLabel.Y-formMasterLabel.Height-MARGIN;

	startTurnLabel.Width=formMasterLabel.Width;
	startTurnLabel.Height=formMasterLabel.Height;
	startTurnLabel.X=startTurnComboBox.X;
	startTurnLabel.Y=startTurnComboBox.Y-startTurnLabel.Height-MARGIN;

	letterLabel.Width=(startTurnLabel.Width-MARGIN)/2;
	letterLabel.Height=startTurnLabel.Height;
	letterLabel.X=startTurnLabel.X;
	letterLabel.Y=startTurnLabel.Y-letterLabel.Height-MARGIN;

	letterEdit.Width=letterLabel.Width;
	letterEdit.Height=letterLabel.Height;
	letterEdit.X=letterLabel.X+letterLabel.Width+MARGIN;
	letterEdit.Y=letterLabel.Y;

	numberLabel.Width=letterLabel.Width;
	numberLabel.Height=letterLabel.Height;
	numberLabel.X=letterLabel.X;
	numberLabel.Y=letterLabel.Y-numberLabel.Height-MARGIN;

	numberEdit.Width=letterEdit.Width;
	numberEdit.Height=letterEdit.Height;
	numberEdit.X=letterEdit.X;
	numberEdit.Y=letterEdit.Y-numberEdit.Height-MARGIN;

	classSubjectsNamedContainer.X=2*MARGIN+removeClassButton.Width;
	classSubjectsNamedContainer.Y=MARGIN;
	classSubjectsNamedContainer.Width=container.Width-classSubjectsNamedContainer.X-MARGIN;
	classSubjectsNamedContainer.Height=container.Height-classSubjectsNamedContainer.Y-MARGIN;
}
void ClassesWindow::InitRelations()
{
	Add(&container);

	container.Add(&numberLabel);
	container.Add(&numberEdit);
	container.Add(&letterLabel);
	container.Add(&letterEdit);
	container.Add(&startTurnLabel);
	container.Add(&startTurnComboBox);
	container.Add(&formMasterLabel);
	container.Add(&formMasterComboBox);
	container.Add(&addClassButton);
	container.Add(&changeClassButton);
	container.Add(&removeClassButton);

	container.Add(&classSubjectsNamedContainer);
//	typeRadioButtonGroup.Add(&typesRadioButtons[0]);
//	typeRadioButtonGroup.Add(&typesRadioButtons[1]);
//	typeRadioButtonGroup.Add(&typesRadioButtons[2]);
}
void ClassesWindow::LoadData()
{
//	static int i;
//	static Classe* subject;
//	subjectsListBox.Clear();
//	for(i=0,subject=controller.Classes->Models.Begin();subject!=nullptr;subject=controller.Classes->Models.Next(),i++)
//	{
//		subjectsListBox.Add(&subject->Name);
//		subjectsListBox.SetItemData(subject,i);
//	}
//	OnLoad(this);
}
void ClassesWindow::LoadExternal()
{
//	static int i;
//	static ClasseGroup* subjectGroup;
//	subjectGroupsListBox.Clear();
//	for(i=0,subjectGroup=controller.ClasseGroups->Models.Begin();subjectGroup!=nullptr;subjectGroup=controller.ClasseGroups->Models.Next(),i++)
//	{
//		subjectGroupsListBox.Add(&subjectGroup->Name);
//		subjectGroupsListBox.SetItemData(subjectGroup,i);
//	}
}
void ClassesWindow::clearInputs()
{
//	static vector<int> selection;
//	nameEdit.Text="";
//	maxClassesPerDayEdit.Text="1";
//	typeRadioButtonGroup.ClearSelection();
//	subjectsListBox.Selection=-1;
//
//	selection=(vector<int>)subjectGroupsListBox.Selection;
//
//	for(int i=0;i<selection.size();i++)
//		subjectGroupsListBox.SetSelection(selection[i],false);
}

Class ClassesWindow::getClass(uint id)
{
//	static vector<int> selection;
//	if(id==-1)
//		id=((Classe*)subjectsListBox.GetItemData(subjectsListBox.Size-1))->Id()+1;
//
//	Classe subject(id,
//		(string)nameEdit.Text,
//		(ClasseType)typeRadioButtonGroup.SelectedIndex(-1),
//		Convert::ToInt(maxClassesPerDayEdit.Text));
//	selection=(vector<int>)subjectGroupsListBox.Selection;
//
//	for(int i=0;i<selection.size();i++)
//		subject.Groups.push_back((ClasseGroup*)subjectGroupsListBox.GetItemData(selection[i]));
	return Class();
}