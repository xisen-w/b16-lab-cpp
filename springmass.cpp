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
: position(), velocity(), force(), mass(1), radius(1),
  xmin(-1), xmax(1), ymin(-1), ymax(1), zmin(-1), zmax(1)
{ }

Mass::Mass(Vector3 position, Vector3 velocity, double mass, double radius)
: position(position), velocity(velocity), force(), mass(mass), radius(radius),
  xmin(-1), xmax(1), ymin(-1), ymax(1), zmin(-1), zmax(1)
{ }

void Mass::setForce(Vector3 f)
{
  force = f ;
}

void Mass::addForce(Vector3 f)
{
  force = force + f ;
}

Vector3 Mass::getForce() const
{
  return force ;
}

Vector3 Mass::getPosition() const
{
  return position ;
}

Vector3 Mass::getVelocity() const
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

double Mass::getEnergy(double gravity) const {
    double energy = 0;
    
    // Kinetic energy: 1/2 * m * v^2
    energy = 0.5 * mass * velocity.norm2();
    
    // Potential energy: m * g * h
    energy += mass * gravity * (position.y + 1);  // This is fine
    
    return energy;
}

void Mass::step(double dt)
{
    velocity = velocity + (force / mass) * dt;
    Vector3 newPosition = position + velocity * dt;
    
    // Check boundaries and handle collisions for all dimensions
    if (newPosition.x >= xmin + radius && newPosition.x <= xmax - radius) {
        position.x = newPosition.x;
    } else {
        velocity.x = -velocity.x;
    }
    
    if (newPosition.y >= ymin + radius && newPosition.y <= ymax - radius) {
        position.y = newPosition.y;
    } else {
        velocity.y = -velocity.y;
    }
    
    if (newPosition.z >= zmin + radius && newPosition.z <= zmax - radius) {
        position.z = newPosition.z;
    } else {
        velocity.z = -velocity.z;
    }
    
    force = Vector3(0, 0, 0);
}

/* ---------------------------------------------------------------- */
// class Spring
/* ---------------------------------------------------------------- */

Spring::Spring(Mass * mass1, Mass * mass2, double naturalLength, double stiffness, double damping)
: mass1(mass1), mass2(mass2),
naturalLength(naturalLength), stiffness(stiffness), damping(damping)
{ }

Vector3 Spring::getForce() const
{
  // Get positions and velocities
  Vector3 x1 = mass1->getPosition();
  Vector3 x2 = mass2->getPosition();
  Vector3 v1 = mass1->getVelocity();
  Vector3 v2 = mass2->getVelocity();
  
  // Calculate current length and unit vector
  Vector3 displacement = x2 - x1;  // (x2 - x1)
  double l = displacement.norm();   // l = ||x2 - x1||
  Vector3 u12 = displacement / l;   // u12 = (x2 - x1)/l
  
  // Calculate spring force: F1 = k(l - l0)u12
  Vector3 springForce = stiffness * (l - naturalLength) * u12;
  
  // Calculate damping force: F1 = d*v12, where v12 = ((v2-v1)·u12)u12
  Vector3 relativeVelocity = v2 - v1;
  double projectedVelocity = dot(relativeVelocity, u12);
  Vector3 dampingForce = damping * projectedVelocity * u12;
  
  // Total force is sum of spring force and damping force
  return springForce + dampingForce;
}

double Spring::getLength() const
{
  Vector3 u = mass2->getPosition() - mass1->getPosition() ;
  return u.norm() ;
}

double Spring::getEnergy() const {
    double length = getLength();
    double dl = length - naturalLength;
    return 0.5 * stiffness * dl * dl;  // This is correct
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
    Vector3 g(0, -gravity, 0);
    
    // Set initial gravitational force on all masses
    for(size_t i = 0; i < masses.size(); ++i) {
        Vector3 gravityForce = g * masses[i]->getMass();
        masses[i]->setForce(gravityForce);
    }
    
    // Add spring forces to connected masses
    for(Spring* spring : springs) {
        Vector3 f1 = spring->getForce();
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
    // Output format: x1 y1 x2 y2 spring_length
    for(size_t i = 0; i < masses.size(); ++i) {
        Vector3 pos = masses[i]->getPosition();
        std::cout << pos.x << " " << pos.y << " " << pos.z;
        if(i < masses.size() - 1) std::cout << " ";
    }
    
    for(Spring* spring : springs) {
        std::cout << " " << spring->getLength();
    }
    std::cout << std::endl;
}

double SpringMass::getEnergy() const {
    double energy = 0;
    
    // Sum energy of all masses
    for(Mass* mass : masses) {
        energy += mass->getEnergy(gravity);
    }
    
    // Add spring potential energy
    for(Spring* spring : springs) {
        energy += spring->getEnergy();
    }
    
    return energy;
}


