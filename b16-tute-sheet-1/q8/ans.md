## Q8: Inheritance

Inheritance: It is desired to write a class hierarchy for a set of graphics shapes, all of which have a position and orientation in 3D space, and which need to implement a method to draw themselves. The geometric objects are: Point, Line, Plane, Cube, Ellipsoid, Quadric, Cone, Cuboid.

(a) Draw a likely class hierarchy.
(b) Design the base class.
(c) Explain why, by using a base class and hierarchy, the process of adding a new subclass, such as a Sphere, is greatly simplified.

### (a) Class Hierarchy

A better hierarchical structure would be:

```
Shape (Abstract Base Class)
  |
  |-- Point
  |
  |-- Line (extends Point)
  |
  |-- Plane (extends Line)
  |    |-- Quadric
  |        |-- Ellipsoid
  |
  |-- Solid
       |-- Cube
            |-- Cuboid
       |-- Cone
       |-- Sphere
```

This hierarchy reflects the geometric relationships:
- A Line is made up of Points
- A Plane is defined by Lines
- Quadrics are special types of Planes (curved surfaces)
- Solids are 3D shapes with volume, including:
  - Cone (3D shape with circular base and point at top)
  - Cube (3D shape with equal sides)
  - Cuboid (3D rectangular shape)

### (b) Base Class

```cpp
class Shape {
protected:
    Vector3D position;    // 3D position
    Matrix3D orientation; // 3D orientation matrix

public:
    // Constructor
    Shape(const Vector3D& pos, const Matrix3D& orient) 
        : position(pos), orientation(orient) {}
    
    // Pure virtual function - must be implemented by derived classes
    virtual void draw() = 0;
    
    // Virtual destructor for proper cleanup
    virtual ~Shape() {}
    
    // Common operations for all shapes
    virtual void translate(const Vector3D& delta);
    virtual void rotate(const Matrix3D& rotation);
};
```

### (c) Simplification of Adding a New Subclass

Adding a new shape (like Sphere) is simplified because:
1. Common functionality (position, orientation, basic transformations) is inherited
2. Only shape-specific code needs to be written:
   ```cpp
   class Sphere : public Ellipsoid {
   private:
       double radius;
   public:
       Sphere(const Vector3D& pos, double r) 
           : Ellipsoid(pos, r, r, r), radius(r) {}
       
       void draw() override {
           // Only need to implement sphere-specific drawing
       }
   };
   ```
3. The new shape automatically works with existing code that operates on Shape pointers
4. Polymorphism allows the new shape to be used anywhere a Shape is expected

This demonstrates the power of inheritance and polymorphism in creating extensible, maintainable code.    



