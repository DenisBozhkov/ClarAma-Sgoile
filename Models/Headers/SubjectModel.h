#ifndef SUBJECT_H
#define SUBJECT_H

#include "Headers/SubjectGroupModel.h"
#include "Interfaces/IModel.h"

namespace Models
{
	eclass SubjectModel:public IModel<uint>
	{
		inline static uint nextId=0;
		public:
			string Name;
			SubjectType Type;
			uint MaxClassesPerDay;
			vector<SubjectGroupModel*> Groups;

			SubjectModel():IModel(nextId++){ }

			SubjectModel(uint id, string name, SubjectType type, uint maxClassesPerDay)
				:IModel(id),
				Name(name),
				Type(type),
				MaxClassesPerDay(maxClassesPerDay)
				{
					if(nextId<=id)nextId=id+1;
				}

			SubjectModel(string name, SubjectType type, uint maxClassesPerDay)
				:SubjectModel(nextId++,name,type,maxClassesPerDay){ }

			static void SetNextId(int id)
			{
				nextId=id;
			}
	};
}

#endif
