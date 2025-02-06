/** file: springmass.cpp
 ** brief: SpringMass simulation implementation
 ** author: Andrea Vedaldi
 **/

#include "springmass.h"

#include <iostream>

/* ---------------------------------------------------------------- */
// class Mass
/* ---------------------------------------------------------------- */

Mass::Mass()
: position(), velocity(), force(), mass(1), radius(1)
{ }

Mass::Mass(Vector2 position, Vector2 velocity, double mass, double radius)
: position(position), velocity(velocity), force(), mass(mass), radius(radius),
xmin(-1),xmax(1),ymin(-1),ymax(1)
{ }

void Mass::setForce(Vector2 f)
{
  force = f ;
}

void Mass::addForce(Vector2 f)
{
  force = force + f ;
}

Vector2 Mass::getForce() const
{
  return force ;
}

Vector2 Mass::getPosition() const
{
  return position ;
}

Vector2 Mass::getVelocity() const
{
  return velocity ;
}

double Mass::getRadius() const
{
  return radius ;
}

double Mass::getMass() const
{
  return mass ;
}

double Mass::getEnergy(double gravity) const
{
    double energy = 0;
    
    // Kinetic energy: 1/2 * m * v^2
    energy += 0.5 * mass * velocity.norm2();
    
    // Potential energy: m * g * h
    // Note: y-coordinate represents height, and y=0 is the reference level
    energy += mass * gravity * position.y;
    
    return energy;
}

void Mass::step(double dt)
{
    // Update position using current velocity
    Vector2 newPosition = position + velocity * dt;
    
    // Check boundaries and handle collisions
    if (newPosition.x >= xmin + radius && newPosition.x <= xmax - radius) {
        position.x = newPosition.x;
    } else {
        velocity.x = -velocity.x; // Elastic collision with walls
    }
    
    if (newPosition.y >= ymin + radius && newPosition.y <= ymax - radius) {
        position.y = newPosition.y;
    } else {
        velocity.y = -velocity.y; // Elastic collision with floor/ceiling
    }
    
    // Update velocity using F = ma -> a = F/m
    // v = v0 + at -> v = v0 + (F/m)t
    velocity = velocity + (force / mass) * dt;
    
    // Reset force for next step
    force = Vector2(0, 0);
}

/* ---------------------------------------------------------------- */
// class Spring
/* ---------------------------------------------------------------- */

Spring::Spring(Mass * mass1, Mass * mass2, double naturalLength, double stiffness, double damping)
: mass1(mass1), mass2(mass2),
naturalLength(naturalLength), stiffness(stiffness), damping(damping)
{ }

Mass * Spring::getMass1() const
{
  return mass1 ;
}

Mass * Spring::getMass2() const
{
  return mass2 ;
}

Vector2 Spring::getForce() const
{
  // Get positions and velocities
  Vector2 x1 = mass1->getPosition();
  Vector2 x2 = mass2->getPosition();
  Vector2 v1 = mass1->getVelocity();
  Vector2 v2 = mass2->getVelocity();
  
  // Calculate current length and unit vector
  Vector2 displacement = x2 - x1;  // (x2 - x1)
  double l = displacement.norm();   // l = ||x2 - x1||
  Vector2 u12 = displacement / l;   // u12 = (x2 - x1)/l
  
  // Calculate spring force: F1 = k(l - l0)u12
  Vector2 springForce = stiffness * (l - naturalLength) * u12;
  
  // Calculate damping force: F1 = d*v12, where v12 = ((v2-v1)·u12)u12
  Vector2 relativeVelocity = v2 - v1;
  double projectedVelocity = dot(relativeVelocity, u12);
  Vector2 dampingForce = damping * projectedVelocity * u12;
  
  // Total force is sum of spring force and damping force
  return springForce + dampingForce;
}

double Spring::getLength() const
{
  Vector2 u = mass2->getPosition() - mass1->getPosition() ;
  return u.norm() ;
}

double Spring::getEnergy() const {
  double length = getLength() ;
  double dl = length - naturalLength;
  return 0.5 * stiffness * dl * dl ;
}

std::ostream& operator << (std::ostream& os, const Mass& m)
{
  os<<"("
  <<m.getPosition().x<<","
  <<m.getPosition().y<<")" ;
  return os ;
}

std::ostream& operator << (std::ostream& os, const Spring& s)
{
  return os<<"$"<<s.getLength() ;
}

/* ---------------------------------------------------------------- */
// class SpringMass : public Simulation
/* ---------------------------------------------------------------- */

SpringMass::SpringMass(double gravity)
: gravity(gravity)
{ }

void SpringMass::addMass(Mass* mass) {
    masses.push_back(mass);
}

void SpringMass::addSpring(Spring* spring) {
    springs.push_back(spring);
}

void SpringMass::step(double dt) {
    Vector2 g(0, -gravity);
    
    // Set initial gravitational force on all masses
    for(Mass* mass : masses) {
        Vector2 gravityForce = g * mass->getMass();
        mass->setForce(gravityForce);
    }
    
    // Add spring forces to connected masses
    for(Spring* spring : springs) {
        Vector2 f1 = spring->getForce();
        Mass* m1 = spring->getMass1();
        Mass* m2 = spring->getMass2();
        
        m1->addForce(f1);        // Add F1 to mass1
        m2->addForce(-1 * f1);   // Add -F1 (F2) to mass2
    }
    
    // Update all masses
    for(Mass* mass : masses) {
        mass->step(dt);
    }
}

void SpringMass::display() {
    // Display all mass positions
    for(Mass* mass : masses) {
        std::cout << *mass << " ";
    }
    // Display all spring lengths
    for(Spring* spring : springs) {
        std::cout << *spring << " ";
    }
    std::cout << std::endl;
}

double SpringMass::getEnergy() const {
    double energy = 0;
    
    // Sum energy of all masses (kinetic + potential)
    for(Mass* mass : masses) {
        energy += mass->getEnergy(gravity);
    }
    
    // Add potential energy of all springs
    for(Spring* spring : springs) {
        energy += spring->getEnergy();
    }
    
    return energy;
}


