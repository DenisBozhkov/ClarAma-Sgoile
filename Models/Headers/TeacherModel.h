#ifndef TEACHER_H
#define TEACHER_H

#include "Interfaces/IModel.h"

namespace Models
{
	eclass TeacherModel:public IModel<uint>
	{
		inline static uint nextId=0;
		public:
			byte Number;
			string Name;
			vector<vector<bool>> IsFree;

			TeacherModel():IModel(nextId++){ }

			TeacherModel(uint id, byte number, string name, byte days, byte hours)
				:IModel(id),
				Number(number),
				Name(name)
				{
					if(nextId<=id)nextId=id+1;
					IsFree.resize(days,vector<bool>(hours,true));
				}

			TeacherModel(byte number, string name, byte days, byte hours)
				:TeacherModel(nextId++,number,name,days,hours){ }

			static void SetNextId(int id)
			{
				nextId=id;
			}
	};
}

#endif
