#include <iostream>

class Foo {
public:
void f() { std::cout << "Foo::f()" << std::endl; }
virtual void g() { std::cout << "Foo::g()"
<< std::endl; }
};
class Bar : public Foo {
public:
void f() { std::cout << "Bar::f()" << std::endl; }
virtual void g() { std::cout << "Bar::g()"
<< std::endl; }
};
void doit1(Foo f) {
f.f();
f.g();
}
void doit2(Foo& f) {
f.f();
f.g();
}
int main() {
Foo foo;
Bar bar;
doit1(foo);
doit1(bar);
doit2(foo);
doit2(bar);
return 0;
}