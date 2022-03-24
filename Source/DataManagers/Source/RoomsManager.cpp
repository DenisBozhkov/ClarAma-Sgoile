#include "Headers/RoomsManager.h"

void DataManagers::RoomsManager::Read()
{
	static ifstream fin;
	static string line;
	static string item;
	static stringstream ss;

	static uint id;
	static string name;
	static byte maxClasses;
	static RoomType type;

	fin.open(saveDir/"Rooms.xml");

	while(getline(fin,line))
	{
		if(line=="<Rooms>")continue;
		if(line=="</Rooms>")break;

		ss=stringstream(line);
		while(getline(ss,item,' '))
		{
			if(item=="></Room>")break;
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
			if(item=="MaxClasses")
			{
				getline(ss,item,'"');
				getline(ss,item,'"');
				maxClasses=Convert::ToInt(item);
				continue;
			}
			if(item=="Type")
			{
				getline(ss,item,'"');
				getline(ss,item,'"');
				type=Convert::ToEnum<RoomType>(item);
				continue;
			}
		}
		Models.Add(new Room(id,name,maxClasses,type));
	}

	fin.close();
}

void DataManagers::RoomsManager::Save()
{
	static ofstream fout;
	fout.open(saveDir/"Rooms.xml");

	fout<<"<Rooms>"<<endl;
	for(Room* item=Models.Begin();item!=nullptr;item=Models.Next())
	{
		fout<<"\t<Room Id=\""<<item->Id()<<'"';
		fout<<" Name=\""<<item->Name<<'"';
		fout<<" MaxClasses=\""<<(uint)item->MaxClasses<<'"';
		fout<<" Type=\""<<item->Type<<"\"></Room>"<<endl;
	}
	fout<<"</Rooms>"<<endl;

	fout.close();
}