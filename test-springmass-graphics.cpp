/** file: test-springmass-graphics.cpp
 ** brief: Tests the spring mass simulation with graphics
 ** author: Andrea Vedaldi
 **/

#include "graphics.h"
#include "springmass.h"

#include <iostream>
#include <sstream>
#include <iomanip>

/* ---------------------------------------------------------------- */
class SpringMassDrawable : public SpringMass, public Drawable
/* ---------------------------------------------------------------- */
{
private:
    Figure figure;
    float rotationX = 0.0f;
    float rotationY = 0.0f;
    float zoom = -5.0f;

public:
    SpringMassDrawable() 
    : figure("3D Spring Mass System") {
        figure.addDrawable(this);
    }

    void draw() {
        // Set up 3D view
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, zoom);
        glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
        
        // Enable depth testing
        glEnable(GL_DEPTH_TEST);
        
        // Draw coordinate axes
        glBegin(GL_LINES);
            // X axis (red)
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);
            
            // Y axis (green)
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 1.0f, 0.0f);
            
            // Z axis (blue)
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 1.0f);
        glEnd();
        
        // Draw masses as spheres
        for(Mass* mass : masses) {
            Vector3 pos = mass->getPosition();
            glPushMatrix();
            glTranslatef(pos.x, pos.y, pos.z);
            glutSolidSphere(mass->getRadius(), 20, 20);
            glPopMatrix();
        }
        
        // Draw springs
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);
        for(Spring* spring : springs) {
            Vector3 pos1 = spring->getMass1()->getPosition();
            Vector3 pos2 = spring->getMass2()->getPosition();
            glVertex3f(pos1.x, pos1.y, pos1.z);
            glVertex3f(pos2.x, pos2.y, pos2.z);
        }
        glEnd();
    }

    void display() {
        figure.update();
    }

    // Add keyboard controls
    static void handleKeyboard(unsigned char key, int x, int y) {
        SpringMassDrawable* sim = static_cast<SpringMassDrawable*>(runningSimulation);
        switch(key) {
            case 'w': sim->rotationX += 5.0f; break;
            case 's': sim->rotationX -= 5.0f; break;
            case 'a': sim->rotationY -= 5.0f; break;
            case 'd': sim->rotationY += 5.0f; break;
            case 'q': sim->zoom -= 0.5f; break;
            case 'e': sim->zoom += 0.5f; break;
        }
        glutPostRedisplay();
    }
} ;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    SpringMassDrawable springmass;
    
    // Create masses in 3D space
    Mass* m1 = new Mass(Vector3(-0.5, 0, 0.2), Vector3(), 0.05, 0.02);
    Mass* m2 = new Mass(Vector3(0.5, 0, -0.2), Vector3(), 0.05, 0.02);
    Mass* m3 = new Mass(Vector3(0, 0.5, 0), Vector3(), 0.05, 0.02);
    
    springmass.addMass(m1);
    springmass.addMass(m2);
    springmass.addMass(m3);
    
    // Create springs to form a triangle
    Spring* s1 = new Spring(m1, m2, 0.95, 1.0, 0.01);
    Spring* s2 = new Spring(m2, m3, 0.95, 1.0, 0.01);
    Spring* s3 = new Spring(m3, m1, 0.95, 1.0, 0.01);
    
    springmass.addSpring(s1);
    springmass.addSpring(s2);
    springmass.addSpring(s3);
    
    run(&springmass, 1.0/60);
    return 0;
}
