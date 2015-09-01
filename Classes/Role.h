#ifndef __ROLE_H__
#define __ROLE_H__

#include "Person.h"

class Role1 : public Person
{
public:
	Role1();
	~Role1();
	bool init();
	CREATE_FUNC(Role1);
};


class Role2: public Person
{
public:
	Role2();
	~Role2();
	bool init();
	CREATE_FUNC(Role2);
};


class Role3: public Person
{
public:
	Role3();
	~Role3();
	bool init();
	CREATE_FUNC(Role3);
};

class Role4: public Person
{
public:
	Role4();
	~Role4();
	bool init();
	CREATE_FUNC(Role4);;
};


#endif