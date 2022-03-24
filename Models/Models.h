#ifndef MODELS_H
#define MODELS_H

#include "Enums/Enums.h"

#include "Interfaces/IModel.h"

#include "Headers/ClassModel.h"
#include "Headers/ClassSubjectModel.h"
#include "Headers/MultiClassSubjectModel.h"
#include "Headers/RoomModel.h"
#include "Headers/SubjectGroupModel.h"
#include "Headers/SubjectModel.h"
#include "Headers/TeacherModel.h"

namespace Models
{
	typedef ClassModel Class;
	typedef ClassSubjectModel ClassSubject;
	typedef MultiClassSubjectModel MultiClassSubject;
	typedef RoomModel Room;
	typedef SubjectGroupModel SubjectGroup;
	typedef SubjectModel Subject;
	typedef TeacherModel Teacher;

}

#endif