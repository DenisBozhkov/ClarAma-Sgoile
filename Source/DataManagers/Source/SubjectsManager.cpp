#include "Headers/SubjectsManager.h"

DataManagers::SubjectsManager::SubjectsManager(SubjectGroupsManager &subjectGroups)
	:subjectGroups(subjectGroups){ }

void DataManagers::SubjectsManager::Read()
{
	static ifstream fin;
	static string line;
	static string item;
	static stringstream ss;
	static Subject* subject;

	static uint id;
	static string name;
	static SubjectType type;
	static byte maxClassesPerDay;
	static uint groupId;

	fin.open(saveDir/"Subjects.xml");

	while(getline(fin,line))
	{
		if(line=="<Subjects>")continue;
		if(line=="</Subjects>")break;

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
			if(item=="Name")
			{
				getline(ss,item,'"');
				getline(ss,item,'"');
				name=item;
				continue;
			}
			if(item=="Type")
			{
				getline(ss,item,'"');
				getline(ss,item,'"');
				type=Convert::ToEnum<SubjectType>(item);
				continue;
			}
			if(item=="MaxClassesPerDay")
			{
				getline(ss,item,'"');
				getline(ss,item,'"');
				maxClassesPerDay=Convert::ToInt(item);
				continue;
			}
		}
		Models.Add(subject=new Subject(id,name,type,maxClassesPerDay));
		while(getline(fin,line))
		{
			if(line=="\t</Subject>")break;
			ss=stringstream(line);
			while(getline(ss,item,' '))
			{
				if(item=="<Group")continue;
				if(item=="></Group>")break;
				getline(ss,item,'=');
				if(item=="Id")
				{
					getline(ss,item,'"');
					getline(ss,item,'"');
					groupId=Convert::ToInt(item);
					continue;
				}
			}
			if(subjectGroups.Models.Get(groupId)!=nullptr)
				subject->Groups.push_back(subjectGroups.Models.Get(groupId));
		}
	}

	fin.close();
}

void DataManagers::SubjectsManager::Save()
{
	static ofstream fout;
	fout.open(saveDir/"Subjects.xml");

	fout<<"<Subjects>"<<endl;
	for(Subject* item=Models.Begin();item!=nullptr;item=Models.Next())
	{
		fout<<"\t<Subject Id=\""<<item->Id()<<'"';
		fout<<" Name=\""<<item->Name<<'"';
		fout<<" Type=\""<<(int)item->Type<<'"';
		fout<<" MaxClassesPerDay=\""<<(int)item->MaxClassesPerDay<<"\">"<<endl;
		for(int i=0;i<item->Groups.size();i++)
			fout<<"\t\t<Group Id=\""<<item->Groups[i]->Id()<<"\"></Group>"<<endl;
		fout<<"\t</Subject>"<<endl;
	}
	fout<<"</Subjects>"<<endl;

	fout.close();
}