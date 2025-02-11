## Q9: Polymorphism

### (a)

```
Foo ( Base Class)
  |
  |-- Bar (Derived Class)
```

### (b) & (c)

This is a very interesting question that tests us on polymorphism.

With Foo foo and Bar bar, we instantiated the two objects.

doit1(foo) and doit1(bar) are both valid, as the function doit1 takes in a Foo object.

doit2(foo) and doit2(bar) are both valid, as the function doit2 takes in a Foo& object.

Now the subtle thing is as belows:

doit1(foo) will take in a Foo object, and the function will call the f() and g() methods of the Foo class.

doit1(bar) will take in a Bar object but the bar object is automatically converted back to the Foo object, and the function will call the f() and g() methods of the Foo class.

doit2 passes by reference instead, so the input is not a copy. 

doit2(foo) will take in a Foo& object (the reference to the foo object), and the function will call the f() and g() methods of the Foo class.

doit2(bar) will take in a Bar object through a Foo& reference:
- For f() (non-virtual): calls Foo::f() because reference type is Foo&
- For g() (virtual): calls Bar::g() because actual object is Bar, and also Bar has the implementation of g() that derives from the virtual function g() in Foo. 

Hence, we expect the output to be:

```
Foo::f()
Foo::g()
Foo::f()
Foo::g()
Foo::f()
Foo::g()
Foo::f()
Bar::g()
```

And in reality, we got:

```
Foo::f()
Foo::g()
Foo::f()
Foo::g()
Foo::f()
Foo::g()
Foo::f()
Bar::g()
``` 

### (d)
The key difference between doit1() and doit2() lies in how parameters are passed:

1. doit1(Foo f) - Pass by Value:
   - Creates a copy of the object in the activation record
   - Due to "object slicing", only the Foo part is copied
   - Any Bar-specific data/behavior is lost
   - That's why both doit1(foo) and doit1(bar) give same results

2. doit2(Foo& f) - Pass by Reference:
   - Stores only the address of the object in the activation record
   - No slicing occurs because no copy is made
   - Preserves the actual type of the object
   - That's why doit2(bar) can call Bar's virtual functions

Memory visualization:
```
doit1(bar):                    doit2(bar):
[Activation Record]            [Activation Record]
| Foo f (full copy) |         | Foo& f (address) |
|  - Foo parts      |         |    ↓             |
|  - Bar parts lost |         | [Bar object]     |
```

This explains why:
- doit1 always uses Foo's methods (due to slicing)
- doit2 uses Foo::f() (non-virtual) but Bar::g() (virtual) for a Bar object


