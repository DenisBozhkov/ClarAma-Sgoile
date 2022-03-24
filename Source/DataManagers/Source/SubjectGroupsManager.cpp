#include "Headers/SubjectGroupsManager.h"

void DataManagers::SubjectGroupsManager::Read()
{
	static ifstream fin;
	static string line;
	static string item;
	static stringstream ss;

	static uint id;
	static string name;
	static byte maxClassesPerDay;
	static bool everyDay;

	fin.open(saveDir/"SubjectGroups.xml");

	while(getline(fin,line))
	{
		if(line=="<SubjectGroups>")continue;
		if(line=="</SubjectGroups>")break;

		ss=stringstream(line);
		while(getline(ss,item,' '))
		{
			if(item=="></SubjectGroup>")break;
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
			if(item=="MaxClassesPerDay")
			{
				getline(ss,item,'"');
				getline(ss,item,'"');
				maxClassesPerDay=Convert::ToInt(item);
				continue;
			}
			if(item=="EveryDay")
			{
				getline(ss,item,'"');
				getline(ss,item,'"');
				everyDay=Convert::ToEnum<RoomType>(item);
				continue;
			}
		}
		Models.Add(new SubjectGroup(id,name,maxClassesPerDay,everyDay));
	}

	fin.close();
}

void DataManagers::SubjectGroupsManager::Save()
{
	static ofstream fout;
	fout.open(saveDir/"SubjectGroups.xml");

	fout<<"<SubjectGroups>"<<endl;
	for(SubjectGroup* item=Models.Begin();item!=nullptr;item=Models.Next())
	{
		fout<<"\t<SubjectGroup Id=\""<<item->Id()<<'"';
		fout<<" Name=\""<<item->Name<<'"';
		fout<<" MaxClassesPerDay=\""<<(uint)item->MaxClassesPerDay<<'"';
		fout<<" EveryDay=\""<<item->EveryDay<<"\"></SubjectGroup>"<<endl;
	}
	fout<<"</SubjectGroups>"<<endl;

	fout.close();
}