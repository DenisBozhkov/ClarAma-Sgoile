#ifndef MULTICLASSSUBJECT_H
#define MULTICLASSSUBJECT_H

#include "Headers/ClassModel.h"

namespace Models
{
	eclass MultiClassSubjectModel:public virtual IModel<uint>,public virtual ClassSubjectModel
	{
		inline static uint nextId;
		public:
			vector<ClassModel*> Classes;

			MultiClassSubjectModel():IModel(nextId++){ }

			MultiClassSubjectModel(int id,SubjectModel* subject, float classesPerWeek)
				:IModel(id),ClassSubjectModel(subject,classesPerWeek)
				{
					if(nextId<=id)
						nextId=id+1;
				}
			MultiClassSubjectModel(SubjectModel* subject, float classesPerWeek)
				:MultiClassSubjectModel(nextId++,subject,classesPerWeek){ }

			static void SetNextId(uint id)
			{
				nextId=id;
			}
	};
}

#endif
