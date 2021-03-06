/*
 * GxfMgr.h
 *
 *  Created on: Mar 9, 2017
 *      Author: sushil
 *
 *      Used by: Stefan Stukelja and Alex Crupi
 *      For: CS 381 - Assignment 4
 */

#ifndef GFXMGR_H_
#define GFXMGR_H_

#include <mgr.h>
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>

class GfxMgr : public Mgr {

public:
	//Ogre variables
	Ogre::Root *ogreRoot;
	Ogre::Camera* ogreCamera;
	Ogre::String resources;
	Ogre::String plugins;
	Ogre::ConfigFile cf;
	void loadConfig(Ogre::ConfigFile cf);
	void configureRenderSystem();
	void initResources();

	void createSceneManager();
	void createCamera();
	Ogre::Viewport *ogreViewport;
	void createViewport();

public:

	GfxMgr(Engine *eng);
	~GfxMgr();

	virtual void tick(float dt);
	virtual void init();
	virtual void loadLevel();
	virtual void stop();

	Ogre::RenderWindow* ogreRenderWindow;
	Ogre::SceneManager* ogreSceneManager;
	Ogre::SceneNode *cameraNode, *pitchNode;

	void testScene();
};

#endif /* GFXMGR_H_ */
