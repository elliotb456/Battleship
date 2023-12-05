/*
 * CS4085: Skeleton for lab assignment.
 *
 * Copyright (C) 2008 Jacek Rosik <jacek.rosik@ul.ie>
 */


#ifndef __WORLD_H__
#define __WORLD_H__ 


#include <vector>

#include <osg/ref_ptr>

#include "singleton.h"


namespace osg {
    class Node;
    class Group;
}

class Entity;


/**
 * Class representing game world.
 */
class World: public Singleton<World> {

    typedef std::vector<osg::ref_ptr<Entity> > Entities;

public:
    World(void);
    virtual ~World(void);

    osg::Node *getSceneGraph(void)
        { return _root.get(); }

    void addEntity(Entity *entity);

private:
    osg::ref_ptr<osg::Group> _root;
    Entities _entities;
};


#endif /* __WORLD_H__ */


/* vi:set tw=78 sw=4 ts=4 et: */
