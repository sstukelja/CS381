/*
 * gameMgr.h
 *
 *  Created on: Mar 11, 2017
 *      Author: sushil
 *
 *      Used by: Stefan Stukelja and Alex Crupi
 *      For: CS 381 - Assignment 4
 */

#ifndef GAMEMGR_H_
#define GAMEMGR_H_

#include <mgr.h>
#include <OgreMeshManager.h>

class GameMgr : public Mgr {

private:
	void createEnts();
	void createSky();
	void createGround();

public:
	GameMgr(Engine *engine);
	~GameMgr();
	virtual void init();
	virtual void tick(float dt);
	virtual void loadLevel();
	virtual void stop();

	Ogre::Plane plane;
};

#endif /* GAMEMGR_H_ */
