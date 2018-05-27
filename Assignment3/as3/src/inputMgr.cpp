/*
 * inputMgr.cpp
 *
 *  Created on: Mar 26, 2017
 *      Authors: Stefan Stukelja and Alex Crupi
 *      For: CS 381 - Assignment 3
 */

#include "inputMgr.h"
#include "engine.h"
#include <OgreRenderWindow.h>

using namespace std;

InputMgr::InputMgr(Engine *eng)
	: Mgr(eng),
	  mInputMgr(0),
	  mKeyboard(0)
{
	engine = eng;
	keyboardTimer = keyTime;
	selectionTimer = selectionTime;
}

InputMgr::~InputMgr()
{

}

void InputMgr::tick(float dt)
{

}

void InputMgr::init()
{
	// OIS
	  Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");

	  OIS::ParamList pl;
	  size_t windowHandle = 0;
	  std::ostringstream windowHandleStr;

	  engine->gfxMgr->mWindow->getCustomAttribute("WINDOW", &windowHandle);
	  windowHandleStr << windowHandle;
	  pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));

	  mInputMgr = OIS::InputManager::createInputSystem(pl);

	  mKeyboard = static_cast<OIS::Keyboard*>(
	  mInputMgr->createInputObject(OIS::OISKeyboard, true));

	  windowResized(engine->gfxMgr->mWindow);
	  Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->mWindow, this);

	  engine->gfxMgr->mRoot->addFrameListener(this);

	// Camera
	  mCamera = engine->gfxMgr->mCamera;

	// A node to attach the camera to so we can move the camera node instead of the camera.
	  cameraNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	  cameraNode->setPosition(0, 200, 500);
	  cameraNode->attachObject(mCamera);
}

void InputMgr::loadLevel()
{

}

void InputMgr::stop()
{

}

void InputMgr::windowResized(Ogre::RenderWindow* rw)
{

}

void InputMgr::windowClosed(Ogre::RenderWindow* rw)
{
  if(rw == engine->gfxMgr->mWindow)
  {
    if(mInputMgr)
    {
        mInputMgr->destroyInputObject(mKeyboard);

        OIS::InputManager::destroyInputSystem(mInputMgr);
    	mInputMgr = 0;
    	engine->stop();
    }
  }
}

bool InputMgr::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
  if (engine->gfxMgr->mWindow->isClosed()) return false;
    mKeyboard->capture();

  if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
	  {
	  	  engine->stop();
	  	  return false;
	  }
  UpdateEnts(fe);
  UpdateCamera(fe);

  return true;
}

void InputMgr::UpdateCamera(const Ogre::FrameEvent& fe)
{
	float move = 400.0f;
	float rotate = 0.1f;

	 Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;

	  if (mKeyboard->isKeyDown(OIS::KC_W))
	    dirVec.z -= move;

	  if (mKeyboard->isKeyDown(OIS::KC_S))
	    dirVec.z += move;

	  if (mKeyboard->isKeyDown(OIS::KC_NUMPAD9))
	    dirVec.y += move;

	  if (mKeyboard->isKeyDown(OIS::KC_NUMPAD3))
	    dirVec.y -= move;

	  if (mKeyboard->isKeyDown(OIS::KC_A))
	    dirVec.x -= move;

	  if (mKeyboard->isKeyDown(OIS::KC_D))
	    dirVec.x += move;

	  if (mKeyboard->isKeyDown(OIS::KC_Q))
		cameraNode->yaw(Ogre::Degree(.5 * rotate));

	  if (mKeyboard->isKeyDown(OIS::KC_E))
	  	cameraNode->yaw(Ogre::Degree(-.5 * rotate));

	  if (mKeyboard->isKeyDown(OIS::KC_Z))
	  	cameraNode->pitch(Ogre::Degree(.5 * rotate));

	  if (mKeyboard->isKeyDown(OIS::KC_X))
	  	cameraNode->pitch(Ogre::Degree(-.5 * rotate));

	  cameraNode->translate(dirVec * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
}

void InputMgr::UpdateEnts(const Ogre::FrameEvent& fe)
{
	selectionTimer -= fe.timeSinceLastFrame;
	keyboardTimer -= fe.timeSinceLastFrame;

	if(selectionTimer < 0 && mKeyboard->isKeyDown(OIS::KC_TAB))
	{
		selectionTimer = this->selectionTime;
		engine->entityMgr->SelectNextEntity();
	}

	if(engine->entityMgr->selectedEntity)
	{
		if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD8))
		{
			keyboardTimer = keyTime;
			engine->entityMgr->selectedEntity->desiredSpeed += 10;
		}

		if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD2))
		{
			keyboardTimer = keyTime;
			engine->entityMgr->selectedEntity->desiredSpeed -= 10;
		}

		// Clamp
		engine->entityMgr->selectedEntity->desiredSpeed = std::max(engine->entityMgr->selectedEntity->minSpeed,
				std::min(engine->entityMgr->selectedEntity->maxSpeed, engine->entityMgr->selectedEntity->desiredSpeed));

		if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD4))
		{
			keyboardTimer = keyTime;
			engine->entityMgr->selectedEntity->desiredHeading -= 0.3f;
		}

		if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD6))
		{
			keyboardTimer = keyTime;
			engine->entityMgr->selectedEntity->desiredHeading += 0.3f;
		}
	}
}
