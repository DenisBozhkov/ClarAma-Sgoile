#include "Headers/SubjectGroupsWindow.h"
SubjectGroupsWindow::SubjectGroupsWindow(Controller &controller)
	:IActionable(controller),Window(false,false,false){ }

void SubjectGroupsWindow::Create()
{
	InitConsts();
	InitRelations();
	Window::Create();
	InitComponents();
	LoadData();
}

void SubjectGroupsWindow::Destroy()
{
	controller.SubjectGroups->Save();
	Window::Destroy();
}

void SubjectGroupsWindow::InitConsts()
{
	nameLabel.Text="Наименование";
	maxClassesPerDayLabel.Text="Максимален брой часове на ден";
	maxClassesPerDayEdit.Text="0";
	everyDayCheckBox.Text="Час всеки ден (по възможност)";
	addButton.Text="Добави";
	changeButton.Text="Промени";
	removeButton.Text="Премахни";

	addButton.Disabled=true;
	changeButton.Disabled=true;
	removeButton.Disabled=true;

	nameEdit.OnEdit=[this](void*){this->enableButtons();};
	maxClassesPerDayEdit.OnEdit=[this](void*){this->enableButtons();};
	everyDayCheckBox.OnClick=[this](void*){this->enableButtons();};

	subjectGroupsListBox.OnSelect=[this](void*){this->subjectGroupsListBox_OnSelect();};

	addButton.OnClick=[this](void*){this->addButton_OnClick();};
	changeButton.OnClick=[this](void*){this->changeButton_OnClick();};
	removeButton.OnClick=[this](void*){this->removeButton_OnClick();};

}
void SubjectGroupsWindow::InitComponents()
{

	container.X=0;
	container.Y=0;
	container.Width=Width;
	container.Height=Height;

	nameLabel.X=(container.Width+MARGIN)/2;
	nameLabel.Y=MARGIN;
	nameLabel.Width=container.Width-nameLabel.X-MARGIN;
	nameLabel.Height=TEXTSIZE;

	nameEdit.X=nameLabel.X;
	nameEdit.Y=nameLabel.Y+nameLabel.Height+MARGIN;
	nameEdit.Width=nameLabel.Width;
	nameEdit.Height=EDITSIZE;

	maxClassesPerDayLabel.X=nameEdit.X;
	maxClassesPerDayLabel.Y=nameEdit.Y+nameEdit.Height+MARGIN;
	maxClassesPerDayLabel.Width=nameEdit.Width;
	maxClassesPerDayLabel.Height=TEXTSIZE;

	maxClassesPerDayEdit.X=maxClassesPerDayLabel.X;
	maxClassesPerDayEdit.Y=maxClassesPerDayLabel.Y+maxClassesPerDayLabel.Height+MARGIN;
	maxClassesPerDayEdit.Width=maxClassesPerDayLabel.Width;
	maxClassesPerDayEdit.Height=EDITSIZE;

	everyDayCheckBox.X=maxClassesPerDayEdit.X;
	everyDayCheckBox.Y=maxClassesPerDayEdit.Y+maxClassesPerDayEdit.Height+MARGIN;
	everyDayCheckBox.Width=maxClassesPerDayEdit.Width;
	everyDayCheckBox.Height=TEXTSIZE;

	addButton.X=everyDayCheckBox.X;
	addButton.Y=everyDayCheckBox.Y+everyDayCheckBox.Height+MARGIN;
	addButton.Width=everyDayCheckBox.Width;
	addButton.Height=EDITSIZE;

	changeButton.X=addButton.X;
	changeButton.Y=addButton.Y+addButton.Height+MARGIN;
	changeButton.Width=addButton.Width;
	changeButton.Height=EDITSIZE;

	removeButton.X=changeButton.X;
	removeButton.Y=changeButton.Y+changeButton.Height+MARGIN;
	removeButton.Width=changeButton.Width;
	removeButton.Height=EDITSIZE;

	subjectGroupsListBox.X=MARGIN;
	subjectGroupsListBox.Y=MARGIN;
	subjectGroupsListBox.Width=container.Width-nameLabel.Width-3*MARGIN;
	subjectGroupsListBox.Height=removeButton.Y+removeButton.Height-MARGIN;
}
void SubjectGroupsWindow::InitRelations()
{
	Add(&container);

	container.Add(&nameLabel);
	container.Add(&nameEdit);
	container.Add(&maxClassesPerDayLabel);
	container.Add(&maxClassesPerDayEdit);
	container.Add(&everyDayCheckBox);
	container.Add(&subjectGroupsListBox);
	container.Add(&addButton);
	container.Add(&changeButton);
	container.Add(&removeButton);
}
void SubjectGroupsWindow::LoadData()
{
	static int i;
	static SubjectGroup* group;
	subjectGroupsListBox.Clear();
	for(i=0,group=controller.SubjectGroups->Models.Begin();group!=nullptr;group=controller.SubjectGroups->Models.Next(),i++)
	{
		subjectGroupsListBox.Add(&group->Name);
		subjectGroupsListBox.SetItemData(group,i);
	}
	OnLoad(this);
}
void SubjectGroupsWindow::clearInputs()
{
	nameEdit.Text="";
	maxClassesPerDayEdit.Text="0";
	everyDayCheckBox.Checked=false;
	subjectGroupsListBox.Selection=-1;
}
void SubjectGroupsWindow::enableButtons()
{
	addButton.Disabled=((string)nameEdit.Text==""||
		(string)maxClassesPerDayEdit.Text=="");
	changeButton.Disabled=(subjectGroupsListBox.Selection==-1||
		(string)nameEdit.Text==""||
		(string)maxClassesPerDayEdit.Text=="");
	removeButton.Disabled=(subjectGroupsListBox.Selection==-1);
}

void SubjectGroupsWindow::addButton_OnClick()
{
	controller.SubjectGroups->Models.Add(new SubjectGroup(getSubjectGroup()));
	LoadData();
	clearInputs();
}
void SubjectGroupsWindow::changeButton_OnClick()
{
	*((SubjectGroup*)subjectGroupsListBox.GetItemData(subjectGroupsListBox.Selection))=getSubjectGroup(subjectGroupsListBox.Selection);
	LoadData();
	clearInputs();
}
void SubjectGroupsWindow::removeButton_OnClick()
{
	controller.SubjectGroups->Models.Delete(((SubjectGroup*)subjectGroupsListBox.GetItemData(subjectGroupsListBox.Selection))->Id());
	LoadData();
	clearInputs();
}

void SubjectGroupsWindow::subjectGroupsListBox_OnSelect()
{
	static SubjectGroup* subjectGroup;
	if(subjectGroupsListBox.Selection!=-1)
	{
		subjectGroup=(SubjectGroup*)subjectGroupsListBox.GetItemData(subjectGroupsListBox.Selection);
		nameEdit.Text=subjectGroup->Name;
		maxClassesPerDayEdit.Text=Convert::ToString((int)subjectGroup->MaxClassesPerDay);
		everyDayCheckBox.Checked=subjectGroup->EveryDay;
	}
	enableButtons();
}

SubjectGroup SubjectGroupsWindow::getSubjectGroup(uint id)
{
	if(id==-1)
		id=((SubjectGroup*)subjectGroupsListBox.GetItemData(subjectGroupsListBox.Size-1))->Id()+1;
	return SubjectGroup(id,nameEdit.Text,
		Convert::ToInt(maxClassesPerDayEdit.Text),
		everyDayCheckBox.Checked);
}