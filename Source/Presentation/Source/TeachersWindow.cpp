#include "Headers/TeachersWindow.h"
using namespace DataManagers;
TeachersWindow::TeachersWindow(Controller &controller)
	:IActionable(controller),Window(false,false,false){ }

void TeachersWindow::Create()
{
	isFreeCheckboxes.resize(controller.MainData->HoursPerTurn);
	for(int i=0;i<isFreeCheckboxes.size();i++)
		isFreeCheckboxes[i].resize(controller.MainData->DaysCount);
	daysLabels.resize(controller.MainData->DaysCount);
	hoursLabels.resize(controller.MainData->HoursPerTurn);
	daysCheckboxes.resize(controller.MainData->DaysCount);
	hoursCheckboxes.resize(controller.MainData->HoursPerTurn);
	uncheckedDays.resize(controller.MainData->DaysCount,0);
	uncheckedHours.resize(controller.MainData->HoursPerTurn,0);

	InitConsts();
	InitRelations();
	Window::Create();
	InitComponents();
	LoadData();
}

void TeachersWindow::Destroy()
{
	controller.Teachers->Save();
	Window::Destroy();
}

void TeachersWindow::InitConsts()
{
	numberLabel.Text="Номер";
	nameLabel.Text="Име";
	isFreeNamedContainer.Name="Възможни часове";
	for(int i=0;i<controller.MainData->DaysCount;i++)
	{
		daysLabels[i].Text=Convert::ToString(i+1);
		daysLabels[i].Alignment=Label::Center;
		daysCheckboxes[i].Column=i;
		daysCheckboxes[i].Checked=true;
		daysCheckboxes[i].OnClick=[this](void* now){ this->daysCheckboxes_OnClick(now); };
	}
	for(int i=0;i<controller.MainData->HoursPerTurn;i++)
	{
		hoursLabels[i].Text=Convert::ToString(i+1);
		hoursLabels[i].Alignment=Label::Right;
		hoursCheckboxes[i].Row=i;
		hoursCheckboxes[i].Checked=true;
		hoursCheckboxes[i].OnClick=[this](void* now){ this->hoursCheckboxes_OnClick(now); };
	}

	for(int i=0;i<controller.MainData->HoursPerTurn;i++)
		for(int j=0;j<controller.MainData->DaysCount;j++)
		{
			isFreeCheckboxes[i][j].Checked=true;
			isFreeCheckboxes[i][j].OnClick=[this](void* now){ this->isFreeCheckboxes_OnClick(now); };
		}

	addButton.Text="addButton";
	changeButton.Text="changeButton";
	removeButton.Text="removeButton";

	addButton.Disabled=true;
	changeButton.Disabled=true;
	removeButton.Disabled=true;

	teachersListBox.HScroll=true;
	teachersListBox.VScroll=true;

	nameEdit.OnEdit=[this](void*){this->enableButtons();};
	numberEdit.OnEdit=[this](void*){this->enableButtons();};

	teachersListBox.OnSelect=[this](void*){this->teachersListBox_OnSelect();};

	addButton.OnClick=[this](void*){this->addButton_OnClick();};
	changeButton.OnClick=[this](void*){this->changeButton_OnClick();};
	removeButton.OnClick=[this](void*){this->removeButton_OnClick();};

}
void TeachersWindow::calculateXY(IComponent &component,int i,int j)
{
	component.X=2*MARGIN+i*(TEXTSIZE+MARGIN);
	component.Y=3*MARGIN+j*(TEXTSIZE+MARGIN);
}
void TeachersWindow::InitComponents()
{

	container.X=0;
	container.Y=0;
	container.Width=Width;
	container.Height=Height;

	numberLabel.X=(container.Width+MARGIN)/2;
	numberLabel.Y=MARGIN;
	numberLabel.Width=container.Width-numberLabel.X-MARGIN;
	numberLabel.Height=TEXTSIZE;

	numberEdit.X=numberLabel.X;
	numberEdit.Y=numberLabel.Y+numberLabel.Height+MARGIN;
	numberEdit.Width=numberLabel.Width;
	numberEdit.Height=EDITSIZE;
	
	nameLabel.X=numberEdit.X;
	nameLabel.Y=numberEdit.Y+numberEdit.Height+MARGIN;
	nameLabel.Width=numberEdit.Width;
	nameLabel.Height=EDITSIZE;
	
	nameEdit.X=nameLabel.X;
	nameEdit.Y=nameLabel.Y+nameLabel.Height+MARGIN;
	nameEdit.Width=nameLabel.Width;
	nameEdit.Height=EDITSIZE;
	
	for(int i=0;i<controller.MainData->HoursPerTurn;i++)
	{
		calculateXY(hoursLabels[i],0,i+2);
		calculateXY(hoursCheckboxes[i],1,i+2);
		hoursLabels[i].Width=hoursCheckboxes[i].Width=TEXTSIZE;
		hoursLabels[i].Height=hoursCheckboxes[i].Height=TEXTSIZE;
	}
	for(int i=0;i<controller.MainData->DaysCount;i++)
	{
		calculateXY(daysLabels[i],i+2,0);
		calculateXY(daysCheckboxes[i],i+2,1);
		daysLabels[i].Width=daysCheckboxes[i].Width=TEXTSIZE;
		daysLabels[i].Height=daysCheckboxes[i].Height=TEXTSIZE;
		for(int j=0;j<controller.MainData->HoursPerTurn;j++)
		{
			calculateXY(isFreeCheckboxes[j][i],i+2,j+2);
			isFreeCheckboxes[j][i].Width=TEXTSIZE;
			isFreeCheckboxes[j][i].Height=TEXTSIZE;
			isFreeCheckboxes[j][i].Row=j;
			isFreeCheckboxes[j][i].Column=i;
		}
	}
	isFreeNamedContainer.X=nameEdit.X;
	isFreeNamedContainer.Y=nameEdit.Y+nameEdit.Height+MARGIN;
	isFreeNamedContainer.Width=isFreeCheckboxes[controller.MainData->HoursPerTurn-1][controller.MainData->DaysCount-1].X+isFreeCheckboxes[controller.MainData->HoursPerTurn-1][controller.MainData->DaysCount-1].Width+MARGIN;
	isFreeNamedContainer.Height=isFreeCheckboxes[controller.MainData->HoursPerTurn-1][controller.MainData->DaysCount-1].Y+isFreeCheckboxes[controller.MainData->HoursPerTurn-1][controller.MainData->DaysCount-1].Height+MARGIN;

	addButton.X=isFreeNamedContainer.X;
	addButton.Y=isFreeNamedContainer.Y+isFreeNamedContainer.Height+MARGIN;
	addButton.Width=nameEdit.Width;
	addButton.Height=EDITSIZE;

	changeButton.X=addButton.X;
	changeButton.Y=addButton.Y+addButton.Height+MARGIN;
	changeButton.Width=addButton.Width;
	changeButton.Height=EDITSIZE;

	removeButton.X=changeButton.X;
	removeButton.Y=changeButton.Y+changeButton.Height+MARGIN;
	removeButton.Width=changeButton.Width;
	removeButton.Height=EDITSIZE;

	teachersListBox.X=MARGIN;
	teachersListBox.Y=MARGIN;
	teachersListBox.Width=container.Width-nameLabel.Width-3*MARGIN;
	teachersListBox.Height=removeButton.Y+removeButton.Height-MARGIN;
}
void TeachersWindow::InitRelations()
{
	Add(&container);

	container.Add(&numberLabel);
	container.Add(&numberEdit);
	container.Add(&nameLabel);
	container.Add(&nameEdit);
	container.Add(&isFreeNamedContainer);
	container.Add(&teachersListBox);
	container.Add(&addButton);
	container.Add(&changeButton);
	container.Add(&removeButton);

	for(int i=0;i<controller.MainData->DaysCount;i++)
	{
		isFreeNamedContainer.Add(&daysLabels[i]);
		isFreeNamedContainer.Add(&daysCheckboxes[i]);
	}
	
	for(int i=0;i<controller.MainData->HoursPerTurn;i++)
	{
		isFreeNamedContainer.Add(&hoursLabels[i]);
		isFreeNamedContainer.Add(&hoursCheckboxes[i]);
		isFreeCheckboxes[i].resize(controller.MainData->DaysCount);
		for(int j=0;j<controller.MainData->DaysCount;j++)
			isFreeNamedContainer.Add(&isFreeCheckboxes[i][j]);
	}
}
void TeachersWindow::LoadData()
{
	static int i;
	static Teacher* teacher;
	teachersListBox.Clear();
	for(i=0,teacher=controller.Teachers->Models.Begin();teacher!=nullptr;teacher=controller.Teachers->Models.Next(),i++)
	{
		teachersListBox.Add(new string(Convert::ToString(teacher->Number)+". "+teacher->Name));
		teachersListBox.SetItemData(teacher,i);
	}
	OnLoad(this);
}
void TeachersWindow::clearInputs()
{
	numberEdit.Text="";
	nameEdit.Text="";

	teachersListBox.Selection=-1;

	for(int i=0;i<controller.MainData->DaysCount;i++)
		daysCheckboxes[i].Checked=true;
}
void TeachersWindow::enableButtons()
{
	addButton.Disabled=((string)nameEdit.Text==""||
		(string)numberEdit.Text=="");
	changeButton.Disabled=(teachersListBox.Selection==-1||
		(string)nameEdit.Text==""||
		(string)numberEdit.Text=="");
	removeButton.Disabled=(teachersListBox.Selection==-1);
}

