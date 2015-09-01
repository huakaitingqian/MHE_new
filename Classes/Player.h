#ifndef __PLAYER_H__
#define __PLAYER_H__

#include"Person.h"

class Player: public Person
{
public:
	Player();
	~Player();
	bool init();

	CREATE_FUNC(Player);
};

#endif