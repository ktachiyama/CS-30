#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir): GameWorld(assetDir)
	{
	}

	virtual int init()
	{
		m_tunnelman = new Tunnelman(this); //create tunnelman
		for (int i = 0; i < 64; i++)
		{
			for (int j = 0; j < 64; j++)
			{
				if ((29 < j) && (j < 34) && (i > 3)) //middle column should not have dirt, but bottom 3 rows should have dirt
					m_EarthPixel[i][j] = nullptr;
				else if (i == 60 || i == 61 || i == 62 || i == 63)	//top 4 rows should not be covered by the dirt
					m_EarthPixel[i][j] = nullptr;
				else
					m_EarthPixel[i][j] = new Earth(j, i, this);	 //create dirt
			}
		}
		return GWSTATUS_CONTINUE_GAME;
	}

	virtual int move()
	{
		// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
		// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
		decLives();
		m_tunnelman->doSomething();
		return GWSTATUS_CONTINUE_GAME;
	}

	virtual void cleanUp()
	{
	}

private:
	Earth * m_EarthPixel[64][64]; //[row][column]
	Tunnelman * m_tunnelman;
};

#endif // STUDENTWORLD_H_
