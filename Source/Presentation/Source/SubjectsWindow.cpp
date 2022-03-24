#include "Headers/SubjectsWindow.h"
SubjectsWindow::SubjectsWindow(Controller &controller)
	:IActionable(controller),Window(false,false,false){ }

void SubjectsWindow::Create()
{
	InitConsts();
	InitRelations();
	Window::Create();
	InitComponents();
	LoadData();
	LoadExternal();
}

void SubjectsWindow::Destroy()
{
	controller.Subjects->Save();
	Window::Destroy();
}

void SubjectsWindow::InitConsts()
{
	nameLabel.Text="nameLabel";
	maxClassesPerDayLabel.Text="maxClassesPerDayLabel";
	maxClassesPerDayEdit.Text="0";
	typeLabel.Text="typeLabel";
	typesRadioButtons[0].Text="typesRadioButtons[0]";
	typesRadioButtons[1].Text="typesRadioButtons[1]";
	typesRadioButtons[2].Text="typesRadioButtons[2]";
	addButton.Text="addButton";
	changeButton.Text="changeButton";
	removeButton.Text="removeButton";

	addButton.Disabled=true;
	changeButton.Disabled=true;
	removeButton.Disabled=true;

	subjectsListBox.HScroll=true;
	subjectsListBox.VScroll=true;

	subjectGroupsListBox.HScroll=true;
	subjectGroupsListBox.VScroll=true;

	nameEdit.OnEdit=[this](void*){this->enableButtons();};
	maxClassesPerDayEdit.OnEdit=[this](void*){this->enableButtons();};
	typesRadioButtons[0].OnClick=[this](void*){this->enableButtons();};
	typesRadioButtons[1].OnClick=[this](void*){this->enableButtons();};
	typesRadioButtons[2].OnClick=[this](void*){this->enableButtons();};

	subjectsListBox.OnSelect=[this](void*){this->subjectsListBox_OnSelect();};

	addButton.OnClick=[this](void*){this->addButton_OnClick();};
	changeButton.OnClick=[this](void*){this->changeButton_OnClick();};
	removeButton.OnClick=[this](void*){this->removeButton_OnClick();};

}
void SubjectsWindow::InitComponents()
{

	container.X=0;
	container.Y=0;
	container.Width=Width;
	container.Height=Height;

	nameLabel.X=(container.Width+MARGIN)/3;
	nameLabel.Y=MARGIN;
	nameLabel.Width=(container.Width-4*MARGIN)/3;
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

	typeLabel.X=maxClassesPerDayEdit.X;
	typeLabel.Y=maxClassesPerDayEdit.Y+maxClassesPerDayEdit.Height+MARGIN;
	typeLabel.Width=maxClassesPerDayEdit.Width;
	typeLabel.Height=TEXTSIZE;

	typeRadioButtonGroup.X=typeLabel.X;
	typeRadioButtonGroup.Y=typeLabel.Y+typeLabel.Height+MARGIN;
	typeRadioButtonGroup.Width=typeLabel.Width;
	typeRadioButtonGroup.Height=3*typeLabel.Height+2*MARGIN;

	typesRadioButtons[0].X=0;
	typesRadioButtons[0].Y=0;
	typesRadioButtons[0].Width=typeRadioButtonGroup.Width;
	typesRadioButtons[0].Height=TEXTSIZE;

	typesRadioButtons[1].X=typesRadioButtons[0].X;
	typesRadioButtons[1].Y=typesRadioButtons[0].Y+typesRadioButtons[0].Height+MARGIN;
	typesRadioButtons[1].Width=typesRadioButtons[0].Width;
	typesRadioButtons[1].Height=typesRadioButtons[0].Height;

	typesRadioButtons[2].X=typesRadioButtons[1].X;
	typesRadioButtons[2].Y=typesRadioButtons[1].Y+typesRadioButtons[1].Height+MARGIN;
	typesRadioButtons[2].Width=typesRadioButtons[1].Width;
	typesRadioButtons[2].Height=typesRadioButtons[1].Height;

	addButton.X=typeRadioButtonGroup.X;
	addButton.Y=typeRadioButtonGroup.Y+typeRadioButtonGroup.Height+MARGIN;
	addButton.Width=typeRadioButtonGroup.Width;
	addButton.Height=EDITSIZE;

	changeButton.X=addButton.X;
	changeButton.Y=addButton.Y+addButton.Height+MARGIN;
	changeButton.Width=addButton.Width;
	changeButton.Height=EDITSIZE;

	removeButton.X=changeButton.X;
	removeButton.Y=changeButton.Y+changeButton.Height+MARGIN;
	removeButton.Width=changeButton.Width;
	removeButton.Height=EDITSIZE;

	subjectsListBox.X=MARGIN;
	subjectsListBox.Y=MARGIN;
	subjectsListBox.Width=nameLabel.Width;
	subjectsListBox.Height=removeButton.Y+removeButton.Height-MARGIN;

	subjectGroupsListBox.X=nameLabel.X+nameLabel.Width+MARGIN;
	subjectGroupsListBox.Y=MARGIN;
	subjectGroupsListBox.Width=container.Width-subjectsListBox.Width-nameLabel.Width-4*MARGIN;
	subjectGroupsListBox.Height=subjectsListBox.Height;
}
void SubjectsWindow::InitRelations()
{
	Add(&container);

	container.Add(&nameLabel);
	container.Add(&nameEdit);
	container.Add(&maxClassesPerDayLabel);
	container.Add(&maxClassesPerDayEdit);
	container.Add(&typeLabel);
	container.Add(&typeRadioButtonGroup);
	container.Add(&subjectsListBox);
	container.Add(&subjectGroupsListBox);
	container.Add(&addButton);
	container.Add(&changeButton);
	container.Add(&removeButton);

	typeRadioButtonGroup.Add(&typesRadioButtons[0]);
	typeRadioButtonGroup.Add(&typesRadioButtons[1]);
	typeRadioButtonGroup.Add(&typesRadioButtons[2]);
}
void SubjectsWindow::LoadData()
{
	static int i;
	static Subject* subject;
	subjectsListBox.Clear();
	for(i=0,subject=controller.Subjects->Models.Begin();subject!=nullptr;subject=controller.Subjects->Models.Next(),i++)
	{
		subjectsListBox.Add(&subject->Name);
		subjectsListBox.SetItemData(subject,i);
	}
	OnLoad(this);
}
void SubjectsWindow::LoadExternal()
{
	static int i;
	static SubjectGroup* subjectGroup;
	subjectGroupsListBox.Clear();
	for(i=0,subjectGroup=controller.SubjectGroups->Models.Begin();subjectGroup!=nullptr;subjectGroup=controller.SubjectGroups->Models.Next(),i++)
	{
		subjectGroupsListBox.Add(&subjectGroup->Name);
		subjectGroupsListBox.SetItemData(subjectGroup,i);
	}
}
void SubjectsWindow::clearInputs()
{
	static vector<int> selection;
	nameEdit.Text="";
	maxClassesPerDayEdit.Text="1";
	typeRadioButtonGroup.ClearSelection();
	subjectsListBox.Selection=-1;

	selection=(vector<int>)subjectGroupsListBox.Selection;

	for(int i=0;i<selection.size();i++)
		subjectGroupsListBox.SetSelection(selection[i],false);
}
void SubjectsWindow::enableButtons()
{
	addButton.Disabled=((string)nameEdit.Text==""||
		(string)maxClassesPerDayEdit.Text==""||
		typeRadioButtonGroup.SelectedIndex(-1)==-1);
	changeButton.Disabled=(subjectsListBox.Selection==-1||
		(string)nameEdit.Text==""||
		(string)maxClassesPerDayEdit.Text==""||
		typeRadioButtonGroup.SelectedIndex(-1)==-1);
	removeButton.Disabled=(subjectsListBox.Selection==-1);
}

