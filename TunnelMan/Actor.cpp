#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, int startX, int startY, Direction startDirection, double size, unsigned int depth, StudentWorld * world) :GraphObject(imageID, startX, startY, startDirection, size, depth)
{
	setVisible(true);
}

Actor::~Actor()
{

}
StudentWorld * Actor::getWorld()
{
	return m_world;
}

//int Actor::getHP() const
//{
//	return m_health;
//}

//void Actor::setHP(int hp)
//{
//	m_health = hp;
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Earth::Earth(int startX, int startY, StudentWorld * world) :Actor(TID_EARTH, startX, startY, right, .25, 3, world)
{
	setVisible(true);
}

void Earth::doSomething()
{

}

bool Earth::canPickUp()
{
	return false;
}

bool Earth::isBlocking()
{
	return false;
}


Earth::~Earth()
{

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Person::Person(int imageID, int startX, int startY, Direction startDirection, double size, unsigned int depth, StudentWorld * world):Actor(imageID, startX, startY, startDirection, size, depth, world)
{
	setVisible(true);
}
Person::~Person()
{

}
void Person::doSomething()
{
	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Tunnelman::Tunnelman(StudentWorld * world):Person(TID_PLAYER, 30, 60, right, 1.0, 0, world)
{

}
Tunnelman::~Tunnelman()
{

}
void Tunnelman::doSomething()
{
	int key;
	if (getWorld()->getKey(key))
	{
		switch (key)
		{
		case KEY_PRESS_LEFT:
			if (getDirection() != left)
			{
				setDirection(left);
			}
			break;
		}

	}
}
void Tunnelman::annoyed(int annoyed)
{

}
bool Tunnelman::isProtester()
{
	return false;
}
bool Tunnelman::isHit()
{
	return 0;
}