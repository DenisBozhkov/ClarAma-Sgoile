#include<iostream>
#include "Models.h"
#include "DataManagers.h"

using namespace std;
using namespace Models;
using namespace DataManagers;

void ReadClassesTest();
void SaveClassesTest();

void ReadMultiClassSubjectsTest();
void SaveMultiClassSubjectsTest();

void ReadRoomsTest();
void SaveRoomsTest();

void ReadSubjectGroupsTest();
void SaveSubjectGroupsTest();

void ReadSubjectsTest();
void SaveSubjectsTest();

void ReadTeachersTest();
void SaveTeachersTest();

SchoolData data2;

int main()
{
	data2.Read();
}

void ReadClassesTest()
{
	SubjectGroupsManager sgm;
	RoomsManager rm;
	TeachersManager tm(data2);
	SubjectsManager sm(sgm);
	ClassesManager cm(sm,tm,rm);

	sgm.Read();
	rm.Read();
	tm.Read();
	sm.Read();
	cm.Read();

	for(Class* c=cm.Models.Begin();c!=nullptr;c=cm.Models.Next())
	{
		cout<<"Id: "<<c->Id()<<endl;
		cout<<"Name: "<<(int)c->Number<<c->Letter<<endl;
		cout<<"StartTurn: "<<(int)c->StartTurn<<endl;
		cout<<"FormMaster: "<<c->FormMaster->Name<<endl;
		cout<<"SubjectsCount: "<<c->Subjects.size()<<endl;
		cout<<endl;
		for(int i=0;i<c->Subjects.size();i++)
		{
			cout<<"\tSubject: "<<c->Subjects[i]->Subject->Name<<endl;
			cout<<"\tClassesPerWeek: "<<c->Subjects[i]->ClassesPerWeek<<endl;
			cout<<"\tTeachers: ";
			for(int j=0;j<c->Subjects[i]->Teachers.size();j++)
				cout<<c->Subjects[i]->Teachers[j]->Name<<' ';
			cout<<endl;
			cout<<"\tRooms: ";
			for(int j=0;j<c->Subjects[i]->Rooms.size();j++)
				cout<<c->Subjects[i]->Rooms[j]->Name<<' ';
			cout<<endl;
			cout<<endl;
		}
		cout<<"---------------------------------------"<<endl;
	}
}
void SaveClassesTest()
{
	Class* c;
	ClassSubject* cs;

	SubjectGroupsManager sgm;
	RoomsManager rm;
	TeachersManager tm(data2);
	SubjectsManager sm(sgm);
	ClassesManager cm(sm,tm,rm);

	sgm.Read();
	rm.Read();
	tm.Read();
	sm.Read();

	c=new Class(5,'a',T_First,tm.Models.Get(0));
	cs=new ClassSubject(sm.Models.Get(0),3);
	cs->Teachers.push_back(tm.Models.Get(0));
	cs->Rooms.push_back(rm.Models.Get(1));
	c->Subjects.push_back(cs);
	cs=new ClassSubject(sm.Models.Get(1),1);
	cs->Teachers.push_back(tm.Models.Get(2));
	cs->Rooms.push_back(rm.Models.Get(1));
	c->Subjects.push_back(cs);
	cm.Models.Add(c);

	c=new Class(5,'b',T_First,tm.Models.Get(2));
	cs=new ClassSubject(sm.Models.Get(0),3);
	cs->Teachers.push_back(tm.Models.Get(0));
	cs->Rooms.push_back(rm.Models.Get(3));
	c->Subjects.push_back(cs);
	cs=new ClassSubject(sm.Models.Get(1),1);
	cs->Teachers.push_back(tm.Models.Get(2));
	cs->Rooms.push_back(rm.Models.Get(3));
	c->Subjects.push_back(cs);
	cm.Models.Add(c);

	cm.Save();
}

