#ifndef IACTIONABLE_H
#define IACTIONABLE_H

#include "Headers/Controller.h"
#include "Configuration.h"

interface IActionable
{
	exec OnLoad;
	protected:
		Service::Controller &controller;
		IActionable(Service::Controller &controller)
			:controller(controller),OnLoad([](void*){}){}
		virtual void InitComponents()=0;
		virtual	void InitConsts()=0;
		virtual	void InitRelations()=0;
		virtual	void LoadData()=0;
};

#endif