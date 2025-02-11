## Q7:Access Control & Const

### a)

First implementation doesn't put float p in public, and then we can't access it from outside the class.

Benefit is 1) Good control over the data members, 2) Can prevent unintended modifications, 3) Can hide the internal implementation details from the user, 4) Can provide flexibility in how the class is used.

The drawbacks are:
1) We can't access the data member from outside the class, so sometimes it is not convenient.
2) We can't use the data member in the constructor initializer list.    

Second implementation puts float p in public, and then we can access it from outside the class.

Benefit is 1) We can access the data member from outside the class, so it is convenient.
2) We can use the data member in the constructor initializer list.

Drawback is 1) We can't prevent unintended modifications, 2) We can't hide the internal implementation details from the user, 3) We can't provide flexibility in how the class is used (?)

b) 

(b) A fellow engineer presents you with the denitions of the following functions,
without giving you access to the implementation. What will you know about
input parameter b after each of them are called?
i. void fn_i(BernoulliDistributionA & b);
ii. void fn_ii(BernoulliDistributionA *& b);
iii. void fn_iii(const BernoulliDistributionB & b);
iv. void fn_iv(BernoulliDistributionB & b);
v. void fn_v(BernoulliDistributionB b);

i. After fn_i(BernoulliDistributionA & b);, we know that b is a BernoulliDistributionA object. Also the reference is not const, so we can modify the object.

ii. After fn_ii(BernoulliDistributionA *& b);, we know that b is a pointer to a BernoulliDistributionA object. Also the pointer is not const, so we can modify the object. The pointer is passed by reference, so we can modify the pointer itself. It is different from i because the pointer is passed instead of ..

iii. After fn_iii(const BernoulliDistributionB & b);, we know that b is a const BernoulliDistributionB object. Also the reference is const, so we can't modify the object.

iv. After fn_iv(BernoulliDistributionB & b);, we know that b is a BernoulliDistributionB object. Also the reference is not const, so we can modify the object.

v. After fn_v(BernoulliDistributionB b);, we know that b is a BernoulliDistributionB object. Also the object is not const, so we can modify the object.

Let's analyze each function signature:

1. `void fn_i(BernoulliDistributionA & b)`
   - Takes a non-const reference to a BernoulliDistributionA object
   - After calling: 
     - The object `b` might be modified (because it's non-const)
     - The reference points to the same object (can't be reassigned)

2. `void fn_ii(BernoulliDistributionA *& b)`
   - Takes a reference to a pointer to a BernoulliDistributionA object
   - After calling:
     - The pointer itself can be modified (can point to a different object)
     - The object pointed to can be modified
     - Example:
       ```cpp
       BernoulliDistributionA* ptr = new BernoulliDistributionA();
       fn_ii(ptr);  // ptr might point to a different object after this
       ```

3. `void fn_iii(const BernoulliDistributionB & b)`
   - Takes a const reference to a BernoulliDistributionB object
   - After calling:
     - The object `b` cannot be modified (const)
     - Used for read-only operations

4. `void fn_iv(BernoulliDistributionB & b)`
   - Similar to fn_i but for BernoulliDistributionB
   - After calling:
     - The object `b` might be modified
     - Reference remains to same object

5. `void fn_v(BernoulliDistributionB b)`
   - Takes BernoulliDistributionB by value (makes a copy)
   - After calling:
     - Original object is unchanged (function worked on a copy)
     - Most expensive in terms of memory (full object copy)


Additional note:
*b:
caller → ptr → [object]
fn1   → ptr(copy) → [new object]  // Original ptr unchanged

*&b:
caller → ptr → [object]
fn2   → ptr(reference) → [new object]  // Original ptr modified


