/** file: springmass.h
 ** brief: SpringMass simulation
 ** author: Andrea Vedaldi
 **/

#ifndef __springmass__
#define __springmass__

#include "simulation.h"

#include <cmath>
#include <vector>

#define MOON_GRAVITY 1.62
#define EARTH_GRAVITY 9.82

/* ---------------------------------------------------------------- */
// class Vector2
/* ---------------------------------------------------------------- */

class Vector2
{
public:
  double x ;
  double y ;

  Vector2() : x(0), y(0) { }
  Vector2(double _x, double _y) : x(_x), y(_y) { }
  double norm2() const { return x*x + y*y ; }
  double norm() const { return std::sqrt(norm2()) ; }
} ;

inline Vector2 operator+ (Vector2 a, Vector2 b) { return Vector2(a.x+b.x, a.y+b.y) ; }
inline Vector2 operator- (Vector2 a, Vector2 b) { return Vector2(a.x-b.x, a.y-b.y) ; }
inline Vector2 operator* (double a, Vector2 b)  { return Vector2(a*b.x, a*b.y) ; }
inline Vector2 operator* (Vector2 a, double b)  { return Vector2(a.x*b, a.y*b) ; }
inline Vector2 operator/ (Vector2 a, double b)  { return Vector2(a.x/b, a.y/b) ; }
inline double dot(Vector2 a, Vector2 b) { return a.x*b.x + a.y*b.y ; }

/* ---------------------------------------------------------------- */
// class Vector3
/* ---------------------------------------------------------------- */

class Vector3
{
public:
    double x, y, z;

    Vector3() : x(0), y(0), z(0) { }
    Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) { }
    double norm2() const { return x*x + y*y + z*z; }
    double norm() const { return std::sqrt(norm2()); }
};

inline Vector3 operator+ (Vector3 a, Vector3 b) { return Vector3(a.x+b.x, a.y+b.y, a.z+b.z); }
inline Vector3 operator- (Vector3 a, Vector3 b) { return Vector3(a.x-b.x, a.y-b.y, a.z-b.z); }
inline Vector3 operator* (double a, Vector3 b) { return Vector3(a*b.x, a*b.y, a*b.z); }
inline Vector3 operator* (Vector3 a, double b) { return Vector3(a.x*b, a.y*b, a.z*b); }
inline Vector3 operator/ (Vector3 a, double b) { return Vector3(a.x/b, a.y/b, a.z/b); }
inline double dot(Vector3 a, Vector3 b) { return a.x*b.x + a.y*b.y + a.z*b.z; }

/* ---------------------------------------------------------------- */
// class Mass
/* ---------------------------------------------------------------- */

class Mass
{
public:
  Mass() ;
  Mass(Vector3 position, Vector3 velocity, double mass, double radius) ;
  void setForce(Vector3 f) ;
  void addForce(Vector3 f) ;
  Vector3 getForce() const ;
  Vector3 getPosition() const ;
  Vector3 getVelocity() const ;
  double getMass() const ;
  double getRadius() const ;
  double getEnergy(double gravity) const ;
  void step(double dt) ;

protected:
  Vector3 position ;
  Vector3 velocity ;
  Vector3 force ;
  double mass ;
  double radius ;

  double xmin ;
  double xmax ;
  double ymin ;
  double ymax ;
  double zmin ;
  double zmax ;
} ;

/* ---------------------------------------------------------------- */
// class Spring
/* ---------------------------------------------------------------- */

class Spring
{
public:
  Spring(Mass* mass1, Mass* mass2, double naturalLength, double stiffness, double damping = 0.01);
  
  Mass* getMass1() const { return mass1; }
  Mass* getMass2() const { return mass2; }
  Vector3 getForce() const;
  double getLength() const;
  double getEnergy() const;
  
protected:
  Mass* mass1;
  Mass* mass2;
  double naturalLength;
  double stiffness;
  double damping;
} ;

/* ---------------------------------------------------------------- */
// class SpringMass : public Simulation
/* ---------------------------------------------------------------- */

class SpringMass : public Simulation
{
public:
  SpringMass(double gravity = MOON_GRAVITY) ;
  
  // Add methods to setup simulation
  void addMass(Mass* mass);
  void addSpring(Spring* spring);
  
  // Required by Simulation interface
  void step(double dt) ;
  void display() ;
  double getEnergy() const ;

protected:
  double gravity ;
  std::vector<Mass*> masses;     // Store n masses
  std::vector<Spring*> springs;   // Store m springs
  Vector3 g;  // Gravity vector (0, -g, 0)
} ;

#endif /* defined(__springmass__) */

