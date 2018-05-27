/*
 * gameMgr.cpp
 *
 *  Created on: Mar 26, 2017
 *      Authors: Stefan Stukelja and Alex Crupi
 *      For: CS 381 - Assignment 3
 */

#include "gameMgr.h"
#include "engine.h"
#include <OgreMeshManager.h>

GameMgr::GameMgr(Engine *eng)
	: Mgr(eng)
{
	engine = eng;
}

GameMgr::~GameMgr()
{

}

void GameMgr::tick(float dt)
{

}

void GameMgr::init()
{
	mSceneMgr = engine->gfxMgr->mSceneMgr;
}

void GameMgr::loadLevel()
{
	// MakeGround
	  Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	  Ogre::MeshManager::getSingleton().createPlane(
	  	    "ground",
	  	    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  	    plane,
	  	    15000, 15000, 20, 20,
	  	    true,
	  	    1, 5, 5,
	  	    Ogre::Vector3::UNIT_Z);

	  Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
	  mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	  groundEntity->setCastShadows(false);
	  groundEntity->setMaterialName("Ocean2_Cg");

	  // MakeSky
	  mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");

	  // Create Entities
	  loadEnts();
}

void GameMgr::stop()
{

}

void GameMgr::loadEnts()
{
		Entity381 * ent;
		int x = 0;
		ent = engine->entityMgr->CreateEntity(EntityType::CVN, Ogre::Vector3(x, 0, 0), 0);

		x += 300;
		ent = engine->entityMgr->CreateEntity(EntityType::DDG, Ogre::Vector3(x, 0, 0), 0);

		x += 200;
		ent = engine->entityMgr->CreateEntity(EntityType::FRIGATE, Ogre::Vector3(x, 0, 0), 0);

		x += 200;
		ent = engine->entityMgr->CreateEntity(EntityType::CIGARETTE, Ogre::Vector3(x, 0, 0), 0);

		x += 200;
		ent = engine->entityMgr->CreateEntity(EntityType::ALIEN, Ogre::Vector3(x, 0, 0), 0);

		ent->isSelected = true;
}
