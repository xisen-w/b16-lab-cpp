```cpp

class Minimiser {
    public:
        Minister(const Func& f, const double startX);
        double Minimum() const;
        double MinimumLocation() const;
    private:
        Func _f;
        double _startX;
        double _minimum;
        double _minimumX; 

}

class Func {

    Func(){

    }

    public: Func(const Func& b){
    }

    virtual bool hasDerivative() const{
        return false;
    }

    virtual dobule val(double x) const{

    }

    virtual double derivative(double x) const{


    }

}

#include <cmath>

class ExponentialFunction : public Func {
public:
    // Compute the function value at x
    double value(double x) const override {
        if (x == 0) {
            throw std::domain_error("Division by zero");
        }
        return std::exp(x) / (x * x);
    }

    // Compute the derivative at x
    bool derivative(double x, double& deriv) const override {
        if (x == 0) {
            return false; // Derivative not defined at x = 0
        }
        deriv = (std::exp(x) * (x - 2)) / (x * x * x);
        return true;
    }
};
```