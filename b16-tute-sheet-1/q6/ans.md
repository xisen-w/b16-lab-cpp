## Q6: Classes & function/operator overlading

(a) For the MathVector class above, show how the square brackets operator
(indexing operator) can be overloaded to return a given indexed element.
Should this operator be a class member function, and if so will it be private
or public?

The indexing operator should be:
A member function (needs direct access to elements)
Public (users need to access vector elements)
Have both const and non-const versions

(b) Explain how the * operator can be overloaded to enable expressions such as
αv, vα, and u∗v (which we take to mean the cross-product, which you need
only implement for 3-vectors), where u and v are vectors and α is a scalar.


Special note:

The name must be operator followed by the operator symbol you want to overload. This is C++ syntax requirement. For example:

- operator[] for indexing
- operator* for multiplication
- operator+ for addition
- operator= for assignment