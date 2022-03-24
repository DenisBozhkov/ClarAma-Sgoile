#ifndef SMALLSET_H
#define SMALLSET_H

#include "config.h"

namespace Structures
{
	eclass SmallSet
	{
		llong map1,map2;
		SmallSet(llong map1,llong map2)
			:map1(map1),map2(map2){ }
		public:
			SmallSet()
				:map1(0),map2(0){ }
			SmallSet(vector<int> vec)
				:map1(0),map2(0)
			{
				for(int i=0;i<vec.size();i++)
					Add(vec[i]);
			}

			void Add(byte index)
			{
				if(index<64)map1|=(1ll<<index);
				else map2|=(1ll<<(index-64));
			}
			void Add(SmallSet smallSet)
			{
				map1|=smallSet.map1;
				map2|=smallSet.map2;
			}

			void Change(byte index)
			{
				if(index<64)map1^=(1ll<<index);
				else map2^=(1ll<<(index-64));
			}
			void Change(SmallSet smallSet)
			{
				map1^=smallSet.map1;
				map2^=smallSet.map2;
			}

			void Remove(byte index)
			{
				if(index<64)map1&=~(1ll<<index);
				else map2&=~(1ll<<(index-64));
			}
			void Remove(SmallSet smallSet)
			{
				map1&=~smallSet.map1;
				map2&=~smallSet.map2;
			}

			bool At(byte index)
			{
				if(index<64)
					return (map1>>index)&1ll;
				else return (map2>>(index-64))&1ll;
			}
			SmallSet Intersect(SmallSet smallSet)
			{
				return SmallSet(map1&smallSet.map1,map2&smallSet.map2);
			}
			SmallSet Merge(SmallSet smallSet)
			{
				return SmallSet(map1|smallSet.map1,map2|smallSet.map2);
			}
			bool IsEmpty()
			{
				return map1==0&&map2==0;
			}
			vector<byte> ToVector()
			{
				vector<byte> ret;
				for(byte i=0;i<128;i++)
					if(At(i))
						ret.push_back(i);
				return ret;
			}
	};
}

#endif
