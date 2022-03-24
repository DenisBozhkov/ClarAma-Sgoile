#include "Models.h"
#include<iostream>
#include<windows.h>
using namespace std;
using namespace Models;
int main()
{
	Teacher t(1,"Teacher",5,8);
	Room r("100",2,RT_Normal);
	Subject s("Subject",ST_B,2);
	ClassSubject cs(&s,1.5);
	Class c(7,'a',T_First,&t);
	cout<<(int)c.Number<<c.Letter<<endl;
	cout<<(int)c.StartTurn<<endl;
	cout<<c.FormMaster->Name<<endl;
}