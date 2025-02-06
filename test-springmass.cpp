/** file: test-srpingmass.cpp
 ** brief: Tests the spring mass simulation
 ** author: Andrea Vedaldi
 **/

#include "springmass.h"

int main(int argc, char** argv)
{
  SpringMass springmass ;

  const double mass = 0.05 ;
  const double radius = 0.02 ;
  const double naturalLength = 0.95 ;

  Mass m1(Vector2(-.5,0), Vector2(), mass, radius) ;
  Mass m2(Vector2(+.5,0), Vector2(), mass, radius) ;

/* INCOMPLETE: TYPE YOUR CODE HERE */

  const double dt = 1.0/30 ;
  for (int i = 0 ; i < 100 ; ++i) {
    springmass.step(dt) ;
    springmass.display() ;
  }

  return 0 ;
}
