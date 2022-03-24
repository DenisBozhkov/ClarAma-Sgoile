#include<cstdio>
#include<windows.h>
using namespace std;
#include "Visual.h"
using namespace Visual;

Window window;
ComboBox comboBox;

Container container;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const int width=150;
	
	comboBox.X=0;
	comboBox.Y=0;
	comboBox.Width=100;
	comboBox.Height=200;
	
	container.X=0;
	container.Y=0;
	container.Width=640;
	container.Height=480;
	container.Add(&comboBox);
	
	window.X=100;
	window.Y=100;
	window.Width=640;
	window.Height=480;
	window.Name="Тест";
	window.Add(&container);
	
	window.Create();
	
	comboBox.Add(new string("Test1"));
	comboBox.Add(new string("Test2"));
	comboBox.Add(new string("Test3"));
	comboBox.Add(new string("Test4"));
	comboBox.Add(new string("Test5"));
	comboBox.Add(new string("Test6"));
	comboBox.Add(new string("Test7"));
	
	window.Loop();
	return 0;
}