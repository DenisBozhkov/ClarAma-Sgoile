#ifndef PROPERTY_H
#define PROPERTY_H

#include<functional>
#include<exception>

template<typename Type,class In> class Property
{
	protected:
		Type value;
		std::function<Type(In*,Type*)> get;
		std::function<void(In*,Type*,Type)> set;
		In* base;
	public:
		Type operator=(Property<Type,In> prop)
		{ return value=(Type)prop; }
		Property(){}
		Property(In* base,std::function<Type(In*,Type*)> get,std::function<void(In*,Type*,Type)> set)
			:base(base)
		{
			this->get=get;
			this->set=set;
		}
		Property(In* base,std::function<Type(In*,Type*)> get)
			:base(base)
		{
			this->get=get;
			this->set=[](In*,Type*,Type){ throw std::runtime_error("You cannot set new value to this property"); };
		}
		Property(In* base,std::function<void(In*,Type*,Type)> set)
			:base(base)
		{
			this->get=[](In*,Type*){ throw std::runtime_error("You cannot get the value of this property"); return *new Type; };
			this->set=set;
		}
		Property(In* base)
			:base(base)
		{
			this->get=[](In*,Type* destination){return *destination;};
			this->set=[](In*,Type* destination,Type value){*destination=value;};
		}
		Type operator=(Type value)
		{
			set(base,&this->value,value); 
			return value;
		}
		operator Type()
		{ return get(base,&this->value); }
		
		static void DefaultSet(In*,Type* destination,Type value)
		{ *destination=value; }
		static Type DefaultGet(In*,Type* destination)
		{ return *destination; }
		
		template<class PType,class PIn> friend void Assign(Property<PType,PIn> &prop,PType value);
		template<class PType,class PIn> friend void Assign(Property<PType,PIn> &prop,Property<PType,PIn> value);
};

template<class PType,class PIn> void Assign(Property<PType,PIn> &prop,PType value)
{ prop.value=value; }
template<class PType,class PIn> void Assign(Property<PType,PIn> &prop,Property<PType,PIn> value)
{
	prop.get=value.get;
	prop.set=value.set;
	prop.base=value.base;
}

#endif