#ifndef ICONFIG_H
#define ICONFIG_H

#include<windows.h>
#include<windowsx.h>
#include<commctrl.h>
#include<uxtheme.h>
#include<functional>
#include<string>
#include<vector>
#include<typeinfo>
#include<unordered_map>

#include "Property.h"

#ifndef einterface
#define einterface interface __declspec(dllexport)
#define eclass class __declspec(dllexport)
#endif

#define exec std::function<void(void*)>

#define P(This,x) Property<x,This>
#define Prop(This,x,f1) Property<x,This>(this,f1)
#define Prop2(This,x,f1,f2) P(This,x)(this,f1,f2)

#define BEGIN namespace Visual{
#define END ;}

#endif