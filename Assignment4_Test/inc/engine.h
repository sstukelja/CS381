/*
 * engine.h
 *
 *  Created on: Mar 9, 2017
 *      Author: sushil
 *
 *      Used by: Stefan Stukelja and Alex Crupi
 *      For: CS 381 - Assignment 4
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <GfxMgr.h>
#include <inputMgr.h>
#include <EntityMgr.h>
#include <gameMgr.h>

class Engine {
private:
public:
	Engine();
	~Engine();

	EntityMgr*      entityMgr;
	GfxMgr*         gfxMgr;
	InputMgr*       inputMgr;
	GameMgr*        gameMgr;

	void init();
	void run();
	void tickAll(float dt);
	void stop();
	void shutdown();

	bool keepRunning;
};



#endif /* ENGINE_H_ */
