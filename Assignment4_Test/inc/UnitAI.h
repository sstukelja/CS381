/*
 * UnitAI.h
 *
 *  Created on: Mar 28, 2017
 *      Author: sushil
 *
 *      Used by: Stefan Stukelja and Alex Crupi
 *      For: CS 381 - Assignment 4
 */

#ifndef UNITAI_H_
#define UNITAI_H_

#include <Aspect.h>
#include <Command.h>
#include <list>

class UnitAI: public Aspect {

public:

	std::list<Command*> commands;

	UnitAI(Entity381* ent);
	~UnitAI();

	void Tick(float dt);
	void SetCommand(Command *c);
	void AddCommand(Command *c);
};

#endif /* UNITAI_H_ */
