# Question 3

**Q**: Templates: What is the difference between a function template and a template function?

**A**: 

A function template is a blueprint for a function that can be used to create a function of any type. 

Example: Function Template:

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}
```
```cpp
#include <iostream>

using namespace std;

tempalte <typename T>
T add(T a, T b){
    return a + b;
}

int main(){
    cout << add(1, 2) << endl; // Instantiate the template for int
    cout << add(1.0, 2.0) << endl; // Instantiate the template for double
    return 0;
}
```

A template function is a function that is created from a function template.

Example: Template Function:

```cpp
//Explicit instantiatoin of a template function 

template int <add<int>> (int, int); // int version 
template double <add<double>> (double, double); // double version  
```













