#include "Headers/MultiClassSubjectsManager.h"

DataManagers::MultiClassSubjectsManager::MultiClassSubjectsManager(ClassesManager &classes,SubjectsManager &subjects,TeachersManager &teachers,RoomsManager &rooms)
	:classes(classes),subjects(subjects),teachers(teachers),rooms(rooms){ }

void DataManagers::MultiClassSubjectsManager::Read()
{
	static ifstream fin;
	static string line;
	static string item;
	static stringstream ss;
	static MultiClassSubject* mcs;

	static uint id;
	static uint subjectId;
	static float classesPerWeek;
	static uint teacherId;
	static uint roomId;
	static uint classId;

	fin.open(saveDir/"MultiClassSubjects.xml");

	while(getline(fin,line))
	{
		if(line=="<MultiClassSubjects>")continue;
		if(line=="</MultiClassSubjects>")break;
		ss=stringstream(line);
		while(getline(ss,item,' '))
		{
			getline(ss,item,'=');
			if(item=="Id")
			{
				getline(ss,item,'"');
				getline(ss,item,'"');
				id=Convert::ToInt(item);
				continue;
			}
			if(item=="SubjectId")
			{
				getline(ss,item,'"');
				getline(ss,item,'"');
				subjectId=Convert::ToInt(item);
				continue;
			}
			if(item=="ClassesPerWeek")
			{
				getline(ss,item,'"');
				getline(ss,item,'"');
				classesPerWeek=Convert::ToDouble(item);
				continue;
			}
		}
		Models.Add(mcs=new MultiClassSubject(id,subjects.Models.Get(subjectId),classesPerWeek));
		while(getline(fin,line))
		{
			if(line.find("</MultiClassSubject>")!=string::npos)break;
			ss=stringstream(line);
			if(line.find("Teacher")!=string::npos)
			{
				while(getline(ss,item,' '))
				{
					getline(ss,item,'=');
					if(item=="Id")
					{
						getline(ss,item,'"');
						getline(ss,item,'"');
						teacherId=Convert::ToInt(item);
						continue;
					}
				}
				mcs->Teachers.push_back(teachers.Models.Get(teacherId));
			}
			else if(line.find("Room")!=string::npos)
			{
				while(getline(ss,item,' '))
				{
					getline(ss,item,'=');
					if(item=="Id")
					{
						getline(ss,item,'"');
						getline(ss,item,'"');
						roomId=Convert::ToInt(item);
						continue;
					}
				}
				mcs->Rooms.push_back(rooms.Models.Get(roomId));
			}
			else if(line.find("Class")!=string::npos)
			{
				while(getline(ss,item,' '))
				{
					getline(ss,item,'=');
					if(item=="Id")
					{
						getline(ss,item,'"');
						getline(ss,item,'"');
						classId=Convert::ToInt(item);
						continue;
					}
				}
				mcs->Classes.push_back(classes.Models.Get(classId));
			}
		}
	}

	fin.close();
}

void DataManagers::MultiClassSubjectsManager::Save()
{
	static ofstream fout;
	fout.open(saveDir/"MultiClassSubjects.xml");

	fout<<"<MultiClassSubjects>"<<endl;
	for(MultiClassSubject* item=Models.Begin();item!=nullptr;item=Models.Next())
	{
  		fout<<"\t<MultiClassSubject Id=\""<<item->Id()<<'"';
		fout<<" SubjectId=\""<<item->Subject->Id()<<'"';
		fout<<" ClassesPerWeek=\""<<item->ClassesPerWeek<<"\">"<<endl;
		for(int j=0;j<item->Teachers.size();j++)
			fout<<"\t\t<Teacher Id=\""<<item->Teachers[j]->Id()<<"\"></Teacher>"<<endl;
		for(int j=0;j<item->Rooms.size();j++)
			fout<<"\t\t<Room Id=\""<<item->Rooms[j]->Id()<<"\"></Room>"<<endl;
		for(int i=0;i<item->Classes.size();i++)
			fout<<"\t\t<Class Id=\""<<item->Classes[i]->Id()<<"\"></Class>"<<endl;
		fout<<"\t</MultiClassSubject>"<<endl;
	}
	fout<<"</MultiClassSubjects>"<<endl;

	fout.close();
}