#ifndef SCHOOLDATA_H
#define SCHOOLDATA_H

#include "Interfaces/IDataManager.h"

namespace DataManagers
{
	eclass SchoolData
	{
		public:
			byte DaysCount;
			byte HoursPerDay;
			byte HoursPerTurn;

			void Read();
			void Save();
	};
}

#endif