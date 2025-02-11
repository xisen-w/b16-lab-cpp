## Q10: More polymorphism

### (a) Class Hierarchy Diagram

![Class Hierarchy Diagram](class_hierarchy.png)

```
X ( Base Class)
  |
  |-- Y (Derived Class)
  |-- Z (Derived Class)
```

### (b)

Input is given as:

```
Z a(2.5), b(3.0), c(10.0);
Y d(a, b);  // d is of type Y, and a and b are of type Z
Y e(d, c);  // e is of type Y, and d is of type Y, and c is of type Z
```

a is an object of class Z. Z inherits from X, so a is also an object of class X. The PrintValue() function is defined in class X, so we can call it on a. Also, it is not a virtual function. Hence, a.PrintValue() will output Eval() of a. But a.Eval() is defined in class Z, so it will output -2.5, as Eval() is a virtual function in X. 

d is an object of class Y. Y inherits from X, so d is also an object of class X. The PrintValue() function is defined in class X, so we can call it on d. Also, it is not a virtual function. Hence, d.PrintValue() will output Eval() of d. But d.Eval() is defined in class Y, so it will output a * b = 7.5. 

e is an object of class Y. Y inherits from X, so e is also an object of class X. The PrintValue() function is defined in class X, so we can call it on e. Also, it is not a virtual function. However, as eval() is a virtual function, the actual function called is the one in class Y. Now, e.Eval() is defined in class Y, so it will output eval of d * eval of c. We know that d is an object of class Y, so eval of d is 7.5 (a*b), but c is an object of class Z, so the eval of c is -10.0. Therefore, e.Eval() will output 7.5 * -10.0 = -75.0. 

