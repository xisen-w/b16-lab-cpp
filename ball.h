/** file: ball.h
 ** brief: Ball class
 ** author: Andrea Vedaldi
 **/

#ifndef __ball__
#define __ball__

#include "simulation.h"

class Ball : public Simulation
{
public:
  // Default constructor
  Ball() ;
  
  // Custom constructor with initial position and velocity
  Ball(double initialX, double initialY, double initialVx, double initialVy) ;

  // Member functions
  void step(double dt) ;
  void display() ;

  // Add these getter/setter methods
  double getX() const { return x; }
  double getY() const { return y; }
  void setPosition(double newX, double newY) {
    // Add bounds checking
    if (newX >= xmin + r && newX <= xmax - r) x = newX;
    if (newY >= ymin + r && newY <= ymax - r) y = newY;
  }

protected:
  // Data members
  // Position and velocity of the ball
  double x ;
  double y ;
  double vx ;
  double vy ;

  // Mass and size of the ball
  double m ;
  double r ;

  // Gravity acceleration
  double g ;

  // Geometry of the box containing the ball
  double xmin ;
  double xmax ;
  double ymin ;
  double ymax ;
} ;

#endif /* defined(__ball__) */
