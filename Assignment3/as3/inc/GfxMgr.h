/*
 * GfxMgr.h
 *
 *  Created on: Mar 26, 2017
 *      Authors: Stefan Stukelja and Alex Crupi
 *      For: CS 381 - Assignment 3
 */

#ifndef AS3_INC_GFXMGR_H_
#define AS3_INC_GFXMGR_H_

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>
#include "mgr.h"

class GfxMgr
	: public Mgr,
	  public Ogre::WindowEventListener,
	  public Ogre::FrameListener
{
public:
	GfxMgr(Engine *eng);
	~GfxMgr();

	void tick(float dt);
	void init();
	void loadLevel();
	void stop();
	bool go();

	Ogre::Root* mRoot;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
};

#endif /* AS3_INC_GFXMGR_H_ */
