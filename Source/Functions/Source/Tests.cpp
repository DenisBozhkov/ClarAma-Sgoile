#include "Functions.h"
#include<iostream>
using namespace std;
using namespace Functions;
enum Enum {T1,T2,T3=11,T4,T5};
int main()
{
	cout<<Convert::ToString(1)<<endl;
	cout<<Convert::ToString(3.14)<<endl;
	cout<<Convert::ToString(L"Test")<<endl;
	cout<<Convert::ToInt("17")<<endl;
	cout<<Convert::ToDouble("2.71")<<endl;
	cout<<(Convert::ToEnum<Enum>("11")==T3)<<endl;
	try
	{
		Control::Throw("Error");
	}
	catch(runtime_error &e)
	{
		cout<<e.what()<<endl;
	}
	Control::Exit(17);
}