#ifndef CLASS_H
#define CLASS_H

#include "Headers/ClassSubjectModel.h"

namespace Models
{
	eclass ClassModel:public IModel<uint>
	{
		inline static uint nextId=0;
		public:
			byte Number;
			char Letter;
			Turn StartTurn;
			TeacherModel* FormMaster;
			vector<ClassSubjectModel*> Subjects;

			ClassModel():IModel(nextId++){ }

			ClassModel(uint id, byte number, char letter, Turn startTurn, TeacherModel* formMaster)
				:IModel(id),
				Number(number),
				Letter(letter),
				StartTurn(startTurn),
				FormMaster(formMaster)
				{
					if(nextId<=id)nextId=id+1;
				}

			ClassModel(byte number, char letter, Turn startTurn, TeacherModel* formMaster)
				:ClassModel(nextId++,number,letter,startTurn,formMaster){ }

			static void SetNextId(uint id)
			{
				nextId=id;
			}
	};
}

#endif
