#include <iostream>
using namespace std;

class X{
    public: 
        virtual double Eval() { return 1.0; }
        void PrintValue() { cout << Eval() << endl; }
};

class Y: public X{
    public:
        Y(X& x1, X& x2): arg1(x1), arg2(x2) {} //Initialise the two arguments
        double Eval() { return arg1.Eval() * arg2.Eval(); } //Add the two arguments
    private:
        X& arg1;
        X& arg2;
};

class Z: public X{
    public:
        Z(double v): val(v) {}
        double Eval() { return -val; }
    private:
        double val;
};

class Sum: public X{
    //Sum is a class that takes two arguments and returns their sum
    public:
        Sum(X& x1, X& x2): arg1(x1), arg2(x2) {}
        double Eval() { return - (arg1.Eval() + arg2.Eval()); } // but what would Eval() be??
    private:
        X& arg1;
        X& arg2;
};

class Tan: public X{
    // Tan claculates the tan of a single argument in radians
    public:
        Tan(X& x1): arg(x1) {}
        double Eval() { return tan(arg.Eval()); }
    private:
        X& arg;
}; 


int main(){
    //First validate our b)
    Z a(2.5), b(3.0), c(10.0);
    Y d(a, b);  // d is of type Y, and a and b are of type Z
    Y e(d, c);  // e is of type Y, and d is of type Y, and c is of type Z
    cout << "b) " << endl;
    a.PrintValue();
    d.PrintValue();
    e.PrintValue();

    //Then test our c)
    Sum f(a, b);
    Tan g(f);
    cout << "c) " << endl;
    f.PrintValue();
    g.PrintValue();
}
