#include <iostream>
#include <vector>
#include <cmath>

// Basic 3D math structures
class Vector3D {
public:
    double x, y, z;
    
    Vector3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    
    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }
};

class Matrix3D {
public:
    double m[3][3];
    
    Matrix3D() {
        // Initialize as identity matrix
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                m[i][j] = (i == j) ? 1.0 : 0.0;
    }
};

// Base Shape class
class Shape {
protected:
    Vector3D position;
    Matrix3D orientation;

public:
    Shape(const Vector3D& pos = Vector3D(), const Matrix3D& orient = Matrix3D()) 
        : position(pos), orientation(orient) {}
    
    virtual void draw() = 0;  // Pure virtual
    virtual ~Shape() {}
    
    virtual void translate(const Vector3D& delta) {
        position = position + delta;
    }
    
    virtual void rotate(const Matrix3D& rotation) {
        // Apply rotation matrix
        orientation = rotation;
    }
};

// Point class
class Point : public Shape {
public:
    Point(const Vector3D& pos = Vector3D()) : Shape(pos) {}
    
    void draw() override {
        std::cout << "Drawing Point at (" << position.x << "," 
                  << position.y << "," << position.z << ")\n";
    }
};

// Line class
class Line : public Point {
protected:
    Vector3D endpoint;

public:
    Line(const Vector3D& start, const Vector3D& end) 
        : Point(start), endpoint(end) {}
    
    void draw() override {
        std::cout << "Drawing Line from (" << position.x << "," 
                  << position.y << "," << position.z << ") to ("
                  << endpoint.x << "," << endpoint.y << "," 
                  << endpoint.z << ")\n";
    }
};

// Plane class
class Plane : public Line {
protected:
    Vector3D normal;

public:
    Plane(const Vector3D& point, const Vector3D& normal) 
        : Line(point, point + normal), normal(normal) {}
    
    void draw() override {
        std::cout << "Drawing Plane at point (" << position.x << "," 
                  << position.y << "," << position.z 
                  << ") with normal vector\n";
    }
};

// Base class for all 3D solids
class Solid : public Shape {
protected:
    double volume;

public:
    Solid(const Vector3D& pos, double vol) 
        : Shape(pos), volume(vol) {}
    
    virtual double getVolume() const { return volume; }
};

// Cube class
class Cube : public Solid {
protected:
    double side;

public:
    Cube(const Vector3D& pos, double side_length) 
        : Solid(pos, side_length * side_length * side_length), 
          side(side_length) {}
    
    void draw() override {
        std::cout << "Drawing Cube with side " << side 
                  << " at (" << position.x << "," 
                  << position.y << "," << position.z << ")\n";
    }
};

// Cuboid class
class Cuboid : public Cube {
private:
    double width, height, length;

public:
    Cuboid(const Vector3D& pos, double l, double w, double h) 
        : Cube(pos, l), width(w), height(h), length(l) {
        volume = length * width * height;
    }
    
    void draw() override {
        std::cout << "Drawing Cuboid " << length << "x" << width 
                  << "x" << height << " at (" << position.x << "," 
                  << position.y << "," << position.z << ")\n";
    }
};

// Sphere class (could also inherit from Ellipsoid if implemented)
class Sphere : public Solid {
private:
    double radius;

public:
    Sphere(const Vector3D& pos, double r) 
        : Solid(pos, (4.0/3.0) * M_PI * r * r * r), radius(r) {}
    
    void draw() override {
        std::cout << "Drawing Sphere with radius " << radius 
                  << " at (" << position.x << "," 
                  << position.y << "," << position.z << ")\n";
    }
};

// Example usage
int main() {
    std::cout << "\n=== Testing Shape Hierarchy ===\n\n";

    // Create shapes
    std::cout << "Creating shapes...\n";
    Point p(Vector3D(1, 2, 3));
    Line l(Vector3D(0, 0, 0), Vector3D(1, 1, 1));
    Cube c(Vector3D(5, 5, 5), 2.0);
    Sphere s(Vector3D(3, 3, 3), 1.5);
    Cuboid cb(Vector3D(1, 1, 1), 3.0, 2.0, 1.0);  // length=3, width=2, height=1
    
    std::cout << "\n=== Initial Positions ===\n";
    std::cout << "Point: "; p.draw();
    std::cout << "Line: "; l.draw();
    std::cout << "Cube: "; c.draw();
    std::cout << "Sphere: "; s.draw();
    std::cout << "Cuboid: "; cb.draw();
    
    // Test volume calculations
    std::cout << "\n=== Volume Tests ===\n";
    std::cout << "Cube volume (should be 8): " << c.getVolume() << "\n";
    std::cout << "Sphere volume: " << s.getVolume() << "\n";
    std::cout << "Cuboid volume (should be 6): " << cb.getVolume() << "\n";
    
    // Test polymorphism
    std::cout << "\n=== Testing Polymorphism ===\n";
    std::vector<Shape*> shapes = {&p, &l, &c, &s, &cb};
    std::cout << "Drawing all shapes through base class pointers:\n";
    for(Shape* shape : shapes) {
        shape->draw();
    }
    
    // Test translations
    std::cout << "\n=== Testing Translations ===\n";
    Vector3D translation(1, 1, 1);
    std::cout << "Translating all shapes by (1,1,1):\n";
    for(Shape* shape : shapes) {
        shape->translate(translation);
        shape->draw();
    }
    
    // Test individual shape features
    std::cout << "\n=== Testing Individual Features ===\n";
    
    // Create a plane
    Plane pl(Vector3D(0, 0, 0), Vector3D(0, 0, 1));
    std::cout << "Plane: "; pl.draw();
    
    // Create shapes with different parameters
    Cube smallCube(Vector3D(0, 0, 0), 1.0);
    Sphere bigSphere(Vector3D(0, 0, 0), 3.0);
    std::cout << "Small cube: "; smallCube.draw();
    std::cout << "Big sphere: "; bigSphere.draw();
    
    std::cout << "\n=== Test Complete ===\n\n";
    
    return 0;
}
