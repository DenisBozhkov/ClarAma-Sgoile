#ifndef ROOMSMANAGER_H
#define ROOMSMANAGER_H

#include "Interfaces/IDataManager.h"

namespace DataManagers
{
	eclass RoomsManager
		:public IDataManager<uint,Room,ModelSet<uint,Room>>
	{
		public:
			void Read();
			void Save();
	};
}

#endif