/*
 * inputMgr.cpp
 *
 *  Created on: Mar 11, 2017
 *      Author: sushil
 *
 *      Used by: Stefan Stukelja and Alex Crupi
 *      For: CS 381 - Assignment 4
 */

#include <inputMgr.h>
#include <engine.h>
#include <OgreSceneNode.h>
#include <Command.h>
#include <Aspect.h>
#include <UnitAI.h>
#include <OgreEntity.h>
#include <OgreAxisAlignedBox.h>
#include <iostream>

InputMgr::InputMgr(Engine *engine) : Mgr(engine){
	keyboardTimer = keyTime;
	selectionTimer = selectionTime;

	keyboard = 0;
	mouse = 0;
	oisInputManager = 0;

	OIS::ParamList pl;
	size_t windowHandle = 0;
	std::ostringstream windowHandleStr;
	engine->gfxMgr->ogreRenderWindow->getCustomAttribute("WINDOW", &windowHandle);
	windowHandleStr << windowHandle;

	pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));

	// insert the following lines right before calling mInputSystem = OIS::InputManager::createInputSystem( paramList );
#if defined OIS_WIN32_PLATFORM
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
	pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
	pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
	pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
	pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif

	oisInputManager = OIS::InputManager::createInputSystem(pl);
	keyboard = static_cast<OIS::Keyboard*>(oisInputManager->createInputObject(OIS::OISKeyboard, true));
	mouse    = static_cast<OIS::Mouse*>(oisInputManager->createInputObject(OIS::OISMouse, true));

	keyboard->setEventCallback(this);
	mouse->setEventCallback(this);

	windowResized(engine->gfxMgr->ogreRenderWindow);
	Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->ogreRenderWindow, this);

}

InputMgr::~InputMgr()
{

}

void InputMgr::init()
{

}

void InputMgr::loadLevel()
{

}

void InputMgr::tick(float dt)
{

	keyboard->capture();
	mouse->capture();
	if(keyboard->isKeyDown(OIS::KC_ESCAPE))
		engine->stop();

	UpdateCamera(dt);
	UpdateDesiredSpeedHeading(dt);

}

void InputMgr::stop()
{
	if (oisInputManager)
	{
		oisInputManager->destroyInputObject(mouse);
		oisInputManager->destroyInputObject(keyboard);
		OIS::InputManager::destroyInputSystem(oisInputManager);
		oisInputManager = 0;
	}
}

void InputMgr::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void InputMgr::windowClosed(Ogre::RenderWindow* rw)
{
	if(rw == engine->gfxMgr->ogreRenderWindow)
		engine->stop();
}

bool InputMgr::keyPressed(const OIS::KeyEvent &arg)
{
	return true;
}
bool InputMgr::keyReleased(const OIS::KeyEvent &arg)
{
	if (arg.key == OIS::KC_TAB)
	{
		engine->entityMgr->SelectNextEntity();
		std::cout << engine->entityMgr->selectedEntity->selectionOutput << std::endl << std::endl;
	}

	return true;
}

bool InputMgr::mouseMoved(const OIS::MouseEvent &arg)
{
	return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	if(mouse->getMouseState().buttonDown(OIS::MB_Left))
	{
		Ogre::Real screenWidth = Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
		Ogre::Real screenHeight = Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();
		OIS::MouseState arg = mouse->getMouseState();

		Ogre::Real offsetX = arg.X.abs / screenWidth;
		Ogre::Real offsetY = arg.Y.abs / screenHeight;

		Ogre::Ray mouseRay = engine->gfxMgr->ogreCamera->getCameraToViewportRay(offsetX, offsetY);
		std::pair<bool, float> result = mouseRay.intersects(engine->gameMgr->plane);

		if(result.first)
		{
			Ogre::Vector3 point = mouseRay.getPoint(result.second);
			std::cout << "Point in world" << point << std::endl;
			Entity381* ent;
			for (std::list<Entity381 *>::const_iterator it = engine->entityMgr->entities.begin(); it != engine->entityMgr->entities.end(); it++)
			{
				(*it)->isSelected = false;
				Ogre::Vector3 size = (*it)->ogreEntity->getWorldBoundingBox().getHalfSize();
				std::cout << size << std::endl;

				if(point.x > ((*it)->pos.x - (size.x + 25)) &&
					point.x < ((*it)->pos.x + (size.x + 25)) &&
					 point.z > ((*it)->pos.z - (size.z + 25)) &&
					  point.z < ((*it)->pos.z + (size.z + 25)))
				{
					ent = (*it);
				}
			}

			if(ent)
			{
				ent->isSelected = true;
				std::cout << ent->selectionOutput << std::endl << std::endl;
			}
		}
	}

	if(mouse->getMouseState().buttonDown(OIS::MB_Right))
	{
		Ogre::Real screenWidth = Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
		Ogre::Real screenHeight = Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();
		OIS::MouseState arg = mouse->getMouseState();

		Ogre::Real offsetX = arg.X.abs / screenWidth;
		Ogre::Real offsetY = arg.Y.abs / screenHeight;

		Ogre::Ray mouseRay = engine->gfxMgr->ogreCamera->getCameraToViewportRay(offsetX, offsetY);
		std::pair<bool, float> result = mouseRay.intersects(engine->gameMgr->plane);

		if(result.first)
		{
			Ogre::Vector3 point = mouseRay.getPoint(result.second);
			std::cout << point << std::endl;

			Ogre::Real min = 100;
			Entity381* ent = NULL;
			for (std::list<Entity381 *>::const_iterator it = engine->entityMgr->entities.begin(); it != engine->entityMgr->entities.end(); it++)
			{
				if(point.distance((*it)->pos) < min)
				{
					min = point.distance((*it)->pos);
					ent = (*it);
				}
			}

			if(keyboard->isKeyDown(OIS::KC_LSHIFT))
			{
				if(ent == NULL)
				{
					Command* c = new MoveTo(engine->entityMgr->selectedEntity, point);
					engine->entityMgr->selectedEntity->ai->AddCommand(c);
				}

				else
				{
					Command* c = new Follow(engine->entityMgr->selectedEntity, ent);
					engine->entityMgr->selectedEntity->ai->SetCommand(c);
				}
			}

			else
			{
				if(ent == NULL)
				{
					Command* c = new MoveTo(engine->entityMgr->selectedEntity, point);
					engine->entityMgr->selectedEntity->ai->SetCommand(c);
				}

				else
				{
					Command* c = new Follow(engine->entityMgr->selectedEntity, ent);
					engine->entityMgr->selectedEntity->ai->SetCommand(c);
				}
			}
		}
	}

	return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return true;
}

