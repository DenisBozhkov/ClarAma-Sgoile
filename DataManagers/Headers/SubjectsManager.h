#ifndef SUBJECTSMANAGER_H
#define SUBJECTSMANAGER_H

#include "SubjectGroupsManager.h"

namespace DataManagers
{
	eclass SubjectsManager
		:public IDataManager<uint,Subject,ModelSet<uint,Subject>>
	{
		SubjectGroupsManager &subjectGroups;
		public:
			SubjectsManager(SubjectGroupsManager&);
			void Read();
			void Save();
	};
}

#endif