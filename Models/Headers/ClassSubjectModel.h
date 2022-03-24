#ifndef CLASSSUBJECT_H
#define CLASSSUBJECT_H

#include "Headers/RoomModel.h"
#include "Headers/SubjectModel.h"
#include "Headers/TeacherModel.h"

namespace Models
{
	eclass ClassSubjectModel:protected virtual IModel<uint>
	{
		public:
			SubjectModel* Subject;
			float ClassesPerWeek;
			vector<TeacherModel*> Teachers;
			vector<RoomModel*> Rooms;

			ClassSubjectModel():IModel(0){ }

			ClassSubjectModel(SubjectModel* subject, float classesPerWeek)
				:IModel(0),Subject(subject),ClassesPerWeek(classesPerWeek){ }
	};
}

#endif
