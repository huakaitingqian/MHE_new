#ifndef __NPC_H__
#define __NPC_H__
#include"Person.h"
#include"Player.h"

class NPC :public Person
{
public:
	NPC();
	~NPC();
	void update(Player* player);
};

class NPC1 :public NPC
{
public:
	NPC1();
	~NPC1();
	bool init();
	CREATE_FUNC(NPC1);
};

class NPC2 :public Person
{
public:
	NPC2();
	~NPC2();
	bool init();
	CREATE_FUNC(NPC2);
};

class NPC3 :public Person
{
public:
	NPC3();
	~NPC3();
	bool init();
	CREATE_FUNC(NPC3);
};
#endif