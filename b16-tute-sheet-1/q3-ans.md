## Question 3

Explain the following concepts, and their significance, in the context of object-oriented programming:

(a) Encapsulation.

A: Encapsulation is the practice of hiding the internal details of an object from the outside world, and only exposing the 'interface' of the function or object. This is important because it allows us to control how the object is used, simplifies the code orgnisation from outside, and protects the internal details from being seen or modified from the outside. 


(b) Compile-time Polymorphism.

A: Compile-time polymorphism is when the compiler determines which function to use at compile time, for example through function overloading. This is important because it allows us to create multiple functions with the same name but different input parameters, which adds up flexibility and reusability. 

(c) Inheritance

A: Inheritance is the practice of creating a new class that 'extends' or 'inherits' from an existing class in a way that it shares the functions and variables of the parent class. This is important as it allows us to write code in a scalable and reusable way for creating new classes that have hierarchical relationships. 

This is related to 'runtime polymorphism' as it allows us to create derived classes that can override virtual functions from the base class. Method overriding occurs when a derived class provides a specific implementation for a method that is already defined in its base class. When combined with virtual functions, this enables runtime polymorphism - where the appropriate method implementation is determined at runtime based on the actual type of the object, not its declared type.

For example:
```cpp
class Animal {
public:
virtual void makeSound() { cout << "..." << endl; }
};
class Dog : public Animal {
public:
void makeSound() override { cout << "Woof!" << endl; } // This is method overriding
};
``` 

