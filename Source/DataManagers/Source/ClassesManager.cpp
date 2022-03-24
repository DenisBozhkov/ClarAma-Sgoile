#include "Headers/ClassesManager.h"

DataManagers::ClassesManager::ClassesManager(SubjectsManager &subjects,TeachersManager &teachers,RoomsManager &rooms)
	:subjects(subjects),teachers(teachers),rooms(rooms){ }

void DataManagers::ClassesManager::Read()
{
	static ifstream fin;
	static string line;
	static string item;
	static stringstream ss;
	static Class* clas;
	static ClassSubject* classSubject;

	static uint id;
	static byte number;
	static char letter;
	static Turn startTurn;
	static uint formMasterId;
	static uint subjectId;
	static float classesPerWeek;
	static uint teacherId;
	static uint roomId;

	fin.open(saveDir/"Classes.xml");

	while(getline(fin,line))
	{
		if(line=="<Classes>")continue;
		if(line=="</Classes>")break;

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
			if(item=="Number")
			{
				getline(ss,item,'"');
				getline(ss,item,'"');
				number=Convert::ToInt(item);
				continue;
			}
			if(item=="Letter")
			{
				getline(ss,item,'"');
				getline(ss,item,'"');
				letter=item[0];
				continue;
			}
			if(item=="StartTurn")
			{
				getline(ss,item,'"');
				getline(ss,item,'"');
				startTurn=Convert::ToEnum<Turn>(item);
				continue;
			}
			if(item=="FormMaster")
			{
				getline(ss,item,'"');
				getline(ss,item,'"');
				formMasterId=Convert::ToInt(item);
				continue;
			}
		}
		Models.Add(clas=new Class(id,number,letter,startTurn,teachers.Models.Get(formMasterId)));
		while(getline(fin,line))
		{
			if(line=="\t</Class>")break;
			ss=stringstream(line);
			while(getline(ss,item,' '))
			{
				getline(ss,item,'=');
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
			clas->Subjects.push_back(classSubject=new ClassSubject(subjects.Models.Get(subjectId),classesPerWeek));
			while(getline(fin,line))
			{
				if(line.find("</ClassSubject>")!=string::npos)break;
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
					classSubject->Teachers.push_back(teachers.Models.Get(teacherId));
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
					classSubject->Rooms.push_back(rooms.Models.Get(roomId));
				}
			}
		}
	}

	fin.close();
}

void DataManagers::ClassesManager::Save()
{
	static ofstream fout;
	fout.open(saveDir/"Classes.xml");

	fout<<"<Classes>"<<endl;
	for(Class* item=Models.Begin();item!=nullptr;item=Models.Next())
	{
		fout<<"\t<Class Id=\""<<item->Id()<<'"';
		fout<<" Number=\""<<(int)item->Number<<'"';
		fout<<" Letter=\""<<item->Letter<<'"';
		fout<<" StartTurn=\""<<(int)item->StartTurn<<'"';
		fout<<" FormMaster=\""<<(int)item->FormMaster->Id()<<"\">"<<endl;
		for(int i=0;i<item->Subjects.size();i++)
		{
			fout<<"\t\t<ClassSubject SubjectId=\""<<item->Subjects[i]->Subject->Id()<<"\"";
			fout<<" ClassesPerWeek=\""<<item->Subjects[i]->ClassesPerWeek<<"\">"<<endl;
			for(int j=0;j<item->Subjects[i]->Teachers.size();j++)
				fout<<"\t\t\t<Teacher Id=\""<<item->Subjects[i]->Teachers[j]->Id()<<"\"></Teacher>"<<endl;
			for(int j=0;j<item->Subjects[i]->Rooms.size();j++)
				fout<<"\t\t\t<Room Id=\""<<item->Subjects[i]->Rooms[j]->Id()<<"\"></Room>"<<endl;
			fout<<"\t\t</ClassSubject>"<<endl;
		}
		fout<<"\t</Class>"<<endl;
	}
	fout<<"</Classes>"<<endl;

	fout.close();
}