void TeachersWindow::addButton_OnClick()
{
	controller.Teachers->Models.Add(new Teacher(getTeacher()));
	LoadData();
	clearInputs();
}
void TeachersWindow::changeButton_OnClick()
{
	*((Teacher*)teachersListBox.GetItemData(teachersListBox.Selection))=getTeacher(teachersListBox.Selection);
	LoadData();
	clearInputs();
}
void TeachersWindow::removeButton_OnClick()
{
	controller.Teachers->Models.Delete(((Teacher*)teachersListBox.GetItemData(teachersListBox.Selection))->Id());
	LoadData();
	clearInputs();
}

void TeachersWindow::teachersListBox_OnSelect()
{
	static Teacher* teacher;
	if(teachersListBox.Selection!=-1)
	{
		teacher=(Teacher*)teachersListBox.GetItemData(teachersListBox.Selection);
		nameEdit.Text=teacher->Name;
		numberEdit.Text=Convert::ToString(teacher->Number);
		for(int i=0;i<controller.MainData->HoursPerTurn;i++)
		{
			uncheckedHours[i]=0;
			hoursCheckboxes[i].SetNoTriggerChecked(true);
		}
		for(int i=0;i<controller.MainData->DaysCount;i++)
		{
			uncheckedDays[i]=0;
			daysCheckboxes[i].SetNoTriggerChecked(true);
		}
		for(int i=0;i<controller.MainData->HoursPerTurn;i++)
			for(int j=0;j<controller.MainData->DaysCount;j++)
			{
				if(teacher->IsFree[j][i])
					isFreeCheckboxes[i][j].SetNoTriggerChecked(true);
				else
				{
					isFreeCheckboxes[i][j].Checked=false;
				}
			}
	}
	enableButtons();
}

