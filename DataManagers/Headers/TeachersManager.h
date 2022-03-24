#ifndef TEACHERSMANAGER_H
#define TEACHERSMANAGER_H

#include "Interfaces/IDataManager.h"
#include "Headers/SchoolData.h"

namespace DataManagers
{
	eclass TeachersManager
		:public IDataManager<uint,Teacher,ModelSet<uint,Teacher>>
	{
		SchoolData &data;
		public:
			TeachersManager(SchoolData&);
			void Read();
			void Save();
	};
}

#endif