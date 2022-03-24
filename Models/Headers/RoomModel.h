#ifndef ROOM_H
#define ROOM_H

#include "Enums/Enums.h"
#include "Interfaces/IModel.h"

namespace Models
{
	eclass RoomModel:public IModel<uint>
	{
		inline static uint nextId=0;
		public:
			string Name;
			byte MaxClasses;
			RoomType Type;

			RoomModel():IModel(nextId++){ }

			RoomModel(uint id, string name, byte maxClasses, RoomType type)
				:IModel(id),
				Name(name),
				MaxClasses(maxClasses),
				Type(type)
				{
					if(nextId<=id)nextId=id+1;
				}

			RoomModel(string name, byte maxClasses, RoomType type)
				:RoomModel(nextId++,name,maxClasses,type){ }

			static void SetNextId(int id)
			{
				nextId=id;
			}
	};
}

#endif
