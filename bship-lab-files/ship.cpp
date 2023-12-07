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

const double WORLDSIZE = 100;

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


Ship * Ship::create() {
    osg::ref_ptr<osg::MatrixTransform> visual = new osg::MatrixTransform();

    // Create a shape to represent the ship
    osg::ref_ptr<osg::Shape> shape = new osg::Box(osg::Vec3(0.0, 0.0, 0.0), 2.0, 2.0, 2.0);  // Adjust size as needed
    //osg::ref_ptr<osg::ShapeDrawable> coneDrawable = new osg::ShapeDrawable(cone);
    
    
    // Set color and material properties if needed
    //osg::ref_ptr<osg::Material> material = new osg::Material;
    //material->setDiffuse(osg::Material::FRONT, osg::Vec4(0, 1, 0, 1.0));  // Grey color
    //coneDrawable->getOrCreateStateSet()->setAttribute(material);
    

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    geode->addDrawable(new osg::ShapeDrawable(shape.get()));
    visual->addChild(geode.get());

    return new Ship(visual.get());
}
void Ship::activateEngine(Engine engine, bool activate)
{
    /* Enable/Disable given engine.  */
    assert(engine >= LEFT_ENGINE && engine <= BOTTOM_ENGINE);
    _engines[engine] = activate;
}

void Ship::translate(const osg::Vec3 translation)
{
    osg::Matrix matrix;
    matrix.makeTranslate(translation);
    _visual->postMult(matrix);
}

void Ship::rotate(double angle)
{
    osg::Matrix matrix;
    matrix.makeRotate(angle, osg::Vec3(0.0, 0.0, 1.0));
    _visual->postMult(matrix);
}

const osg::Vec3 Ship::getPosition(void) const
{
    osg::Vec3 trans, vdummy;
    osg::Quat qdummy;
    _visual->getMatrix().decompose(trans, qdummy, vdummy, qdummy);

    return trans;
}

double Ship::getOrientation(void) const
{
    double angle;
    osg::Vec3 vdummy;
    osg::Quat rot, qdummy;
    _visual->getMatrix().decompose(vdummy, rot, vdummy, qdummy);
    rot.getRotate(angle, vdummy);

    return angle;
}

void Ship::increaseSpeed() {
	_power += 1;
	if (_power > 10.0) {
		_power = 10.0;
	}
}

void Ship::decreaseSpeed() {
	_power -= 1;
	if (_power < 1.0) {
		_power = 1.0;
	}
}

void Ship::onUpdate(double time)
{
    double delta = time - _lastFrame;
    _lastFrame = time;

    /* Get the force vector first.  */
    osg::Vec3 force(0.0, 0.0, 0.0);
    if (_engines[LEFT_ENGINE])
        force += osg::Vec3(10.0, 0.0, 0.0);
    if (_engines[TOP_ENGINE])
        force += osg::Vec3(0.0, -10.0, 0.0);
    if (_engines[RIGHT_ENGINE])
        force += osg::Vec3(-10.0, 0.0, 0.0);
    if (_engines[BOTTOM_ENGINE])
        force += osg::Vec3(0.0, 10.0, 0.0);
    force *= _power;

    /* Update ship's position.  */
    translate(_velocity * delta);

    /* Caluclate ship's new velocity.  */
    _velocity += force * delta;
    
    // Setting the maximum velocity
	const double MAXVELOCITY = 50;
		if (_velocity.length() > MAXVELOCITY) {
			_velocity.normalize();
			_velocity *= MAXVELOCITY;
		}

    // Debugging statments | Can be commented out 
    printf("VELOCITY: %f %f\n", _velocity[0], _velocity[1]);
    printf("Speed: %f\n", _power);
    
    
    // Change varibale names 
    // Wrapping the ship around the worlds edges
    osg::Vec3 position = getPosition();
    double worldHalfSize = WORLDSIZE / 2.0;
    
    if (position.x() < -worldHalfSize) 
    {
    	position.x() += WORLDSIZE;
    	_visual->setMatrix(osg::Matrix::translate(position));
    } 
    if (position.x() > worldHalfSize) 
    {
    	position.x() -= WORLDSIZE;
    	_visual->setMatrix(osg::Matrix::translate(position));
    } 
    if (position.y() < -worldHalfSize) 
    {
    	position.y() += WORLDSIZE;
    	_visual->setMatrix(osg::Matrix::translate(position));
    } 
    if (position.y() > worldHalfSize) 
    {
    	position.y() -= WORLDSIZE;
    	_visual->setMatrix(osg::Matrix::translate(position));
    } 
    
} // end onUpdate

/* vi:set tw=78 sw=4 ts=4 et: */





