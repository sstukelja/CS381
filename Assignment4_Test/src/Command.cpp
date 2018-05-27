/*
 * Command.cpp
 *
 *  Created on: Apr 2, 2017
 *      Authors: Stefan Stukelja and Alex Crupi
 *      For: CS 381 - Assignment 4
 */

#include "Command.h"
#include <UnitAI.h>

Command::Command(Entity381* ent, COMMAND_TYPE ct)
{
	entity = ent;
	commandType = ct;
}

Command::~Command()
{

}

void Command::init()
{

}

void Command::tick(float dt)
{

}

bool Command::done()
{
	return true;
}

MoveTo::MoveTo(Entity381* ent, Ogre::Vector3 location) : Command(ent, COMMAND_TYPE::MOVE)
{
	targetLocation = location;
	MOVE_DISTANCE_THRESHOLD = 25;
}

MoveTo::~MoveTo()
{

}

void MoveTo::init()
{

}

void MoveTo::tick(float dt)
{
	entity->desiredSpeed = entity->maxSpeed;

	float xDistance = targetLocation.x - entity->pos.x;
	float zDistance = targetLocation.z - entity->pos.z;
	entity->desiredHeading = atan2(zDistance, xDistance);

	if(entity->pos.x > (targetLocation.x - MOVE_DISTANCE_THRESHOLD) &&
		entity->pos.x < (targetLocation.x + MOVE_DISTANCE_THRESHOLD) &&
		 entity->pos.z > (targetLocation.z - MOVE_DISTANCE_THRESHOLD) &&
		  entity->pos.z < (targetLocation.z + MOVE_DISTANCE_THRESHOLD))
	{
		entity->desiredSpeed = 0;
		entity->speed = 0;
		done();
	}
}

bool MoveTo::done()
{
	entity->ai->commands.pop_front();

	return true;
}

Follow::Follow(Entity381* entFollower, Entity381* entTarget) : Command(entFollower, COMMAND_TYPE::MOVE)
{
	target = entTarget;
	MOVE_DISTANCE_THRESHOLD = 200;
}

Follow::~Follow()
{

}

void Follow::init()
{

}

void Follow::tick(float dt)
{
	entity->desiredSpeed = entity->maxSpeed;

	float xDistance = target->pos.x - entity->pos.x;
	float zDistance = target->pos.z - entity->pos.z;
	entity->desiredHeading = atan2(zDistance, xDistance);

	if(entity->pos.x > (target->pos.x - MOVE_DISTANCE_THRESHOLD) &&
		entity->pos.x < (target->pos.x + MOVE_DISTANCE_THRESHOLD) &&
		 entity->pos.z > (target->pos.z - MOVE_DISTANCE_THRESHOLD) &&
		  entity->pos.z < (target->pos.z + MOVE_DISTANCE_THRESHOLD))
	{
		if(target->speed == 0)
			entity->speed = 0;

		entity->desiredSpeed = target->speed;
		done();
	}
}

bool Follow::done()
{
	return true;
}


