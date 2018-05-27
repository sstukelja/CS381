/*
 * mgr.h
 *
 *  Created on: Mar 9, 2017
 *      Author: sushil
 *
 *      Used by: Stefan Stukelja and Alex Crupi
 *      For: CS 381 - Assignment 4
 */

#ifndef MGR_H_
#define MGR_H_

class Engine;

class Mgr {
public:
	Engine *engine;

	Mgr(Engine *eng);
	virtual ~Mgr();

	virtual void tick(float dt);
	virtual void init();
	virtual void loadLevel();
	virtual void stop();
};

#endif /* MGR_H_ */
