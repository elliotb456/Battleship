/*
 * CS4085: Skeleton for lab assignment.
 *
 * Copyright (C) 2008 Jacek Rosik <jacek.rosik@ul.ie>
 */

extern "C" {
#include "lualib.h"
#include "lauxlib.h"
}

#include <cstdlib>

#include <osg/Group>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include "ship.h"
#include "shipcontroller.h"
#include "world.h"


#define WINDOW_SIZE                     512

#define WORLD_SIZE                      100.0

/**
 * Initialise the display window camera and projections.
 */
void
initViewer(osgViewer::Viewer &viewer)
{
    /* This will set up a square window (app runs fullscreen by default).  */
    viewer.setUpViewInWindow(0, 0, WINDOW_SIZE, WINDOW_SIZE);

    /* This will create rendering context windows camreras etc... */
    viewer.realize();
    
    /* Set up the camera that it is showing the whole world and does not
     * react to window resizes. The camera is looking at XY plane from above.  */
    osg::ref_ptr<osg::Camera> camera =  viewer.getCamera();
    camera->setProjectionResizePolicy(osg::Camera::FIXED);
    camera->setProjectionMatrixAsOrtho2D(-0.5 * WORLD_SIZE, 0.5 * WORLD_SIZE,
                                         -0.5 * WORLD_SIZE, 0.5 * WORLD_SIZE);
    camera->setViewMatrixAsLookAt(osg::Vec3(0.0, 0.0, 0.0),
                                  osg::Vec3(0.0, 0.0, -1.0),
                                  osg::Vec3(0.0, 1.0, 0.0));
    /* This will disable the manipulator which is useless for us.  */
    camera->setAllowEventFocus(false);
}

/**
 * Create the game world and underlying scene graph.
 */
void
initGameWorld(osgViewer::Viewer &viewer)
{
  World *world = World::instance();

  /* Attach the scene graph to viewer.  */
  viewer.setSceneData(world->getSceneGraph());

  /* Add our space ship to the world.  */
  osg::ref_ptr<Ship> ship = Ship::create();
  world->addEntity(ship.get());

  // very good advice here:
  //http://rubenlaguna.com/wp/2012/11/26/first-steps-lua-cplusplus-integration/

  lua_State *L = luaL_newstate();

  //  addBarrier() call below is for demo purposes only
  //  DELETE next line before handin
  world->addBarrier(30.0f, 3.0f, 0.0f, -10.0f, -25.0f, 0.0f);  // DELETE ME!!

  lua_close(L);

  /* Set up keboard event handler to controll the ship.  */
  viewer.addEventHandler(new ShipController(ship.get()));
}


/**
 * MAIN
 */
int
main(int argc, char *argv[])
{
  /* Create and initialise the viewer.  */
  osgViewer::Viewer viewer;
  initViewer(viewer);

  /* Create the scene.  */
  initGameWorld(viewer);

  /* Enter the event processing loop.  */
  return  viewer.run();
}


/* vi:set tw=78 sw=4 ts=4 et: */
