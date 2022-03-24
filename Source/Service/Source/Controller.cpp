#include "Headers/Controller.h"
Service::Controller::Controller()
{
	MainData=new DataManagers::SchoolData;
	Rooms=new DataManagers::RoomsManager;
	Teachers=new DataManagers::TeachersManager(*MainData);
	SubjectGroups=new DataManagers::SubjectGroupsManager;
	Subjects=new DataManagers::SubjectsManager(*SubjectGroups);
	Classes=new DataManagers::ClassesManager(*Subjects,*Teachers,*Rooms);
	MultiClassSubjects=new DataManagers::MultiClassSubjectsManager(*Classes,*Subjects,*Teachers,*Rooms);

	MainData->Read();
	Rooms->Read();
	Teachers->Read();
	SubjectGroups->Read();
	Subjects->Read();
	Classes->Read();
	MultiClassSubjects->Read();
}
Service::Controller::~Controller()
{
	SaveAll();

	delete MainData;
	delete Rooms;
	delete Teachers;
	delete SubjectGroups;
	delete Subjects;
	delete Classes;
	delete MultiClassSubjects;
}
void Service::Controller::SaveAll()
{
	MainData->Save();
	Rooms->Save();
	Teachers->Save();
	SubjectGroups->Save();
	Subjects->Save();
	Classes->Save();
	MultiClassSubjects->Save();
}