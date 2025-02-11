#include <vector>
#include <stdexcept>  // for std::out_of_range and std::invalid_argument
#include <iostream>
class MathVector {
private:
    std::vector<double> elements;  // Store vector elements
    int length;                    // Length of vector

public:
    // Constructors
    MathVector(int len) : elements(len, 0.0), length(len) {}  // Initialize with zeros
    
    // Constructor with initializer list, or one could just use the constructors in Q5
    MathVector(std::initializer_list<double> list) 
        : elements(list), length(list.size()) {}

    // (a) Indexing operators
    // Non-const version - allows modification (e.g., v[0] = 1.0)
    double& operator[](int index) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of bounds");
        }
        return elements[index];
    }
    
    // Const version - for read-only access (e.g., double x = v[0])
    const double& operator[](int index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of bounds");
        }
        return elements[index];
    }

    // (b) Scalar multiplication and cross product
    // Member function for vector * scalar (vα)
    MathVector operator*(double alpha) const {
        MathVector result(length);
        for(int i = 0; i < length; i++) {
            result[i] = elements[i] * alpha;
        }
        return result;
    }

    // Getter for length (needed for cross product)
    int getLength() const { return length; }
};

// Non-member function for scalar * vector (αv)
// This needs to be outside the class to handle scalar-first multiplication
MathVector operator*(double alpha, const MathVector& v) {
    return v * alpha;  // Reuse the member function
}

// Cross product (u*v) - only for 3D vectors
// This is outside the class because it operates on two vectors equally
MathVector operator*(const MathVector& u, const MathVector& v) {
    // Check if both vectors are 3D
    if (u.getLength() != 3 || v.getLength() != 3) {
        throw std::invalid_argument("Cross product only defined for 3D vectors");
    }

    // Calculate cross product: u × v
    return MathVector({
        u[1]*v[2] - u[2]*v[1],  // i component
        u[2]*v[0] - u[0]*v[2],  // j component
        u[0]*v[1] - u[1]*v[0]   // k component
    });
}

// Example usage:
int main() {
    MathVector v1({1, 0, 0});    // [1,0,0]
    MathVector v2({0, 1, 0});    // [0,1,0]
    
    // Using different operators:
    MathVector v3 = v1 * 2.0;    // Vector-scalar: [2,0,0]
    std::cout << v3[0] << std::endl;      
    MathVector v4 = 2.0 * v1;    // Scalar-vector: [2,0,0]
    std::cout << v4[0] << std::endl;
    MathVector v5 = v1 * v2;     // Cross product: [0,0,1]
    std::cout << v5[0] << std::endl;
    
    double x = v1[0];            // Indexing: x = 1.0
    std::cout << x << std::endl;
    return 0;
}

