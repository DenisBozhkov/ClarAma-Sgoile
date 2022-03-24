#ifndef SUBJECTGROUPMODEL_H
#define SUBJECTGROUPMODEL_H

#include "Interfaces/IModel.h"

namespace Models
{
	eclass SubjectGroupModel:public IModel<uint>
	{
		inline static uint nextId=0;
		public:
			string Name;
			uint MaxClassesPerDay;
			bool EveryDay;

			SubjectGroupModel():IModel(nextId++){ }

			SubjectGroupModel(uint id, string name, uint maxClassesPerDay, bool everyDay)
				:IModel(id),
				Name(name),
				MaxClassesPerDay(maxClassesPerDay),
				EveryDay(everyDay)
				{
					if(nextId<=id)nextId=id+1;
				}

			SubjectGroupModel(string name, uint maxClassesPerDay, bool everyDay)
				:SubjectGroupModel(nextId++,name,maxClassesPerDay,everyDay){ }

			static void SetNextId(int id)
			{
				nextId=id;
			}
	};
}

#endif
