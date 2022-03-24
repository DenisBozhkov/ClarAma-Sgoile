#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "config.h"
#include "DataManagers.h"

namespace Service
{
	eclass Controller
	{
		public:
			Controller();
			~Controller();

			DataManagers::SchoolData* MainData;

			DataManagers::ClassesManager* Classes;
			DataManagers::MultiClassSubjectsManager* MultiClassSubjects;
			DataManagers::RoomsManager* Rooms;
			DataManagers::SubjectGroupsManager* SubjectGroups;
			DataManagers::SubjectsManager* Subjects;
			DataManagers::TeachersManager* Teachers;

			void SaveAll();
	};
}

#endif