void ReadMultiClassSubjectsTest()
{
	SubjectGroupsManager sgm;
	RoomsManager rm;
	TeachersManager tm(data2);
	SubjectsManager sm(sgm);
	ClassesManager cm(sm,tm,rm);
	MultiClassSubjectsManager mcsm(cm,sm,tm,rm);

	sgm.Read();
	rm.Read();
	tm.Read();
	sm.Read();
	cm.Read();
	mcsm.Read();

	for(MultiClassSubject* mcs=mcsm.Models.Begin();mcs!=nullptr;mcs=mcsm.Models.Next())
	{
		cout<<"Subject: "<<mcs->Subject->Name<<endl;
		cout<<"ClassesPerWeek: "<<mcs->ClassesPerWeek<<endl;
		cout<<"Teachers: ";
		for(int j=0;j<mcs->Teachers.size();j++)
			cout<<mcs->Teachers[j]->Name<<' ';
		cout<<endl;
		cout<<"Rooms: ";
		for(int j=0;j<mcs->Rooms.size();j++)
			cout<<mcs->Rooms[j]->Name<<' ';
		cout<<endl;
		cout<<"Classes: ";
		for(int j=0;j<mcs->Classes.size();j++)
			cout<<(int)mcs->Classes[j]->Number<<mcs->Classes[j]->Letter<<' ';
		cout<<endl;
		cout<<endl;

	}
}
void SaveMultiClassSubjectsTest()
{
	SubjectGroupsManager sgm;
	RoomsManager rm;
	TeachersManager tm(data2);
	SubjectsManager sm(sgm);
	ClassesManager cm(sm,tm,rm);
	MultiClassSubjectsManager mcsm(cm,sm,tm,rm);
	MultiClassSubject* mcs;

	sgm.Read();
	rm.Read();
	tm.Read();
	sm.Read();
	cm.Read();

	mcsm.Models.Add(mcs=new MultiClassSubject(sm.Models.Get(2),3));
	mcs->Classes.push_back(cm.Models.Get(1));
	mcs->Classes.push_back(cm.Models.Get(0));
	mcs->Teachers.push_back(tm.Models.Get(0));
	mcs->Teachers.push_back(tm.Models.Get(1));
	mcs->Teachers.push_back(tm.Models.Get(2));
	mcs->Rooms.push_back(rm.Models.Get(0));
	mcs->Rooms.push_back(rm.Models.Get(1));
	mcs->Rooms.push_back(rm.Models.Get(2));
	mcsm.Models.Add(mcs=new MultiClassSubject(sm.Models.Get(1),2));
	mcs->Classes.push_back(cm.Models.Get(1));
	mcs->Classes.push_back(cm.Models.Get(0));
	mcs->Teachers.push_back(tm.Models.Get(1));
	mcs->Teachers.push_back(tm.Models.Get(2));
	mcs->Rooms.push_back(rm.Models.Get(3));
	mcs->Rooms.push_back(rm.Models.Get(4));

	mcsm.Save();
}

void ReadRoomsTest()
{
	RoomsManager rm;
	rm.Read();
	cout<<rm.Models.Size()<<endl;
	for(Room* room=rm.Models.Begin();room!=nullptr;room=rm.Models.Next())
	{
		cout<<"Id: "<<room->Id()<<endl;
		cout<<"Name: "<<room->Name<<endl;
		cout<<"MaxClasses: "<<(int)room->MaxClasses<<endl;
		cout<<"Type: "<<(int)room->Type<<endl;
		cout<<endl;
	}
}
void SaveRoomsTest()
{
	RoomsManager rm;
	rm.Models.Add(new Room("100",2,RT_Normal));
	rm.Models.Add(new Room("101",1,RT_Normal));
	rm.Models.Add(new Room("102",1,RT_Normal));
	rm.Models.Add(new Room("103",1,RT_Normal));
	rm.Models.Add(new Room("104",1,RT_Computer));
	rm.Models.Add(new Room(6,"106",1,RT_Normal));
	rm.Models.Add(new Room("107",1,RT_Computer));
	rm.Save();
}

