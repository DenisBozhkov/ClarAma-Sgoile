#ifndef CLASSESMANAGER_H
#define CLASSESMANAGER_H

#include "RoomsManager.h"
#include "SubjectsManager.h"
#include "TeachersManager.h"

namespace DataManagers
{
	eclass ClassesManager
		:public IDataManager<uint,Class,ModelSet<uint,Class>>
	{
		RoomsManager &rooms;
		SubjectsManager &subjects;
		TeachersManager &teachers;
		public:
			ClassesManager(SubjectsManager&,TeachersManager&,RoomsManager&);
			void Read();
			void Save();
	};
}

#endif