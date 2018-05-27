/*
 * GfxMgr.cpp
 *
 *  Created on: Mar 26, 2017
 *      Authors: Stefan Stukelja and Alex Crupi
 *      For: CS 381 - Assignment 3
 */

#include "GfxMgr.h"
#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreException.h>

GfxMgr::GfxMgr(Engine *eng)
	: Mgr(eng),
	  mRoot(0),
	  mResourcesCfg(Ogre::StringUtil::BLANK),
	  mPluginsCfg(Ogre::StringUtil::BLANK),
	  mWindow(0),
	  mSceneMgr(0),
	  mCamera(0)
{
	engine = eng;
}

GfxMgr::~GfxMgr()
{
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);

	delete mRoot;
}

void GfxMgr::tick(float dt)
{
	Ogre::WindowEventUtilities::messagePump();
	mRoot->renderOneFrame();
}

void GfxMgr::init()
{
	this->go();
}

void GfxMgr::loadLevel()
{

}

void GfxMgr::stop()
{

}

bool GfxMgr::go()
{
#ifdef _DEBUG
  mResourcesCfg = "resources_d.cfg";
  mPluginsCfg = "plugins_d.cfg";
#else
  mResourcesCfg = "resources.cfg";
  mPluginsCfg = "plugins.cfg";
#endif

  mRoot = new Ogre::Root(mPluginsCfg);

  Ogre::ConfigFile cf;
  cf.load(mResourcesCfg);

  Ogre::String name, locType;
  Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();

  while (secIt.hasMoreElements())
  {
    Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator it;

    for (it = settings->begin(); it != settings->end(); ++it)
    {
      locType = it->first;
      name = it->second;

      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
    }
  }

  if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
    return false;

  mWindow = mRoot->initialise(true, "Assignment 3");

  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

  mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

  mCamera = mSceneMgr->createCamera("MainCam");
  mCamera->setPosition(400, 250, 800);
  mCamera->lookAt(400, 0, 0);
  mCamera->setNearClipDistance(5);

  Ogre::Viewport* vp = mWindow->addViewport(mCamera);
  vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

  mCamera->setAspectRatio(
    Ogre::Real(vp->getActualWidth()) /
    Ogre::Real(vp->getActualHeight()));

  mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

  Ogre::Light* light = mSceneMgr->createLight("MainLight");
  light->setPosition(20, 80, 50);

  return true;
}
