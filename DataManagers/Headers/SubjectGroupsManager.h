#ifndef SUBJECTGROUPSMANAGER_H
#define SUBJECTGROUPSMANAGER_H

#include "Interfaces/IDataManager.h"

namespace DataManagers
{
	eclass SubjectGroupsManager
		:public IDataManager<uint,SubjectGroup,ModelSet<uint,SubjectGroup>>
	{
		public:
			void Read();
			void Save();
	};
}

#endif