void SubjectsWindow::addButton_OnClick()
{
	controller.Subjects->Models.Add(new Subject(getSubject()));
	LoadData();
	clearInputs();
}
void SubjectsWindow::changeButton_OnClick()
{
	*((Subject*)subjectsListBox.GetItemData(subjectsListBox.Selection))=getSubject(subjectsListBox.Selection);
	LoadData();
	clearInputs();
}
void SubjectsWindow::removeButton_OnClick()
{
	controller.Subjects->Models.Delete(((Subject*)subjectsListBox.GetItemData(subjectsListBox.Selection))->Id());
	LoadData();
	clearInputs();
}

void SubjectsWindow::subjectsListBox_OnSelect()
{
	static Subject* subject;
	if(subjectsListBox.Selection!=-1)
	{
		subject=(Subject*)subjectsListBox.GetItemData(subjectsListBox.Selection);
		nameEdit.Text=subject->Name;
		maxClassesPerDayEdit.Text=Convert::ToString((int)subject->MaxClassesPerDay);
		typeRadioButtonGroup.SelectedIndex((int)subject->Type);
		for(int i=0,j=0;i<controller.SubjectGroups->Models.Size();i++)
		{
			if(j<subject->Groups.size())
				if(subject->Groups[j]==subjectGroupsListBox.GetItemData(i))
				{
					subjectGroupsListBox.SetSelection(i,true);
					j++;
				}
				else subjectGroupsListBox.SetSelection(i,false);
			else subjectGroupsListBox.SetSelection(i,false);
		}
	}
	enableButtons();
}

Subject SubjectsWindow::getSubject(uint id)
{
	static vector<int> selection;
	if(id==-1)
		id=((Subject*)subjectsListBox.GetItemData(subjectsListBox.Size-1))->Id()+1;

	Subject subject(id,
		(string)nameEdit.Text,
		(SubjectType)typeRadioButtonGroup.SelectedIndex(-1),
		Convert::ToInt(maxClassesPerDayEdit.Text));
	selection=(vector<int>)subjectGroupsListBox.Selection;

	for(int i=0;i<selection.size();i++)
		subject.Groups.push_back((SubjectGroup*)subjectGroupsListBox.GetItemData(selection[i]));
	return subject;
}