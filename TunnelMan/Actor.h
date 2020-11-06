#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

class Actor :public GraphObject {
public:
	Actor(int imageID, int startX, int startY, Direction startDirection, double size, unsigned int depth, StudentWorld * world);

	virtual void doSomething() = 0;
	StudentWorld * getWorld();
	//virtual bool canPickUp() = 0; //returns true if tunnelman can pick up
	//virtual bool isBlocking() = 0; //returns true if actor can block path

	~Actor();

private:
	StudentWorld * m_world;
	//bool m_alive;
	//int m_health;
};

class Earth :public Actor {
public:
	Earth(int startX, int startY, StudentWorld * world);
	virtual void doSomething();
	virtual bool canPickUp();
	virtual bool isBlocking();
	~Earth();
};

class Person : public Actor {
public:
	Person(int imageID, int startX, int startY, Direction startDirection, double size, unsigned int depth, StudentWorld * world);
  virtual void annoyed(int annoyed) = 0; //if actor is annoyed, lose 1 hp
  virtual bool isProtester() = 0; //returns true if protester
  virtual bool isHit() = 0; //if boulder falls on actor, if protester gets hit by squirt, if tunnelman is yelled at by protester
  virtual void doSomething();
  ~Person();

};

class Tunnelman : public Person {
public:
	Tunnelman(StudentWorld * world);
	~Tunnelman();
	virtual void doSomething();
	virtual void annoyed(int annoyed);
	virtual bool isProtester();
	virtual bool isHit();
};
#endif // ACTOR_H_
