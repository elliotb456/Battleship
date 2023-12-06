/*
 * CS4085: Skeleton for lab assignment.
 *
 * Copyright (C) 2008 Jacek Rosik <jacek.rosik@ul.ie>
 */


#ifndef __SHIP_H__
#define __SHIP_H__ 


#include <string>

#include "entity.h"


/**
 * Class representing the space ship.
 */
class Ship: public Entity {

public:
    enum Engine {
        LEFT_ENGINE     = 0,
        TOP_ENGINE      = 1,
        RIGHT_ENGINE    = 2,
        BOTTOM_ENGINE   = 3,
    };

public:
    virtual ~Ship(void) {}

    static Ship *create(void);

    void activateEngine(Engine engine, bool activate);

    void translate(const osg::Vec3 trans);
    void rotate(double angle);

    const osg::Vec3 getPosition(void) const;
    double getOrientation(void) const;


protected:
    Ship(osg::MatrixTransform *visual);

    virtual void onUpdate(double time);

private:
    double _lastFrame;
    bool _engines[4];

    double _power;
    osg::Vec3 _velocity;
};

void setDirection(float angle);
void updateVelocity();

private:
    float _angle;  // Direction angle of the ship in radians
    float _speed;  // Speed of the ship
};

void increaseSpeed();
void decreaseSpeed();

private:
    float _maxSpeed;  // Maximum speed of the ship
    float _acceleration;  // Acceleration rate of the ship
};



void checkAndWrapEdges();

private:
    static constexpr float LEFT_EDGE = -50.0;  // Adjust based on your screen/world size
    static constexpr float RIGHT_EDGE = 50.0;
    static constexpr float TOP_EDGE = 50.0;
    static constexpr float BOTTOM_EDGE = -50.0;
};


private:
    float _maxSpeed;  // Maximum allowed speed of the ship
    // ... other members ...
};

#endif /* __SHIP_H__ */


/* vi:set tw=78 sw=4 ts=4 et: */
