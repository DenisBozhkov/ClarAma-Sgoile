#ifndef MULTICLASSSUBJECTSMANAGER_H
#define MULTICLASSSUBJECTSMANAGER_H

#include "ClassesManager.h"

namespace DataManagers
{
	eclass MultiClassSubjectsManager
		:public IDataManager<uint,MultiClassSubject,ModelSet<uint,MultiClassSubject>>
	{
		ClassesManager &classes;
		RoomsManager &rooms;
		SubjectsManager &subjects;
		TeachersManager &teachers;
		public:
			MultiClassSubjectsManager(ClassesManager&,SubjectsManager&,TeachersManager&,RoomsManager&);
			void Read();
			void Save();
	};
}

#endif