#include<iostream>
#include "Structures.h"
using namespace Structures;
using namespace std;
void print(SmallSet &ss)
{
	auto vec=ss.ToVector();
	for(int i=0;i<vec.size();i++)
		cout<<(int)vec[i]<<' ';
	cout<<endl;
}
void SmallSetTest()
{
	SmallSet s1,s2(vector<int>({1,6,73,15,127}));
	cout<<s1.IsEmpty()<<endl;
	system("pause>nul");

	s1.Add(16);
	s1.Add(34);
	s1.Add(126);
	s1.Add(16);

	print(s1);
	system("pause>nul");
	print(s2);
	system("pause>nul");

	s1.Change(126);
	print(s1);
	system("pause>nul");
	s2.Remove(73);
	print(s2);
	system("pause>nul");

	s2.Change(s1);
	s1.Add(s2);
	print(s2);
	system("pause>nul");
	print(s1);
	system("pause>nul");

	s1.Remove(s2);
	print(s1);
	system("pause>nul");

	cout<<s2.At(16)<<endl;
}
struct test
{
	int id;
	int Id()
	{
		return id;
	}
};
void print(ModelSet<int,test> &ms)
{
	for(test* begin=ms.Begin();begin!=nullptr;begin=ms.Next())
		cout<<begin->Id()<<' ';
	cout<<endl;
}
int main()
{
	ModelSet<int,test> ms;
	for(int i=0;i<10;i++)
		ms.Add(new test{(i*i)%11});
	ms.Get(1)->id=17;
	print(ms);
	system("pause>nul");

	cout<<(ms.Get(1)->Id()==1)<<endl;
	system("pause>nul");

	ms.Delete(1);
	print(ms);
	system("pause>nul");

	cout<<ms.Size()<<endl;
	system("pause>nul");

	auto vec=ms.ToVector();
	for(int i=0;i<vec.size();i++)
		cout<<vec[i]->Id()<<' ';
	cout<<endl;
}