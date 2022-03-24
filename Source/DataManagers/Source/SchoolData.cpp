#include "Headers/SchoolData.h"

void DataManagers::SchoolData::Read()
{
	static ifstream fin;
	static string line;
	static string item;
	static stringstream ss;

	fin.open("../Save/Saved/SchoolData.xml");

	if((fin.rdstate()&std::ifstream::failbit)!=0)
    	Control::Throw("Cannot read SchoolData!");

	getline(fin,line);

	ss=stringstream(line);
	while(getline(ss,item,' '))
	{
		if(item=="></SchoolData>")break;
		getline(ss,item,'=');
		if(item=="DaysCount")
		{
			getline(ss,item,'"');
			getline(ss,item,'"');
			DaysCount=Convert::ToInt(item);
			continue;
		}
		if(item=="HoursPerDay")
		{
			getline(ss,item,'"');
			getline(ss,item,'"');
			HoursPerDay=Convert::ToInt(item);
			continue;
		}
		if(item=="HoursPerTurn")
		{
			getline(ss,item,'"');
			getline(ss,item,'"');
			HoursPerTurn=Convert::ToInt(item);
			continue;
		}
	}

	fin.close();
}

void DataManagers::SchoolData::Save()
{
	static ofstream fout;
	fout.open("../Save/Saved/SchoolData.xml");

	fout<<"<SchoolData DaysCount=\""<<(int)DaysCount<<'"';
	fout<<" HoursPerDay=\""<<(int)HoursPerDay<<'"';
	fout<<" HoursPerTurn=\""<<(int)HoursPerTurn<<"\"></SchoolData>"<<endl;

	fout.close();
}