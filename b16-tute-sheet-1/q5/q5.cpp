#include <vector>
using namespace std;

class MathVector{
public:
    // First Constructor - creates vector of given length with zeros
    MathVector(int length);
    
    // Second Constructor - accepts array of values
    MathVector(int length, double values[]);
    
    // Alternative: using vector for initialization
    MathVector(const vector<double>& values);

    // Third, a copy constructor
    MathVector(const MathVector& other);

private:
    // private data
    vector<double> elements;
    int length; 

};

int main(){
    // First way - using array
    double values[] = {1.0, 2.0, 3.0};
    MathVector v1(3);
    MathVector v2(3, values); // We can't do: MathVector v2(3,{1.0, 2.0, 3.0}) because that would be an initializer list, which cannot be automatically converted to an array in a function call;
    
    // Second way - using vector constructor
    MathVector v2b({1.0, 2.0, 3.0});  // using the vector<double> constructor
    
    // Third way - copy constructor
    MathVector v3(v2);

    return 0;
}