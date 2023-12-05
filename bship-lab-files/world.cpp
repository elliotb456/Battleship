/*
 * CS4085: Skeleton for lab assignment.
 *
 * Copyright (C) 2008 Jacek Rosik <jacek.rosik@ul.ie>
 */


#include <osg/Group>

#include "entity.h"

#include "world.h"


World::World(void):
    _root(new osg::Group())
{
}


World::~World(void)
{
}


/**
 * Add entity to the world.
 *
 * The world teakes the ownership of the entity and is responsible for
 * destroying it.
 */
void
World::addEntity(Entity *entity)
{
    _entities.push_back(entity);

    /* Add the visual representation to the scene graph.  */
    _root->addChild(entity->getVisual());
}


/* vi:set tw=78 sw=4 ts=4 et: */
