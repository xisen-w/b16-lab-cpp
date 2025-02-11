## Q5

### a)

Code is already shown in q5.cpp. 

Special note: MathVector(const MathVector& other) is a copy constructor., as it takes another MathVector object as an argument. 

```cpp
MathVector v1(3);           // Create first vector
MathVector v2 = v1;         // Copy constructor called
MathVector v3(v1);          // Also calls copy constructor
```

### b)

Shown in the code too.


### c) & d) Problems & Solutions with Dynamic Memory Allocation

We are asked to explain the problems with dynamic memory allocation using `new` instead of `std::vector<>`.

When using raw pointers with dynamic memory allocation, several critical issues arise:

1. **Manual Memory Management**
```cpp
class MathVector {
    double* elements;  // Raw pointer
public:
    // Must remember to allocate
    MathVector(int len) {
        elements = new double[len];  // What if this fails?
    }
    
    // Must remember to deallocate
    ~MathVector() {
        delete[] elements;  // Forgetting this = memory leak
    }
};
```

2. **Deep Copy Requirements**
```cpp
class MathVector {
    double* elements;
    int length;
public:
    // Without proper copy constructor:
    MathVector(const MathVector& other) {
        elements = other.elements;  // WRONG! Shallow copy
        // Both objects now point to same memory
        // When one is deleted, the other has dangling pointer
    }
    
    // Correct deep copy needed:
    MathVector(const MathVector& other) {
        elements = new double[other.length];  // Allocate new memory
        for(int i = 0; i < other.length; i++) {
            elements[i] = other.elements[i];  // Copy each element
        }
    }
};
```

3. **Exception Safety Issues**
```cpp
class MathVector {
    double* elements1;
    double* elements2;
public:
    MathVector(int len) {
        elements1 = new double[len];  // What if this succeeds...
        elements2 = new double[len];  // ...but this fails?
        // Memory leak! elements1 is never freed
    }
};
```

If the second new fails (throws bad_alloc), the first allocation is never freed
Constructor exits due to exception before finishing
Destructor won't be called for partially constructed objects
Result: Memory leak of elements1

4. **Assignment Operator Problems**
```cpp
MathVector& operator=(const MathVector& other) {
    if (this != &other) {  // Self-assignment check needed
        delete[] elements;  // Delete old memory
        length = other.length;
        elements = new double[length];  // What if this throws?
        // Copy elements...
    }
    return *this;
}
```

In contrast, `std::vector` handles all these issues:
```cpp
class MathVector {
    std::vector<double> elements;  // RAII handles everything
public:
    MathVector(int len) : elements(len) {}  // Allocation
    // No destructor needed
    // No copy constructor needed
    // No assignment operator needed
    // Exception safe
    // Memory safe
};
```

The `std::vector` implementation:
- Automatically manages memory (RAII)
- Provides exception-safe copying
- Handles self-assignment
- Prevents memory leaks
- Prevents dangling pointers
- Manages resource cleanup automatically

This is why modern C++ strongly encourages using standard containers like `vector` instead of raw pointers and manual memory management.
