# Lab Notes Xisen

This place stores the logging for the questions and answers.

## Task 1: Understanding the implementation of the member functions.

#### Q: What is the initial state of the ball when the object is created (instantiated)?

This is the state: 

```cpp
Ball::Ball()
: r(0.1),    // radius = 0.1
  x(0),      // x position = 0 (center)
  y(0),      // y position = 0 (center)
  vx(0.3),   // x velocity = 0.3
  vy(-0.1),  // y velocity = -0.1
  g(9.8),    // gravity = 9.8
  m(1),      // mass = 1
  xmin(-1), xmax(1), ymin(-1), ymax(1)  // box boundaries
{ }
```

#### Q: How does display() prints information on the screen?

```cpp
void Ball::display()
{
  std::cout<<x<<" "<<y<<std::endl ;
}
```

It uses cout to print the x and y coordinates of the ball.

#### Q: The ball is constrained to bounce in the box [−1, 1] × [−1, 1]. How is this handled by theintegrator implemented in step()? Is the total (kinetic + potential) energy of the ball conserved by this integrator?

This is handled by the integrator implemented in step(). The integrator is a function that updates the position and velocity of the ball based on the forces acting on it. 

#### Energy Conservation: Yes! It's very elastic. 

Another note is that it's quite discrete and the more "precision" you give for the time the better the plot is. 

#### Now look at test-ball.cpp and answer the following question: What do you expect the output of your program to be?

We should explain what happens in test-ball.cpp:

1. **Setup:**
```cpp
Ball ball;  // Creates ball at initial position (0,0) with initial velocity (0.3, -0.1)
const double dt = 1.0/30;  // Time step of approximately 0.033 seconds
```

2. **Simulation Loop:**
```cpp
for (int i = 0 ; i < 100 ; ++i) {  // Runs for 100 iterations
    ball.step(dt);   // Updates position and velocity
    ball.display();  // Prints current position
}
```

The simulation will:
- Run for 100 frames
- Each frame represents 1/30 second (typical animation frame rate)
- Total simulation time = 100 * (1/30) ≈ 3.33 seconds

We will see: 
- The output will be 100 lines of x-y coordinates
- The ball will:
  1. Start at (0,0)
  2. Move right (due to vx = 0.3) and downward (due to vy = -0.1 and gravity g = 9.8)
  3. Bounce off walls when it hits them (x = ±0.9, accounting for radius 0.1)
  4. Bounce off floor/ceiling (y = ±0.9)
  5. Each bounce will reverse the respective velocity component

Sample of first few lines of output might look like:
```
0 0
0.01 -0.00498
0.02 -0.01994
...
```

The motion will show:
- Parabolic trajectories between bounces (due to gravity)
- Perfect bounces off walls
- Gradually increasing downward speed between floor bounces (due to gravity)
- Continuous horizontal motion with direction changes at wall collisions

## Task 2: Running the program. 

The last question can be answered empirically, by com-
piling and running the program. In order to do so:
• Make sure that test-ball is the target that will be run. See Figure 2 for details. For
Windows system, it should be e.g. test-ball-win.
• Select Run Without Debugging in the Run menu (at the top of the screen).
This will automatically compile and link the program to create and run the ball executable
for you. A console window will pop up, displaying the output of the program. Does it look
reasonable?

Snippet:
```
0.01 -0.00877778
0.02 -0.0284444
0.03 -0.059
0.04 -0.100444
0.05 -0.152778
0.06 -0.216
0.07 -0.290111
0.08 -0.375111
```
Looks quite reasonable to me.

## Task 3 & Task 4: 

Reasonable.

Section 3.3 simply explains the differences between public, private, and protected. 

We first declare, and then define. 

## Task 5: Member functions and separation of concerns. 

By isolating data members
in the protected part of the class definition, the representation of the data (protected data
members) can be separated from the operations that apply to it (public member functions).
Answer the following questions:
Q: **How should the class be changed so that a user could be able to get and set the position**
of the ball?
- We should add public getter and setter methods (accessors and mutators). 

Q: **The member functions of a class are often said to encode its “behaviour”. Can you find a practical example demonstrating why separating the data representation from its behaviour is useful?**

- It is useful because it allows us to change the data representation without changing the behavior of the class. Eg, we can change the data representation of the ball from a circle to a square, but the behavior of the ball will remain the same. Or, coordinate transformation could also work. 

```cpp
class Ball : public Simulation
{
protected:
    // Could change internal representation
    double radius;    // distance from origin
    double theta;     // angle
    // instead of x,y coordinates

public:
    // But keep the same interface
    double getX() const { return radius * cos(theta); }
    double getY() const { return radius * sin(theta); }
    void setPosition(double x, double y) {
        radius = sqrt(x*x + y*y);
        theta = atan2(y, x);
    }
```

## Task 6:Understanding constructors. 

The constructor Ball() does not allow the use of the class to choose a custom initial position or velocity of the ball. Design an alternative constructor that would allow to do so upon class instantiation.

Our solution:

```cpp
Ball::Ball(double initialX, double initialY, double initialVx, double initialVy)
: r(0.1), g(9.8), m(1),
xmin(-1), xmax(1), ymin(-1), ymax(1)
{
  // Use setPosition to ensure bounds checking
  setPosition(initialX, initialY);
  
  // Set velocities
  vx = initialVx;
  vy = initialVy;
}
```

Now we can create a ball with a custom initial position and velocity.

Like:
```cpp
// Example usage:
Ball ball1;  // Uses default constructor (0,0) position, (0.3,-0.1) velocity
Ball ball2(0.5, 0.5, -0.2, 0.4);  // Custom position (0.5,0.5) and velocity (-0.2,0.4)
```

