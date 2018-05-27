/*
 * gameMgr.h
 *
 *  Created on: Mar 26, 2017
 *      Authors: Stefan Stukelja and Alex Crupi
 *      For: CS 381 - Assignment 3
 */

#ifndef AS3_INC_GAMEMGR_H_
#define AS3_INC_GAMEMGR_H_

#include "mgr.h"
#include <OgreRoot.h>

class GameMgr : public Mgr
{
public:
	GameMgr(Engine *eng);
	~GameMgr();

	void tick(float dt);
	void init();
	void loadLevel();
	void stop();
	void loadEnts();

	Ogre::SceneManager* mSceneMgr;
};

#endif /* AS3_INC_GAMEMGR_H_ */