void ReadSubjectGroupsTest()
{
	SubjectGroupsManager sgm;
	sgm.Read();
	cout<<sgm.Models.Size()<<endl;
	for(SubjectGroup* subjectGroup=sgm.Models.Begin();subjectGroup!=nullptr;subjectGroup=sgm.Models.Next())
	{
		cout<<"Id: "<<subjectGroup->Id()<<endl;
		cout<<"Name: "<<subjectGroup->Name<<endl;
		cout<<"MaxClassesPerDay: "<<(int)subjectGroup->MaxClassesPerDay<<endl;
		cout<<"EveryDay: "<<subjectGroup->EveryDay<<endl;
		cout<<endl;
	}
}
void SaveSubjectGroupsTest()
{
	SubjectGroupsManager sgm;
	sgm.Models.Add(new SubjectGroup("Group1",2,false));
	sgm.Models.Add(new SubjectGroup("Group2",1,true));
	sgm.Models.Add(new SubjectGroup("Group3",4,false));
	sgm.Save();
}

void ReadSubjectsTest()
{
	SubjectGroupsManager sgm;
	SubjectsManager sm(sgm);
	sgm.Read();
	sm.Read();
	cout<<sm.Models.Size()<<endl;
	for(Subject* subject=sm.Models.Begin();subject!=nullptr;subject=sm.Models.Next())
	{
		cout<<"Id: "<<subject->Id()<<endl;
		cout<<"Name: "<<subject->Name<<endl;
		cout<<"Type: "<<(int)subject->Type<<endl;
		cout<<"MaxClassesPerDay: "<<(int)subject->MaxClassesPerDay<<endl;
		cout<<"Group: "<<subject->Groups[0]->Name<<endl;
		cout<<endl;
	}
}
void SaveSubjectsTest()
{
	SubjectGroupsManager sgm;
	SubjectsManager sm(sgm);
	sgm.Read();
	sm.Models.Add(new Subject("Subject1",ST_A,1));
	sm.Models.Add(new Subject("Subject2",ST_C,2));
	sm.Models.Add(new Subject("Subject3",ST_B,0));
	sm.Models.Get(0)->Groups.push_back(sgm.Models.Get(2));
	sm.Models.Get(1)->Groups.push_back(sgm.Models.Get(0));
	sm.Models.Get(2)->Groups.push_back(sgm.Models.Get(1));
	sm.Save();
}

void ReadTeachersTest()
{
	TeachersManager tm(data2);
	tm.Read();
	cout<<tm.Models.Size()<<endl;
	for(Teacher* teacher=tm.Models.Begin();teacher!=nullptr;teacher=tm.Models.Next())
	{
		cout<<"Id: "<<teacher->Id()<<endl;
		cout<<"Number: "<<(int)teacher->Number<<endl;
		cout<<"Name: "<<teacher->Name<<endl;
		cout<<"IsFree: "<<teacher->IsFree[2][3]<<endl;
		cout<<endl;
	}
}
void SaveTeachersTest()
{
	TeachersManager tm(data2);
	tm.Models.Add(new Teacher(1,"Test1",5,8));
	tm.Models.Get(0)->IsFree[1][4]=false;
	tm.Models.Get(0)->IsFree[4][2]=false;
	tm.Models.Add(new Teacher(2,"Test2",5,8));
	tm.Models.Get(1)->IsFree[0][0]=false;
	tm.Models.Get(1)->IsFree[1][0]=false;
	tm.Models.Get(1)->IsFree[2][0]=false;
	tm.Models.Get(1)->IsFree[3][0]=false;
	tm.Models.Get(1)->IsFree[4][0]=false;
	tm.Models.Add(new Teacher(3,"Test3",5,8));
	tm.Models.Get(2)->IsFree[2][3]=false;
	tm.Models.Add(new Teacher(4,"Test4",5,8));
	tm.Models.Get(3)->IsFree[0][0]=false;
	tm.Models.Get(3)->IsFree[0][1]=false;
	tm.Models.Get(3)->IsFree[0][2]=false;
	tm.Models.Get(3)->IsFree[0][3]=false;
	tm.Models.Get(3)->IsFree[0][4]=false;
	tm.Models.Get(3)->IsFree[0][5]=false;
	tm.Models.Get(3)->IsFree[0][6]=false;
	tm.Models.Get(3)->IsFree[0][7]=false;
	tm.Save();
}