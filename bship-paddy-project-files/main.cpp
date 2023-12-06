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
void initGameWorld(osgViewer::Viewer &viewer, const char* luaScriptPath) {
    World *world = World::instance();
    viewer.setSceneData(world->getSceneGraph());
    osg::ref_ptr<Ship> ship = Ship::create();
    world->addEntity(ship.get());

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L, "addBarrier", lua_addBarrier);

    if (luaL_dofile(L, luaScriptPath) != LUA_OK) {
        std::cerr << "Error running Lua script: " << lua_tostring(L, -1) << std::endl;
    }

    lua_close(L);
    viewer.addEventHandler(new ShipController(ship.get()));
}


static int lua_addBarrier(lua_State* L) {
    // Ensure there are exactly 6 arguments
    if (lua_gettop(L) != 6) {
        luaL_error(L, "Incorrect number of arguments to addBarrier");
    }

    float hx = luaL_checknumber(L, 1);
    float hy = luaL_checknumber(L, 2);
    float hz = luaL_checknumber(L, 3);
    float ox = luaL_checknumber(L, 4);
    float oy = luaL_checknumber(L, 5);
    float oz = luaL_checknumber(L, 6);

    World::instance()->addBarrier(hx, hy, hz, ox, oy, oz);

    return 0; // Number of return values
}

/**
 * MAIN
 */
int main(int argc, char *argv[]) {
    osgViewer::Viewer viewer;
    initViewer(viewer);

    // Check if the Lua script filename is provided
    if (argc > 1) {
        initGameWorld(viewer, argv[1]);
    } else {
        std::cerr << "Lua script filename not provided." << std::endl;
        return 1;
    }

    return viewer.run();
}


/* vi:set tw=78 sw=4 ts=4 et: */


