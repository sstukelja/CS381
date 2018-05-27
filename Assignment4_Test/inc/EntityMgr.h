/*
 * EntityMgr.h
 *
 *  Created on: Feb 22, 2017
 *      Author: sushil
 *
 *      Used by: Stefan Stukelja and Alex Crupi
 *      For: CS 381 - Assignment 4
 */

#ifndef ENTITYMGR_H_
#define ENTITYMGR_H_


#include <list>
#include <OgreVector3.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>

#include <Entity381.h>
#include <mgr.h>

class Engine;

class EntityMgr: public Mgr {

public:
	std::list<Entity381 *> entities;

public:
	Entity381* selectedEntity;

	EntityMgr(Engine *eng);
	~EntityMgr();

	virtual void init();
	virtual void tick(float dt);
	virtual void loadLevel();
	virtual void stop();

	Entity381 *CreateEntity(EntityType entityType, Ogre::Vector3 pos, float yaw = 0);
	void CreateOgreEntityAndNode(Entity381 *ent);
	void SelectNextEntity();

};

#endif /* ENTITYMGR_H_ */
