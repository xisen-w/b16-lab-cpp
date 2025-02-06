/** file: test-srpingmass.cpp
 ** brief: Tests the spring mass simulation
 ** author: Andrea Vedaldi
 **/

#include "springmass.h"

int main(int argc, char** argv)
{
    // Create simulation with earth gravity instead
    SpringMass springmass(EARTH_GRAVITY);

    // Create two masses with:
    // - positions: (-0.5,0) and (0.5,0)
    // - zero initial velocity
    // - mass: 0.05
    // - radius: 0.02
    Mass* m1 = new Mass(Vector2(-0.5, 0), Vector2(), 0.05, 0.02);
    Mass* m2 = new Mass(Vector2(0.5, 0), Vector2(), 0.05, 0.02);
    
    // Add masses to simulation
    springmass.addMass(m1);
    springmass.addMass(m2);

    // Create spring connecting masses with:
    // - natural length: 0.95
    // - stiffness: 1.0
    // - default damping: 0.01
    Spring* spring = new Spring(m1, m2, 0.95, 1.0);
    springmass.addSpring(spring);

    // Run simulation
    const double dt = 1.0/30;  // 30 fps
    for (int i = 0; i < 100; ++i) {
        springmass.step(dt);
        springmass.display();
    }

    // Cleanup
    delete m1;
    delete m2;
    delete spring;

    return 0;
}
