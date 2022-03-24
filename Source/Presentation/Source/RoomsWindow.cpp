#include "Headers/RoomsWindow.h"
RoomsWindow::RoomsWindow(Controller &controller)
	:IActionable(controller),Window(false,false,false){ }

void RoomsWindow::Create()
{
	InitConsts();
	InitRelations();
	Window::Create();
	InitComponents();
	LoadData();
}

void RoomsWindow::Destroy()
{
	controller.Rooms->Save();
	Window::Destroy();
}

void RoomsWindow::InitConsts()
{
	nameLabel.Text="Наименование";
	maxClassesLabel.Text="Максимален брой класове";
	maxClassesEdit.Text="1";
	typeLabel.Text="Вид";
	typesRadioButtons[0].Text="Класна стая";
	typesRadioButtons[1].Text="Компютърна зала";
	addButton.Text="Добави";
	changeButton.Text="Промени";
	removeButton.Text="Премахни";

	addButton.Disabled=true;
	changeButton.Disabled=true;
	removeButton.Disabled=true;

	roomsListBox.HScroll=true;
	roomsListBox.VScroll=true;

	nameEdit.OnEdit=[this](void*){this->enableButtons();};
	maxClassesEdit.OnEdit=[this](void*){this->enableButtons();};
	typesRadioButtons[0].OnClick=[this](void*){this->enableButtons();};
	typesRadioButtons[1].OnClick=[this](void*){this->enableButtons();};

	roomsListBox.OnSelect=[this](void*){this->roomsListBox_OnSelect();};

	addButton.OnClick=[this](void*){this->addButton_OnClick();};
	changeButton.OnClick=[this](void*){this->changeButton_OnClick();};
	removeButton.OnClick=[this](void*){this->removeButton_OnClick();};

}
void RoomsWindow::InitComponents()
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

	maxClassesLabel.X=nameEdit.X;
	maxClassesLabel.Y=nameEdit.Y+nameEdit.Height+MARGIN;
	maxClassesLabel.Width=nameEdit.Width;
	maxClassesLabel.Height=TEXTSIZE;

	maxClassesEdit.X=maxClassesLabel.X;
	maxClassesEdit.Y=maxClassesLabel.Y+maxClassesLabel.Height+MARGIN;
	maxClassesEdit.Width=maxClassesLabel.Width;
	maxClassesEdit.Height=EDITSIZE;

	typeLabel.X=maxClassesEdit.X;
	typeLabel.Y=maxClassesEdit.Y+maxClassesEdit.Height+MARGIN;
	typeLabel.Width=maxClassesEdit.Width;
	typeLabel.Height=TEXTSIZE;

	typeRadioButtonGroup.X=typeLabel.X;
	typeRadioButtonGroup.Y=typeLabel.Y+typeLabel.Height+MARGIN;
	typeRadioButtonGroup.Width=typeLabel.Width;
	typeRadioButtonGroup.Height=2*typeLabel.Height+MARGIN;

	typesRadioButtons[0].X=0;
	typesRadioButtons[0].Y=0;
	typesRadioButtons[0].Width=typeRadioButtonGroup.Width;
	typesRadioButtons[0].Height=TEXTSIZE;

	typesRadioButtons[1].X=typesRadioButtons[0].X;
	typesRadioButtons[1].Y=typesRadioButtons[0].Y+typesRadioButtons[0].Height+MARGIN;
	typesRadioButtons[1].Width=typesRadioButtons[0].Width;
	typesRadioButtons[1].Height=typesRadioButtons[0].Height;

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

	roomsListBox.X=MARGIN;
	roomsListBox.Y=MARGIN;
	roomsListBox.Width=container.Width-nameLabel.Width-3*MARGIN;
	roomsListBox.Height=removeButton.Y+removeButton.Height-MARGIN;
}
void RoomsWindow::InitRelations()
{
	Add(&container);

	container.Add(&nameLabel);
	container.Add(&nameEdit);
	container.Add(&maxClassesLabel);
	container.Add(&maxClassesEdit);
	container.Add(&typeLabel);
	container.Add(&typeRadioButtonGroup);
	container.Add(&roomsListBox);
	container.Add(&addButton);
	container.Add(&changeButton);
	container.Add(&removeButton);

	typeRadioButtonGroup.Add(&typesRadioButtons[0]);
	typeRadioButtonGroup.Add(&typesRadioButtons[1]);
}
void RoomsWindow::LoadData()
{
	static int i;
	static Room* room;
	roomsListBox.Clear();
	for(i=0,room=controller.Rooms->Models.Begin();room!=nullptr;room=controller.Rooms->Models.Next(),i++)
	{
		roomsListBox.Add(&room->Name);
		roomsListBox.SetItemData(room,i);
	}
	OnLoad(this);
}
void RoomsWindow::clearInputs()
{
	nameEdit.Text="";
	maxClassesEdit.Text="1";
	typeRadioButtonGroup.ClearSelection();
	roomsListBox.Selection=-1;
}
void RoomsWindow::enableButtons()
{
	addButton.Disabled=((string)nameEdit.Text==""||
		(string)maxClassesEdit.Text==""||
		typeRadioButtonGroup.SelectedIndex(-1)==-1);
	changeButton.Disabled=(roomsListBox.Selection==-1||
		(string)nameEdit.Text==""||
		(string)maxClassesEdit.Text==""||
		typeRadioButtonGroup.SelectedIndex(-1)==-1);
	removeButton.Disabled=(roomsListBox.Selection==-1);
}

void RoomsWindow::addButton_OnClick()
{
	controller.Rooms->Models.Add(new Room(getRoom()));
	LoadData();
	clearInputs();
}
void RoomsWindow::changeButton_OnClick()
{
	*((Room*)roomsListBox.GetItemData(roomsListBox.Selection))=getRoom(roomsListBox.Selection);
	LoadData();
	clearInputs();
}
void RoomsWindow::removeButton_OnClick()
{
	controller.Rooms->Models.Delete(((Room*)roomsListBox.GetItemData(roomsListBox.Selection))->Id());
	LoadData();
	clearInputs();
}

void RoomsWindow::roomsListBox_OnSelect()
{
	static Room* room;
	if(roomsListBox.Selection!=-1)
	{
		room=(Room*)roomsListBox.GetItemData(roomsListBox.Selection);
		nameEdit.Text=room->Name;
		maxClassesEdit.Text=Convert::ToString(room->MaxClasses);
		typeRadioButtonGroup.SelectedIndex((int)room->Type);
	}
	enableButtons();
}

Room RoomsWindow::getRoom(uint id)
{
	if(id==-1)
		id=((Room*)roomsListBox.GetItemData(roomsListBox.Size-1))->Id()+1;
	return Room(id,nameEdit.Text,
		Convert::ToInt(maxClassesEdit.Text),
		(RoomType)(int)typeRadioButtonGroup.SelectedIndex(-1));
}