void InputMgr::UpdateCamera(float dt)
{
	float move = 100.0f;
	float rotate = 0.1f;
	Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;

	  if (keyboard->isKeyDown(OIS::KC_LSHIFT))
	  {
		move = 200.0f;
		rotate = 0.2f;
	  }

	  if (keyboard->isKeyDown(OIS::KC_W))
	    dirVec.z -= move;

	  if (keyboard->isKeyDown(OIS::KC_S))
	    dirVec.z += move;

	  if (keyboard->isKeyDown(OIS::KC_R))
	    dirVec.y += move;

	  if (keyboard->isKeyDown(OIS::KC_F) && engine->gfxMgr->cameraNode->getPosition().y > 25)
	      dirVec.y -= move;

	  if (keyboard->isKeyDown(OIS::KC_A))
	    dirVec.x -= move;

	  if (keyboard->isKeyDown(OIS::KC_D))
	    dirVec.x += move;

	  if (keyboard->isKeyDown(OIS::KC_Q))
		engine->gfxMgr->cameraNode->yaw(Ogre::Degree(.5 * rotate));

	  if (keyboard->isKeyDown(OIS::KC_E))
		engine->gfxMgr->cameraNode->yaw(Ogre::Degree(-.5 * rotate));

	  if (keyboard->isKeyDown(OIS::KC_Z))
		engine->gfxMgr->cameraNode->pitch(Ogre::Degree(.5 * rotate));

	  if (keyboard->isKeyDown(OIS::KC_X))
		engine->gfxMgr->cameraNode->pitch(Ogre::Degree(-.5 * rotate));

	  if(keyboard->isKeyDown(OIS::KC_P))
		cameraView = !cameraView;

	  if (cameraView)
	  {
		  engine->gfxMgr->cameraNode->setPosition(engine->entityMgr->selectedEntity->pos + Ogre::Vector3(0, 500, 500));
		  engine->gfxMgr->ogreCamera->lookAt(engine->entityMgr->selectedEntity->pos);
	  }

	  engine->gfxMgr->cameraNode->translate(dirVec * dt, Ogre::Node::TS_LOCAL);
}

void InputMgr::UpdateDesiredSpeedHeading(float dt)
{
	keyboardTimer -= dt;

	if(engine->entityMgr->selectedEntity)
	{
		if((keyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_NUMPAD8))
		{
			keyboardTimer = keyTime;
			engine->entityMgr->selectedEntity->desiredSpeed += 10;
		}
		if((keyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_NUMPAD2))
		{
			keyboardTimer = keyTime;
			engine->entityMgr->selectedEntity->desiredSpeed -= 10;
		}

		engine->entityMgr->selectedEntity->desiredSpeed = std::max(engine->entityMgr->selectedEntity->minSpeed, std::min(engine->entityMgr->selectedEntity->maxSpeed, engine->entityMgr->selectedEntity->desiredSpeed));

		if((keyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_NUMPAD4))
		{
			keyboardTimer = keyTime;
			engine->entityMgr->selectedEntity->desiredHeading -= 0.3f;
		}

		if((keyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_NUMPAD6))
		{
			keyboardTimer = keyTime;
			engine->entityMgr->selectedEntity->desiredHeading += 0.3f;
		}
	}
}

void InputMgr::UpdateSelection(float dt)
{
	selectionTimer -= dt;
	if(selectionTimer < 0 && keyboard->isKeyDown(OIS::KC_TAB))
	{
		selectionTimer = this->selectionTime;
		engine->entityMgr->SelectNextEntity();
	}
}