void TeachersWindow::daysCheckboxes_OnClick(void* now)
{
	static GridCheckbox* checkbox;
	checkbox=(GridCheckbox*)now;
	for(int i=0;i<isFreeCheckboxes.size();i++)
		if(isFreeCheckboxes[i][checkbox->Column].Checked!=checkbox->Checked)
			isFreeCheckboxes[i][checkbox->Column].Checked=checkbox->Checked;
}
void TeachersWindow::hoursCheckboxes_OnClick(void* now)
{
	static GridCheckbox* checkbox;
	checkbox=(GridCheckbox*)now;
	for(int i=0;i<isFreeCheckboxes[checkbox->Row].size();i++)
		if(isFreeCheckboxes[checkbox->Row][i].Checked!=checkbox->Checked)
			isFreeCheckboxes[checkbox->Row][i].Checked=checkbox->Checked;
}
void TeachersWindow::isFreeCheckboxes_OnClick(void* now)
{
	static GridCheckbox* checkbox;
	checkbox=(GridCheckbox*)now;
	if(checkbox->Checked)
	{
		uncheckedDays[checkbox->Column]--;
		uncheckedHours[checkbox->Row]--;
		if(uncheckedDays[checkbox->Column]==0)
			daysCheckboxes[checkbox->Column].SetNoTriggerChecked(true);
		if(uncheckedHours[checkbox->Row]==0)
			hoursCheckboxes[checkbox->Row].SetNoTriggerChecked(true);
	}
	else
	{
		uncheckedDays[checkbox->Column]++;
		uncheckedHours[checkbox->Row]++;
		daysCheckboxes[checkbox->Column].SetNoTriggerChecked(false);
		hoursCheckboxes[checkbox->Row].SetNoTriggerChecked(false);
	}
}

Teacher TeachersWindow::getTeacher(uint id)
{
	if(id==-1)
		id=((Teacher*)teachersListBox.GetItemData(teachersListBox.Size-1))->Id()+1;
	Teacher teacher(id,Convert::ToInt(numberEdit.Text),
		(string)nameEdit.Text,
		controller.MainData->DaysCount,
		controller.MainData->HoursPerTurn);
	for(int i=0;i<controller.MainData->HoursPerTurn;i++)
		for(int j=0;j<controller.MainData->DaysCount;j++)
			teacher.IsFree[j][i]=isFreeCheckboxes[i][j].Checked;
	return teacher;
}