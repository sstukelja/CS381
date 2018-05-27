/*
 * InputMgr.h
 *
 *  Created on: Mar 26, 2017
 *      Authors: Stefan Stukelja and Alex Crupi
 *      For: CS 381 - Assignment 3
 */

#ifndef AS3_INC_INPUTMGR_H_
#define AS3_INC_INPUTMGR_H_

#include "mgr.h"
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>

class InputMgr
	: public Mgr,
	  public Ogre::WindowEventListener,
	  public Ogre::FrameListener
{
public:
	InputMgr(Engine *eng);
	~InputMgr();

	void tick(float dt);
	void init();
	void loadLevel();
	void stop();

	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow* rw);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
	void UpdateCamera(const Ogre::FrameEvent& fe);
	void UpdateEnts(const Ogre::FrameEvent& fe);

	OIS::InputManager* mInputMgr;
	OIS::Keyboard* mKeyboard;
	Ogre::Camera* mCamera;
	Ogre::SceneNode* cameraNode;

	float keyboardTimer;
	float selectionTimer;
	const float keyTime = 0.2f;
	const float selectionTime = 0.2f;
};

#endif /* AS3_INC_INPUTMGR_H_ */
