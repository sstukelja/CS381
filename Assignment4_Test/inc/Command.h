/*
 * Command.h
 *
 *  Created on: Mar 28, 2017
 *      Author: sushil
 *
 *      Used by: Stefan Stukelja and Alex Crupi
 *      For: CS 381 - Assignment 4
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <Entity381.h>
#include <OgreVector3.h>

enum COMMAND_TYPE {MOVE, FOLLOW};

class Command {

public:
	Command(Entity381* ent, COMMAND_TYPE ct);
	virtual ~Command();

	virtual void init();
	virtual void tick(float dt);
	virtual bool done();

	Entity381* entity;
	COMMAND_TYPE commandType;

};

class MoveTo: public Command {

public:
	MoveTo(Entity381* ent, Ogre::Vector3 location);
	~MoveTo();

	void init();
	void tick(float dt);
	bool done();

	Ogre::Vector3 targetLocation;
	float MOVE_DISTANCE_THRESHOLD;

};

class Follow: public Command {

public:
	Follow(Entity381* entFollower, Entity381* entTarget);
	~Follow();

	void init();
	void tick(float dt);
	bool done();

	Entity381* target;
	float MOVE_DISTANCE_THRESHOLD;

};

#endif /* COMMAND_H_ */
