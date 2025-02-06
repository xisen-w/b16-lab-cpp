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

#### Energy Conservation:
The integrator **does not** conserve total energy due to:
- Simple velocity reversal on collision.
- Euler integration for position and velocity updates.
- No elastic collision physics.
- Gravity approximation using basic kinematics.


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

## Task 2: Implementing a more realistic ball simulation

