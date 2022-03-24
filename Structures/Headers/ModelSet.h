#ifndef MODELSET_H
#define MODELSET_H

#include "Interfaces/IStructure.h"

namespace Structures
{
	template<typename K,class T> eclass ModelSet:public IStructure<K,T>
	{
		uint size;
		map<K,T*> models;
		map<K,T*>::iterator it;
		public:
			ModelSet()
				:size(0){ }

			void Add(T* model)
			{

				if(models.find(model->Id())!=models.end())
					return;
				models.insert(make_pair(model->Id(),model));
				size++;
			}
			T* Get(K id)
			{
				if(models.find(id)==models.end())
					return nullptr;
				return models[id];
			}
			void Delete(K id)
			{
				if(models.find(id)==models.end())
					return;
				models.erase(id);
				size--;
			}

			vector<T*> ToVector()
			{
				static T* item;
				vector<T*> ret;

				for(item=Begin();item!=nullptr;item=Next())
					ret.push_back(item);
				return ret;
			}

			uint Size()
			{
				return size;
			}

			T* Begin()
			{
				it=models.begin();
				return (*it).second;
			}
			T* Next()
			{
				it++;
				return (it==models.end())?nullptr:(*it).second;
			}
	};
}

#endif
