#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Mass {
public:
    double position;
    double velocity;
    double mass;
    
    Mass(double m = 1.0, double pos = 0.0, double vel = 0.0) 
        : mass(m), position(pos), velocity(vel) {}
    
    // Update mass state based on force and time step
    void update(double force, double dt) {
        double acceleration = force / mass;
        velocity += acceleration * dt;
        position += velocity * dt;
    }
};

class Spring {
public:
    double springConstant;
    double restLength;
    Mass* mass1;
    Mass* mass2;
    
    Spring(double k = 1.0, double length = 1.0, Mass* m1 = nullptr, Mass* m2 = nullptr)
        : springConstant(k), restLength(length), mass1(m1), mass2(m2) {}
    
    // Calculate spring force using Hooke's Law
    double getForce() const {
        double currentLength = abs(mass2->position - mass1->position);
        double displacement = currentLength - restLength;
        return -springConstant * displacement;  // F = -kx
    }
};

class World {
public:
    vector<Mass*> masses;   
    vector<Spring*> springs;
    
    // Add simulation components
    void addMass(Mass* mass) { masses.push_back(mass); }
    void addSpring(Spring* spring) { springs.push_back(spring); }
    
    // Update the entire system for one time step
    void update(double dt) {
        // Calculate and apply forces to masses
        for (Spring* spring : springs) {
            double force = spring->getForce(); // Get the force of the spring
            spring->mass1->update(-force, dt);  // Equal and opposite forces
            spring->mass2->update(force, dt); // Apply the force to the second mass
        }
    }
    
    // Clean up allocated memory
    ~World() {
        for (Mass* mass : masses) delete mass;
        for (Spring* spring : springs) delete spring;
    }
};

// Explain the interface and how the classes will interact:

// The World class contains two vectors, one for masses and one for springs. The addMass() function adds a mass to the masses vector, and the addSpring() function adds a spring to the springs vector. The update() function updates the entire system for one time step, by calculating and applying forces to masses. The destructor cleans up allocated memory for masses and springs.

// The Mass class contains three variables: position, velocity, and mass. The update() function updates the mass's position and velocity based on the force applied to it.

// The Spring class contains three variables: springConstant, restLength, mass1, and mass2. The getForce() function calculates the force exerted by the spring on the two masses it connects.



