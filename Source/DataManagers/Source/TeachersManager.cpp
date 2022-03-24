#include "Headers/TeachersManager.h"
DataManagers::TeachersManager::TeachersManager(SchoolData &data)
	:data(data){ }
void DataManagers::TeachersManager::Read()
{
	static ifstream fin;
	static string line;
	static string item;
	static stringstream ss;
	static Teacher* teacher;

	static uint id;
	static byte number;
	static string name;
	static byte day,hour;

	fin.open(saveDir/"Teachers.xml");

	while(getline(fin,line))
	{
		if(line=="<Teachers>")continue;
		if(line=="</Teachers>")break;

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
			if(item=="Name")
			{
				getline(ss,item,'"');
				getline(ss,item,'"');
				name=item;
				continue;
			}
		}
		Models.Add(teacher=new Teacher(id,number,name,data.DaysCount,data.HoursPerTurn));
		while(getline(fin,line))
		{
			if(line=="\t</Teacher>")break;
			ss=stringstream(line);
			while(getline(ss,item,' '))
			{
				if(item=="<NotFree")continue;
				if(item=="></NotFree>")break;
				getline(ss,item,'=');
				if(item=="Day")
				{
					getline(ss,item,'"');
					getline(ss,item,'"');
					day=(byte)Convert::ToInt(item);
					continue;
				}
				if(item=="Hour")
				{
					getline(ss,item,'"');
					getline(ss,item,'"');
					hour=(byte)Convert::ToInt(item);
					continue;
				}
			}
			teacher->IsFree[day][hour]=false;
		}
	}

	fin.close();
}

void DataManagers::TeachersManager::Save()
{
	static ofstream fout;
	fout.open(saveDir/"Teachers.xml");

	fout<<"<Teachers>"<<endl;
	for(Teacher* item=Models.Begin();item!=nullptr;item=Models.Next())
	{
		fout<<"\t<Teacher Id=\""<<item->Id()<<'"';
		fout<<" Number=\""<<(int)item->Number<<'"';
		fout<<" Name=\""<<item->Name<<"\">"<<endl;
		for(int i=0;i<item->IsFree.size();i++)
			for(int j=0;j<item->IsFree[i].size();j++)
				if(!item->IsFree[i][j])
					fout<<"\t\t<NotFree Day=\""<<i<<"\" Hour=\""<<j<<"\"></NotFree>"<<endl;
		fout<<"\t</Teacher>"<<endl;
	}
	fout<<"</Teachers>"<<endl;

	fout.close();
}