/*
 * CS4085: Skeleton for lab assignment.
 *
 * Copyright (C) 2008 Jacek Rosik <jacek.rosik@ul.ie>
 */


#include <cassert>
#include <cmath>

#include <osg/Geode>
#include <osg/Quat>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>

#include "ship.h"


Ship::Ship(osg::MatrixTransform *visual):
    Entity(visual), _lastFrame(0.0),
    _power(1.0), _velocity(0.0, 0.0, 0.0)
{
    /* All engines initially disabled.  */
    _engines[0] = false; 
    _engines[1] = false; 
    _engines[2] = false; 
    _engines[3] = false; 
}


Ship 
* Ship::create() {
    osg::ref_ptr<osg::MatrixTransform> visual = new osg::MatrixTransform();

    // Create a cone to represent the ship
    osg::ref_ptr<osg::Cone> cone = new osg::Cone(osg::Vec3(0.0, 0.0, 0.0), 1.0, 2.0);  // Adjust size as needed
    osg::ref_ptr<osg::ShapeDrawable> coneDrawable = new osg::ShapeDrawable(cone);
    
    // Set color and material properties if needed
    osg::ref_ptr<osg::Material> material = new osg::Material;
    material->setDiffuse(osg::Material::FRONT, osg::Vec4(0.6, 0.6, 0.6, 1.0));  // Grey color
    coneDrawable->getOrCreateStateSet()->setAttribute(material);

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    geode->addDrawable(coneDrawable.get());
    visual->addChild(geode.get());

    return new Ship(visual.get());
}


void
Ship::activateEngine(Engine engine, bool activate)
{
    /* Enable/Disable given engine.  */
    assert(engine >= LEFT_ENGINE && engine <= BOTTOM_ENGINE);
    _engines[engine] = activate;
}


void
Ship::translate(const osg::Vec3 translation)
{
    osg::Matrix matrix;
    matrix.makeTranslate(translation);
    _visual->postMult(matrix);
}


void
Ship::rotate(double angle)
{
    osg::Matrix matrix;
    matrix.makeRotate(angle, osg::Vec3(0.0, 0.0, 1.0));
    _visual->postMult(matrix);
}

const osg::Vec3
Ship::getPosition(void) const
{
    osg::Vec3 trans, vdummy;
    osg::Quat qdummy;
    _visual->getMatrix().decompose(trans, qdummy, vdummy, qdummy);

    return trans;
}


double
Ship::getOrientation(void) const
{
    double angle;
    osg::Vec3 vdummy;
    osg::Quat rot, qdummy;
    _visual->getMatrix().decompose(vdummy, rot, vdummy, qdummy);
    rot.getRotate(angle, vdummy);

    return angle;
}



void
Ship::onUpdate(double time)
{
    double delta = time - _lastFrame;
    _lastFrame = time;

    /* Get the force vector first.  */
    osg::Vec3 force(0.0, 0.0, 0.0);
    if (_engines[LEFT_ENGINE])
        force += osg::Vec3(1.0, 0.0, 0.0);
    if (_engines[TOP_ENGINE])
        force += osg::Vec3(0.0, -1.0, 0.0);
    if (_engines[RIGHT_ENGINE])
        force += osg::Vec3(-1.0, 0.0, 0.0);
    if (_engines[BOTTOM_ENGINE])
        force += osg::Vec3(0.0, 1.0, 0.0);
    force *= _power;

    /* Update ship's position.  */
    translate(_velocity * delta);

    /* Caluclate ship's new velocity.  */
    _velocity += force * delta;
    //printf("VELOCITY: %f %f %f\n", _velocity[0], _velocity[1], _velocity[2]);
}


/* vi:set tw=78 sw=4 ts=4 et: */

void Ship::setDirection(float angle) {
    _angle = angle;
    updateVelocity();
}

void Ship::updateVelocity() {
    // Update velocity based on the current angle and speed
    _velocity.set(cos(_angle) * _speed, sin(_angle) * _speed, 0.0);
}

// Modify the onUpdate method to use the new velocity
void Ship::onUpdate(double time) {
    double delta = time - _lastFrame;
    _lastFrame = time;

    // Update ship's position based on the new velocity
    translate(_velocity * delta);
}

void Ship::increaseSpeed() {
    _speed = std::min(_speed + _acceleration, _maxSpeed);
    updateVelocity();
}

void Ship::decreaseSpeed() {
    _speed = std::max(_speed - _acceleration, 0.0f);
    updateVelocity();
}



void Ship::checkAndWrapEdges() {
    osg::Vec3 position = getPosition();

    if (position.x() < LEFT_EDGE) {
        position.x() = RIGHT_EDGE;
    } else if (position.x() > RIGHT_EDGE) {
        position.x() = LEFT_EDGE;
    }

    if (position.y() < BOTTOM_EDGE) {
        position.y() = TOP_EDGE;
    } else if (position.y() > TOP_EDGE) {
        position.y() = BOTTOM_EDGE;
    }

    // Update the ship's position
    setPosition(position);
}

// Update the setPosition method or create it if it doesn't exist
void Ship::setPosition(const osg::Vec3& position) {
    // This should set the visual node's position to the specified value
    // The implementation depends on how you're handling transformations
    _visual->setPosition(position);
}

// Modify the onUpdate method to call checkAndWrapEdges
void Ship::onUpdate(double time) {
    double delta = time - _lastFrame;
    _lastFrame = time;

    // Update ship's position based on velocity
    translate(_velocity * delta);

    // Check and handle edge wrapping
    checkAndWrapEdges();
}


void Ship::increaseSpeed() {
    _speed = std::min(_speed + _acceleration, _maxSpeed);
    updateVelocity();
}

void Ship::decreaseSpeed() {
    _speed = std::max(_speed - _acceleration, 0.0f);
    updateVelocity();
}

void Ship::updateVelocity() {
    // Ensure that speed does not exceed the maximum limit
    _speed = std::min(_speed, _maxSpeed);

    // Update velocity based on the current angle and speed
    _velocity.set(cos(_angle) * _speed, sin(_angle) * _speed, 0.0);
}