## Task 7: Programming principles.

What is the distinction between a class declaration, definition, implementation, and instantiation?

- Class declaration: The class is declared, but not defined.
- Class definition: The class is declared and defined.
- Class implementation: The class is implemented.
- Class instantiation: The class is instantiated.

Example:

```cpp
class Ball;                              // 1. Declaration: Just the name and interface (compiler promise)

class Ball { double x; void move(); };   // 2. Definition: Full class structure and members

void Ball::move() { x += 1; }           // 3. Implementation: Actual code for methods

Ball b1;                                 // 4. Stack Instantiation: Create object
Ball* b2 = new Ball();                  // 5. Heap Instantiation: Create object dynamically
```

## Task 8 & 9 : 

IDE is cool! Not that suitable for mac tho. 

## Task 10: Interface

Thus Simulation declares two virtual member functions step() and display(). The = 0 suffix tells the compiler that it should not expect Simulation to provide a de nition of these functions. Rather, this is left to the compiler. Answer the following questions:

Can you replace the for loop in the main function de ned in test-ball.cpp with the instruction run(ball, dt)?

```cpp
// In simulation.h
class Simulation {
public:
    virtual void step(double dt) = 0;    // Pure virtual functions
    virtual void display() = 0;
};

// In test-ball.cpp
void run(Simulation& s, double dt) {
    for (int i = 0; i < 100; ++i) {
        s.step(dt);
        s.display();
    }
}

int main() {
    Ball ball;
    run(ball, dt);    // This works with virtual functions
    return 0;
}
```


What would happen if Simulation did not declare step and display to be virtual? Would run still work as expected? If not, what would happen?

Without virtual functions:
The compiler would use "static binding" instead of "dynamic binding"
It would call Simulation::step() and Simulation::display() instead of Ball::step() and Ball::display()
This would likely cause:
Compilation error if Simulation doesn't implement these methods
Or incorrect behavior if it does implement them, as it would not use Ball's specific implementations
Here's the difference:

```cpp
// Without virtual (WRONG behavior)
class Simulation {
    void step(double dt) { /* base version */ }
};

// With virtual (CORRECT behavior)
class Simulation {
    virtual void step(double dt) = 0;  // Forces derived classes to implement
};
```

## Task 11: Complete the Mass class. 

Start by completing the implementation Mass class by implementing the member functions getEnergy() and step()

The Mass class implementation now includes two key physics functions: getEnergy() calculates the total mechanical energy of the mass by summing its kinetic energy (½mv²) and gravitational potential energy (mgh), while step() handles the time evolution of the system by updating position and velocity using Newton's laws of motion. The step function also includes collision handling with the boundaries of the container, implementing elastic collisions by reversing the appropriate velocity component when the mass hits a wall, and updates the velocity based on accumulated forces before resetting the force accumulator for the next timestep.

## Task 12: Complete the Spring class. 

Gets positions (x1, x2) and velocities (v1, v2) of both masses
Calculates spring geometry:
Displacement vector (x2 - x1)
Current length (l)
Unit direction vector (u12)
Calculates spring force:
F1 = k(l - l0)u12
Where k is stiffness and l0 is naturalLength
Calculates damping force:
Projects relative velocity onto spring direction
F1 = d((v2-v1)·u12)u12
Where d is damping coefficient
Returns total force (spring + damping)

## Task 13:

This implementation:
Uses vectors to store multiple masses and springs
Handles gravity and spring forces properly
Updates all masses in the system
Displays state of all masses and springs
Calculates total system energy

Check sample usage here: 

```cpp 
int main() {
    SpringMass sim(MOON_GRAVITY);
    
    // Create and add masses
    Mass* m1 = new Mass(Vector2(-0.5, 0), Vector2(), 0.05, 0.02);
    Mass* m2 = new Mass(Vector2(0.5, 0), Vector2(), 0.05, 0.02);
    sim.addMass(m1);
    sim.addMass(m2);
    
    // Create and add spring
    Spring* spring = new Spring(m1, m2, 0.95, 1.0);
    sim.addSpring(spring);
    
    // Run simulation
    const double dt = 1.0/30;
    for(int i = 0; i < 100; ++i) {
        sim.step(dt);
        sim.display();
    }
    
    // Cleanup
    delete m1;
    delete m2;
    delete spring;
    
    return 0;
}
```

## Task 14 & 15:

Implemented & Visualised. Looking quite cool! 

I tried to run it like a video (of different frames), and it works quite well. 

## Task 16: OpenGL

Understand how to open a window and draw in it. Then navigate in Visual Studio Code to the file graphics.h file and inspect it. This module does a few things:
• It includes the OpenGL header files (glut.h). This means that, by including graphics.h, your program will have access to the OpenGL functions as well. GLUT is an utility library, companion to OpenGL, which handles windows and events | more on this later.
• It declares a function run() that takes as input an object of type Simulation and a timeStep. This function never returns; instead, it enters a loop that handles the stream of events from the graphical user interface (e.g. a window being resized). It also runs the simulation by repeatedly calling the member functions step (to advance the simulation) and display (to update a corresponding figure).
• It de nes a class Figure which simpli es opening a window and drawing in it.

A: We first understand the components in graphics.h

```cpp
// Key components in graphics.h
class Figure {
public:
    void drawCircle(double x, double y, double r);  // Draw a circle
    void drawLine(double x1, double y1, double x2, double y2);  // Draw a line
    void update();  // Update the display
};

void run(Simulation* simulation, double timeStep);  // Main animation loop
```




















